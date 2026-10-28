/* SPDX-License-Identifier: CC0-1.0
 * rg_timing: the port half of the timing record (rg_timing.h,
 * docs/TIMING-LOCKSTEP.md).  Records use probe.py's JSONL schema; the site
 * table is generated from probe.py (tools/trace/gen_timing_sites.py). */
/* the generated site table's data (rg_timing.h includes rg_timing_sites.h) */
#define RG_TIMING_SITE_TABLE 1
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ps2k.h"
#include "rg_runtime.h"
#include "rg_trace.h"
#include "rg_timing.h"
#include "ovl.h"
#include "libcdvd.h"
#include "rg_fs.h"
#include "libpad.h"
#include "movie_game.h"


/* Game addresses (retail SCUS_974.90; the same as probe.py's T_* constants). */
#define A_DRAWCTX    0x004810A4u   /* GetDrawCtx_15de80: frame context pointer */
#define A_SCENE      0x00481998u   /* GetCurrentScene_1f5be0: scene pointer */
#define A_GAMEMODE   0x004B51A0u   /* GameModeStack[0] */
#define A_PHASE      0x004B51E0u   /* GameModePhaseStack[0] */
#define A_OVERLAY    0x0047E254u   /* OverlayLoad_1c3210 / GetLoadedOverlayId_1c3200 */
#define A_SYSMODE    0x0047E224u   /* MainLoop_1c2c10 mode */
#define A_PAUSESTEP  0x0048276Cu   /* GetPauseStep_2f6660 */
#define A_TASKDEPTH  0x00482278u   /* TaskStatePushAll_27c220 depth */
#define A_VSYNC_SEMA 0x0047DF18u   /* WaitVsyncCount_15de90's semaphore id */
/* frame context (GfxEndFrame_141c20 / GfxFlipBuffersMaybe_143650) */
#define CTX_DB       0x270u        /* -> Db: +0x24 interval, +0x28 sync, +0x2C divisor */
#define CTX_FLIP     0xF00u        /* vbl of the last flip (o->last) */
#define CTX_LATE     0xF04u
#define CTX_FB       0xF10u        /* stored feedback (f32) */
#define CTX_F18      0xF18u
#define CTX_DEPTH_ON 0x3CD0u
#define CTX_DEPTH_Z  0x3CDCu
#define CTX_3D2C     0x3D2Cu
#define SCENE_TS     0x5E00u       /* +0x5E00..+0x5E14 time-scale block */

#define MAX_TID   (PS2K_MAX_THREADS + 1)
#define MAX_DEPTH 64

int rg_timing_on;

typedef struct frame {
    int site;
    unsigned flags;
    uint32_t a[4], f12;
    const void *ra;
} frame;

static struct {
    rg_timing_config cfg;
    FILE *f;
    int open, attached, obs, armed, atexit_set;
    uint64_t seq;
    rg_timing_stats st;
    uint8_t wrapped[RG_TIMING_NSITES];   /* the stage wraps this site: built-in source off */
    frame (*stk)[MAX_DEPTH];             /* [MAX_TID][MAX_DEPTH] */
    int depth[MAX_TID];
    uint32_t next_pair;                  /* built-in entry/ret pairs: 0x80000000 | n */
    /* memory view */
    int have_flip;
    uint32_t last_flip;
    int have_mem;
    uint32_t mem[10];
    /* kernel trace: vsync-sema waits */
    int32_t vsync_sema;
    int last_vsync_tid;
    uint32_t vsync_waits;                /* since the last VBlank */
    int movie_active;
    uint32_t ovl_pair;
    int stopped;
} T;

/* ------------------------------------------------------------ memory */
static int rd_ps2(uint32_t addr, uint32_t *v)
{
    uint8_t b[4];
    if (rg_trace_read(addr, b, 4, NULL) != 0)
        return -1;
    *v = b[0] | b[1] << 8 | b[2] << 16 | (uint32_t)b[3] << 24;
    return 0;
}

static uint32_t rd_ps2_or0(uint32_t addr)
{
    uint32_t v = 0;
    rd_ps2(addr, &v);
    return v;
}

/* A host pointer stored in game memory (i686: 32 bits): through the reverse
 * map when it covers it, else raw if the page is readable. */
static int rd_host(uint32_t hostp, uint32_t *v)
{
    uint32_t ps2;
    const void *p = (const void *)(uintptr_t)hostp;
    if (!hostp)
        return -1;
    if (rg_trace_ps2_addr(p, &ps2) == 0 && rd_ps2(ps2, v) == 0)
        return 0;
    if (!rg_trace_host_readable(p, 4))
        return -1;
    memcpy(v, p, 4);
    return 0;
}

static uint32_t rd_host_or0(uint32_t hostp)
{
    uint32_t v = 0;
    rd_host(hostp, &v);
    return v;
}

static uint32_t to_ps2(uint32_t hostp)
{
    uint32_t ps2;
    if (hostp && rg_trace_ps2_addr((const void *)(uintptr_t)hostp, &ps2) == 0)
        return ps2;
    return hostp;
}

/* One dump word (probe.py W_* semantics; rg_timing.h). */
static uint32_t dump_word(const rg_timing_word *w, const frame *fr)
{
    uint32_t p;
    int i;
    switch (w->kind) {
    case RG_TW_FPR:
        return fr ? fr->f12 : 0;
    case RG_TW_ARG:
        if (!fr || w->base > 3)
            return 0;
        p = fr->a[w->base];
        if (!w->noffs)
            return (fr->flags & (1u << w->base)) ? to_ps2(p) : p;
        for (i = 0; i < w->noffs - 1; i++) {
            p = rd_host_or0(p + w->offs[i]);
            if (!p)
                return 0;
        }
        return rd_host_or0(p + w->offs[w->noffs - 1]);
    case RG_TW_ABS:
        /* the first load is at a PS2 address; what it yields is a host pointer */
        if (!w->noffs)
            return w->base;
        if (w->noffs == 1)
            return rd_ps2_or0(w->base + w->offs[0]);
        p = rd_ps2_or0(w->base + w->offs[0]);
        for (i = 1; i < w->noffs - 1; i++) {
            if (!p)
                return 0;
            p = rd_host_or0(p + w->offs[i]);
        }
        return p ? rd_host_or0(p + w->offs[w->noffs - 1]) : 0;
    default:
        return 0;
    }
}

/* ------------------------------------------------------------ records */
static uint32_t cur_vbl(void)
{
    return rg_trace_read_vbl((uint32_t)ps2k_vblank_count(), NULL);
}

static void json_str(FILE *f, const char *s)
{
    fputc('"', f);
    for (; s && *s; s++) {
        unsigned char c = (unsigned char)*s;
        if (c == '"' || c == '\\')
            fprintf(f, "\\%c", c);
        else if (c < 0x20 || c >= 0x7F)
            fprintf(f, "\\u%04x", c);
        else
            fputc(c, f);
    }
    fputc('"', f);
}

/* extra: already-formatted JSON members (",\"k\":v..."), or NULL */
static void rec(const char *k, const char *fn, uint32_t vbl, const uint32_t a[4], uint32_t v0, uint32_t pair,
                const uint32_t d[6], const char *ra_name, const void *ra, const char *src, const char *extra)
{
    static const uint32_t z[6];
    if (!T.open)
        return;
    if (!a)
        a = z;
    if (!d)
        d = z;
    fprintf(T.f, "{\"t\":\"r\",\"seq\":%llu,\"k\":\"%s\",\"fn\":\"%s\",\"vbl\":%u,\"cnt\":%u,"
                 "\"a\":[%u,%u,%u,%u],\"v0\":%u,\"pair\":%u,\"d\":[%u,%u,%u,%u,%u,%u]",
            (unsigned long long)T.seq++, k, fn, vbl, (uint32_t)(2 * ps2k_now()), a[0], a[1], a[2], a[3], v0,
            pair, d[0], d[1], d[2], d[3], d[4], d[5]);
    if (ra_name) {
        fputs(",\"ra_name\":", T.f);
        json_str(T.f, ra_name);
    }
    if (ra) {
#ifdef _WIN32
        extern char __ImageBase;     /* COFF: the image base */
        fprintf(T.f, ",\"ra_rva\":%lu", (unsigned long)((uintptr_t)ra - (uintptr_t)&__ImageBase));
#else
        fprintf(T.f, ",\"ra_host\":%lu", (unsigned long)(uintptr_t)ra);
#endif
    }
    if (src)
        fprintf(T.f, ",\"src\":\"%s\"", src);
    if (extra)
        fputs(extra, T.f);
    fputs("}\n", T.f);
    T.st.records++;
}

static int cur_tid(void)
{
    int t;
    if (ps2k_in_handler())
        return 0;
    t = ps2k_get_thread_id();
    return (t > 0 && t < MAX_TID) ? t : 0;
}

/* ------------------------------------------------------------ synthetic ticks */
/* Which loop flipped: the thread that last blocked on the vsync semaphore
 * (the flipping thread waited in WaitVsyncCount_15de90 just before).  Main
 * thread (id 1): MainLoop_1c2c10, or MoviePlayModal_267c60 while a movie is
 * open outside the title overlay (heuristic until GfxEndFrame is wrapped:
 * the title's background movie draws inside the main loop). */
static const char *loop_name(void)
{
    if (T.last_vsync_tid > 1)
        return "LoadingScreenThread_343510";
    if (T.movie_active && rd_ps2_or0(A_OVERLAY) != 2)
        return "MoviePlayModal_267c60";
    return "MainLoop_1c2c10";
}

static void mem_tick_poll(void)
{
    uint32_t ctx, flip, db, e[6], r[6], pair;
    if (!T.open || !T.cfg.mem_ticks || T.wrapped[RG_TIMING_GfxEndFrame])
        return;
    if (rd_ps2(A_DRAWCTX, &ctx) != 0 || !ctx || rd_host(ctx + CTX_FLIP, &flip) != 0)
        return;
    if (T.have_flip && flip == T.last_flip)
        return;
    if (!T.have_flip) {
        T.have_flip = 1;
        T.last_flip = flip;
        if (flip == 0)
            return;             /* baseline: no flip yet */
    }
    T.last_flip = flip;
    db = rd_host_or0(ctx + CTX_DB);
    e[0] = 0;                   /* T0_COUNT: guest code costs no virtual time */
    e[1] = 0;                   /* VIF1 time sample */
    e[2] = db ? rd_host_or0(db + 0x2C) : 0;
    e[3] = db ? rd_host_or0(db + 0x28) : 0;
    e[4] = rd_host_or0(ctx + CTX_F18);
    e[5] = rd_host_or0(ctx + CTX_3D2C);
    r[0] = rd_host_or0(ctx + CTX_FB);
    r[1] = flip;
    r[2] = rd_host_or0(ctx + CTX_LATE);
    r[3] = db ? rd_host_or0(db + 0x24) : 0;
    r[4] = rd_host_or0(ctx + CTX_DEPTH_ON);
    r[5] = rd_host_or0(ctx + CTX_DEPTH_Z);
    pair = 0x80000000u | T.next_pair++;
    {
        uint32_t a[4] = {to_ps2(ctx), 0, 0, 0};
        const char *ln = loop_name();
        rec("entry", "GfxEndFrame", flip, a, 0, pair, e, ln, NULL, "mem", NULL);
        rec("ret", "GfxEndFrame", flip, NULL, 0, pair, r, ln, NULL, "mem", NULL);
    }
    T.st.mem_ticks++;
}

/* ------------------------------------------------------------ per VBlank */
static void mem_state(uint32_t vbl)
{
    uint32_t ctx = rd_ps2_or0(A_DRAWCTX), db = ctx ? rd_host_or0(ctx + CTX_DB) : 0;
    uint32_t scene = rd_ps2_or0(A_SCENE);
    uint32_t m[10];
    m[0] = db ? rd_host_or0(db + 0x24) : 0;                 /* interval */
    m[1] = db ? rd_host_or0(db + 0x28) : 0;                 /* sync */
    m[2] = rd_ps2_or0(A_GAMEMODE);
    m[3] = rd_ps2_or0(A_PHASE);
    m[4] = rd_ps2_or0(A_OVERLAY);
    m[5] = scene ? rd_host_or0(scene + SCENE_TS + 0x14) : 0;  /* locked | susp << 8 */
    m[6] = rd_ps2_or0(A_SYSMODE);
    m[7] = rd_ps2_or0(A_PAUSESTEP);
    m[8] = rd_ps2_or0(A_TASKDEPTH);
    m[9] = scene ? rd_host_or0(scene + SCENE_TS + 0x0C) : 0;  /* multiplier (f32) */
    if (T.have_mem && !memcmp(m, T.mem, sizeof m))
        return;
    T.have_mem = 1;
    memcpy(T.mem, m, sizeof m);
    {
        uint32_t a[4] = {m[6], m[7], m[8], m[9]};
        char x[96];
        snprintf(x, sizeof x, ",\"x\":{\"db\":%u,\"scene\":%u}", db ? 1u : 0u, scene ? 1u : 0u);
        rec("entry", "MemState", vbl, a, 0, 0, m, NULL, NULL, "mem", x);
    }
    T.st.mem_states++;
}

int rg_timing_vblank(uint64_t field)
{
    uint32_t vbl, d[6];
    if (!T.open)
        return 0;
    (void)field;
    mem_tick_poll();
    vbl = cur_vbl();
    mem_state(vbl);
    if (!T.wrapped[RG_TIMING_VblankStart]) {
        const rg_timing_site *s = &k_rg_timing_sites[RG_TIMING_VblankStart];
        char x[96];
        int i;
        for (i = 0; i < 6; i++)
            d[i] = i < s->nent ? dump_word(&s->ent[i], NULL) : 0;
        snprintf(x, sizeof x, ",\"x\":{\"vsw\":%u,\"vst\":%d}", T.vsync_waits, T.last_vsync_tid);
        rec("entry", "VblankStart", vbl, NULL, 0, 0, d, NULL, NULL, NULL, x);
    }
    T.vsync_waits = 0;
    /* the vsync semaphore id is created at boot; re-read it each VBlank */
    {
        uint32_t s;
        if (rd_ps2(A_VSYNC_SEMA, &s) == 0)
            T.vsync_sema = (int32_t)s;
    }
    if (!T.st.vblanks)
        T.st.first_vbl = vbl;
    T.st.last_vbl = vbl;
    T.st.vblanks++;
    if (T.cfg.stop_vbl && vbl >= T.cfg.stop_vbl && !T.stopped) {
        T.stopped = 1;
        return 1;
    }
    return 0;
}

/* ------------------------------------------------------------ wrapper API */
void rg_timing_enter(int site, unsigned flags, const void *ra, uint32_t a0, uint32_t a1, uint32_t a2,
                     uint32_t a3, uint32_t f12)
{
    const rg_timing_site *s;
    int tid, dp;
    frame *fr, tmp;
    if (!T.open || site <= 0 || site >= RG_TIMING_NSITES)
        return;
    s = &k_rg_timing_sites[site];
    T.wrapped[site] = 1;
    T.st.wrapped_calls++;
    if (site != RG_TIMING_GfxEndFrame)
        mem_tick_poll();
    tid = cur_tid();
    dp = T.depth[tid]++;
    fr = (T.stk && dp < MAX_DEPTH) ? &T.stk[tid][dp] : &tmp;
    fr->site = site;
    fr->flags = flags;
    fr->a[0] = a0;
    fr->a[1] = a1;
    fr->a[2] = a2;
    fr->a[3] = a3;
    fr->f12 = f12;
    fr->ra = ra;
    if (!(s->flags & RG_TS_ENTRY))
        return;
    if (s->skip_zero_arg >= 0 && s->skip_zero_arg < 4 && fr->a[s->skip_zero_arg] == 0)
        return;
    {
        uint32_t a[4], d[6];
        int i;
        for (i = 0; i < 4; i++)
            a[i] = (flags & (1u << i)) ? to_ps2(fr->a[i]) : fr->a[i];
        for (i = 0; i < 6; i++)
            d[i] = i < s->nent ? dump_word(&s->ent[i], fr) : 0;
        rec("entry", s->name, cur_vbl(), a, 0, (uint32_t)(tid << 8 | (dp & 0xFF)), d, NULL, ra, NULL, NULL);
    }
}

void rg_timing_leave(int site, unsigned flags, uint32_t v0)
{
    const rg_timing_site *s;
    int tid, dp;
    frame *fr = NULL, none;
    if (!T.open || site <= 0 || site >= RG_TIMING_NSITES)
        return;
    s = &k_rg_timing_sites[site];
    tid = cur_tid();
    dp = T.depth[tid] - 1;
    if (dp >= 0) {
        T.depth[tid] = dp;
        if (T.stk && dp < MAX_DEPTH && T.stk[tid][dp].site == site)
            fr = &T.stk[tid][dp];
    }
    if (!fr) {
        memset(&none, 0, sizeof none);
        none.site = site;
        fr = &none;
    }
    if (!(s->flags & RG_TS_RET))
        return;
    {
        uint32_t a[4], d[6];
        int i;
        for (i = 0; i < 4; i++)
            a[i] = (fr->flags & (1u << i)) ? to_ps2(fr->a[i]) : fr->a[i];
        for (i = 0; i < 6; i++)
            d[i] = i < s->nret ? dump_word(&s->ret[i], fr) : 0;
        rec("ret", s->name, cur_vbl(), a, (flags & RG_TIMING_RETPTR) ? to_ps2(v0) : v0,
            (uint32_t)(tid << 8 | ((dp < 0 ? 0 : dp) & 0xFF)), d, NULL, fr->ra, NULL, NULL);
    }
}

/* ------------------------------------------------------------ built-in sources */
static void on_vblank(int which, uint64_t field, void *user)
{
    (void)user;
    if (which != PS2K_VBLANK_START || !T.open)
        return;
    if (rg_timing_vblank(field))
        rg_runtime_request_quit();
}

static void on_ktrace(const ps2k_trace_rec *r, void *user)
{
    (void)user;
    if (r->type == PS2K_TR_SEMA_WAIT && T.vsync_sema > 0 && r->a == T.vsync_sema) {
        T.last_vsync_tid = r->b;
        T.vsync_waits++;
        T.st.vsync_waits++;
    }
}

static void on_ovl(void *user, int ovl, int done)
{
    const rg_ovl_desc *dsc = rg_ovl_desc_at(ovl);
    uint32_t a[4] = {0, 0, 0, 0}, d[6] = {0, 0, 0, 0, 0, 0};
    (void)user;
    if (T.wrapped[RG_TIMING_OverlayLoad] || !T.open)
        return;
    mem_tick_poll();
    a[0] = dsc ? (uint32_t)dsc->index : (uint32_t)ovl;
    d[0] = rd_ps2_or0(A_OVERLAY);
    d[1] = rd_ps2_or0(A_SYSMODE);
    if (!done) {
        T.ovl_pair = 0x80000000u | T.next_pair++;
        rec("entry", "OverlayLoad", cur_vbl(), a, 0, T.ovl_pair, d, NULL, NULL, "ovl", NULL);
        T.st.overlay_loads++;
    } else {
        rec("ret", "OverlayLoad", cur_vbl(), a, 0, T.ovl_pair, d, NULL, NULL, "ovl", NULL);
    }
}

static void on_cd(void *user, uint32_t lsn, uint32_t sectors, void *buf, int pattern)
{
    uint32_t a[4];
    (void)user;
    if (T.wrapped[RG_TIMING_sceCdRead] || !T.open)
        return;
    mem_tick_poll();
    a[0] = lsn;
    a[1] = sectors;
    a[2] = to_ps2((uint32_t)(uintptr_t)buf);
    a[3] = (uint32_t)pattern;
    rec("entry", "sceCdRead", cur_vbl(), a, 0, 0, NULL, NULL, NULL, "sce", NULL);
    T.st.cd_reads++;
}

/* native file service read (docs/NATIVE-FS.md): "FsRead", a = [buf, 0, 0, 0],
 * d = [offset lo, offset hi, length, file size, bytes from the file, handle],
 * "file" = the data/ path.  Counted with the CD reads (cd_reads). */
static void on_fs(void *user, int h, const char *path, int64_t off, int64_t len, int64_t got,
                  const void *buf)
{
    uint32_t a[4] = {0, 0, 0, 0}, d[6];
    char extra[300];
    int64_t size = rg_fs_size(h);
    (void)user;
    if (!T.open)
        return;
    mem_tick_poll();
    a[0] = to_ps2((uint32_t)(uintptr_t)buf);
    d[0] = (uint32_t)off;
    d[1] = (uint32_t)((uint64_t)off >> 32);
    d[2] = (uint32_t)len;
    d[3] = (uint32_t)size;
    d[4] = (uint32_t)got;
    d[5] = (uint32_t)h;
    snprintf(extra, sizeof extra, ",\"file\":\"%s\"", path ? path : "?");
    rec("entry", "FsRead", cur_vbl(), a, 0, 0, d, NULL, NULL, "fs", extra);
    T.st.cd_reads++;
}

static void on_pad(void *user, int port, int slot, const unsigned char *data, int len)
{
    uint32_t a[4] = {(uint32_t)port, (uint32_t)slot, 0, 0}, d[6] = {0, 0, 0, 0, 0, 0};
    int i;
    (void)user;
    if (!T.open || !T.cfg.pad_reads)
        return;
    mem_tick_poll();
    for (i = 0; i < len && i < 24; i++)
        d[i / 4] |= (uint32_t)data[i] << (8 * (i % 4));
    rec("ret", "scePadRead", cur_vbl(), a, (uint32_t)len, (uint32_t)(cur_tid() << 8), d, NULL, NULL, "sce", NULL);
    T.st.pad_reads++;
}

static void on_movie(void *user, int ev, const char *path, int active)
{
    uint32_t a[4] = {(uint32_t)active, 0, 0, 0};
    (void)user;
    if (!T.open)
        return;
    if (ev == RG_MOVIE_G_EV_OPEN) {
        T.movie_active = 1;
        if (T.wrapped[RG_TIMING_MovieOpen])
            return;
        mem_tick_poll();
        {
            char x[300];
            char esc[256];
            size_t j = 0;
            const char *p = path ? path : "";
            for (; *p && j < sizeof esc - 7; p++) {
                unsigned char c = (unsigned char)*p;
                if (c == '"' || c == '\\') {
                    esc[j++] = '\\';
                    esc[j++] = (char)c;
                } else if (c >= 0x20 && c < 0x7F) {
                    esc[j++] = (char)c;
                }
            }
            esc[j] = 0;
            snprintf(x, sizeof x, ",\"path\":\"%s\"", esc);
            rec("entry", "MovieOpen", cur_vbl(), a, 0, 0, NULL, NULL, NULL, "movie", x);
        }
    } else {
        T.movie_active = 0;
        if (T.wrapped[RG_TIMING_MovieShutdown])
            return;
        mem_tick_poll();
        rec("entry", "MovieShutdown", cur_vbl(), a, 0, 0, NULL, NULL, NULL, "movie", NULL);
    }
    T.st.movie_events++;
}

/* ------------------------------------------------------------ setup */
int rg_timing_site_count(void) { return RG_TIMING_NSITES - 1; }

const rg_timing_site *rg_timing_site_at(int id)
{
    return (id > 0 && id < RG_TIMING_NSITES) ? &k_rg_timing_sites[id] : NULL;
}

int rg_timing_site_find(const char *name)
{
    int i;
    for (i = 1; name && i < RG_TIMING_NSITES; i++)
        if (!strcmp(k_rg_timing_sites[i].name, name) || !strcmp(k_rg_timing_sites[i].func, name))
            return i;
    return 0;
}

void rg_timing_default_config(rg_timing_config *c)
{
    memset(c, 0, sizeof *c);
    c->mem_ticks = 1;
    c->pad_reads = 1;
}

int rg_timing_config_from_env(rg_timing_config *c)
{
    const char *e = getenv("RG_TIMING");
    char *end;
    if (!e || !*e)
        return 0;
    c->out = e;
    if ((e = getenv("RG_TIMING_STOP_VBL")) && *e) {
        c->stop_vbl = (uint32_t)strtoul(e, &end, 0);
        if (*end) {
            fprintf(stderr, "rg_timing: bad RG_TIMING_STOP_VBL '%s'\n", e);
            return -1;
        }
    }
    if ((e = getenv("RG_TIMING_MEMTICKS")) && *e)
        c->mem_ticks = atoi(e) != 0;
    if ((e = getenv("RG_TIMING_PADREADS")) && *e)
        c->pad_reads = atoi(e) != 0;
    return 1;
}

int rg_timing_open(const rg_timing_config *c)
{
    int i;
    if (T.open)
        rg_timing_close("reopened");
    if (!c || !c->out) {
        fprintf(stderr, "rg_timing: no output path\n");
        return -1;
    }
    {
        frame (*stk)[MAX_DEPTH] = T.stk;
        memset(&T, 0, sizeof T);
        T.stk = stk;
    }
    T.cfg = *c;
    T.f = fopen(c->out, "w");
    if (!T.f) {
        fprintf(stderr, "rg_timing: cannot write %s\n", c->out);
        return -1;
    }
    setvbuf(T.f, NULL, _IOFBF, 1 << 16);
    if (!T.stk)
        T.stk = calloc(MAX_TID, sizeof *T.stk);
    T.last_vsync_tid = 1;
    fputs("{\"t\":\"meta\",\"hooks\":[\"timing\"],\"side\":\"port\",\"sites\":{", T.f);
    for (i = 1; i < RG_TIMING_NSITES; i++)
        fprintf(T.f, "%s\"%d\":\"%s\"", i > 1 ? "," : "", i, k_rg_timing_sites[i].name);
    fputs("},\"input\":", T.f);
    if (c->input)
        json_str(T.f, c->input);
    else
        fputs("null", T.f);
    fprintf(T.f, ",\"clock\":\"2*ps2k_now\",\"mem_ticks\":%d,\"pad_reads\":%d,\"stop_vbl\":%u}\n", c->mem_ticks,
            c->pad_reads, c->stop_vbl);
    T.open = 1;
    rg_timing_on = 1;
    return 0;
}

int rg_timing_is_open(void) { return T.open; }

int rg_timing_attach(void)
{
    if (T.attached)
        return 0;
    T.obs = ps2k_add_vblank_observer(on_vblank, NULL);
    if (T.obs < 0) {
        fprintf(stderr, "rg_timing: no free VBlank observer slot\n");
        return -1;
    }
    ps2k_set_trace_hook(on_ktrace, NULL);
    rg_ovl_set_load_hook(on_ovl, NULL);
    sceCdHleSetReadHook(on_cd, NULL);
    rg_fs_add_read_hook(on_fs, NULL);
    scePadHleSetReadHook(on_pad, NULL);
    rg_movie_g_set_hook(on_movie, NULL);
    T.attached = 1;
    return 0;
}

void rg_timing_detach(void)
{
    if (!T.attached)
        return;
    ps2k_remove_vblank_observer(T.obs);
    ps2k_set_trace_hook(NULL, NULL);
    rg_ovl_set_load_hook(NULL, NULL);
    sceCdHleSetReadHook(NULL, NULL);
    rg_fs_remove_read_hook(on_fs, NULL);
    scePadHleSetReadHook(NULL, NULL);
    rg_movie_g_set_hook(NULL, NULL);
    T.attached = 0;
}

void rg_timing_close(const char *reason)
{
    if (!T.open)
        return;
    fprintf(T.f, "{\"t\":\"end\",\"reason\":");
    json_str(T.f, reason ? reason : "");
    fprintf(T.f, ",\"records\":%llu,\"vblanks\":%llu,\"mem_ticks\":%llu,\"wrapped_calls\":%llu}\n",
            (unsigned long long)T.st.records, (unsigned long long)T.st.vblanks,
            (unsigned long long)T.st.mem_ticks, (unsigned long long)T.st.wrapped_calls);
    fclose(T.f);
    T.f = NULL;
    T.open = 0;
    rg_timing_on = 0;
}

const rg_timing_stats *rg_timing_get_stats(void) { return &T.st; }

/* tests (tests/trace/timing_tests.c): feed one kernel trace record */
void rg_timing_test_ktrace(const ps2k_trace_rec *r) { on_ktrace(r, NULL); }
