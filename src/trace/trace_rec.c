/* SPDX-License-Identifier: CC0-1.0
 * The recorder: one sample per VBLANK_START, rows in tools/trace/trace.py's
 * TSV format (docs/TRACE-PORT.md "Format"). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_trace.h"

static struct {
    int open;
    rg_trace_config cfg;
    rg_trace_regions rs;
    FILE *out;
    uint8_t *buf;
    size_t bufcap;
    uint32_t *keys;
    int nkeys;
    rg_trace_stats st;
    int have_mode, have_ovl;
    int32_t mode, ovl;
    int fault_done;
    int key_noted; /* -1 none, 0 kernel, 1 game */
} T;

void rg_trace_default_config(rg_trace_config *c)
{
    memset(c, 0, sizeof *c);
    c->vbl_addr = RG_TRACE_GAME_VBL_ADDR;
    c->every = 1;
    c->input_lead = 1;
    c->fault_xor = 1;
}

static int env_u32(const char *name, uint32_t *v)
{
    const char *s = getenv(name);
    if (!s || !*s)
        return 0;
    char *e;
    unsigned long long x = strtoull(s, &e, 0);
    if (*e || x > 0xFFFFFFFFull) {
        fprintf(stderr, "rg_trace: bad %s=%s\n", name, s);
        return -1;
    }
    *v = (uint32_t)x;
    return 1;
}

static const char *env_s(const char *name)
{
    const char *s = getenv(name);
    return s && *s ? s : NULL;
}

int rg_trace_config_from_env(rg_trace_config *c)
{
    uint32_t v;
    int r;
    c->out = env_s("RG_TRACE_OUT");
    if (env_s("RG_TRACE_REGIONS")) c->regions = env_s("RG_TRACE_REGIONS");
    if (env_s("RG_TRACE_PORTCFG")) c->portcfg = env_s("RG_TRACE_PORTCFG");
    if (env_s("RG_TRACE_INPUT")) c->input = env_s("RG_TRACE_INPUT");
    if (env_s("RG_TRACE_KEYS")) c->keys = env_s("RG_TRACE_KEYS");
#define U32(name, field)                     \
    if ((r = env_u32(name, &v)) < 0)         \
        return -1;                           \
    if (r)                                   \
        c->field = v;
    U32("RG_TRACE_EVERY", every)
    U32("RG_TRACE_STOP_VBL", stop_vbl)
    U32("RG_TRACE_FRAMES", stop_frames)
    U32("RG_TRACE_VBL_ADDR", vbl_addr)
    U32("RG_TRACE_VBL_KERNEL", vbl_kernel)
    U32("RG_TRACE_PS2PTRS", ps2_pointers)
    U32("RG_TRACE_INPUT_LEAD", input_lead)
#undef U32
    const char *f = env_s("RG_TRACE_FAULT");
    if (f) {
        unsigned long long a, b, x = 1;
        char *e;
        a = strtoull(f, &e, 0);
        if (*e != ':') goto bad;
        b = strtoull(e + 1, &e, 0);
        if (*e == ':')
            x = strtoull(e + 1, &e, 0);
        if (*e || a > 0xFFFFFFFFull || b > 0xFFFFFFFFull || !x || x > 255) goto bad;
        c->fault = 1;
        c->fault_addr = (uint32_t)a;
        c->fault_vbl = (uint32_t)b;
        c->fault_xor = (uint8_t)x;
    }
    if (!c->every)
        c->every = 1;
    return c->out ? 1 : 0;
bad:
    fprintf(stderr, "rg_trace: bad RG_TRACE_FAULT=%s (want addr:vbl[:xor])\n", f);
    return -1;
}

static int cmp_u32(const void *a, const void *b)
{
    uint32_t x = *(const uint32_t *)a, y = *(const uint32_t *)b;
    return x < y ? -1 : x > y;
}

static int load_keys(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "rg_trace: cannot open keys file %s\n", path);
        return -1;
    }
    int cap = 1024;
    T.keys = (uint32_t *)malloc((size_t)cap * sizeof *T.keys);
    char line[128];
    while (T.keys && fgets(line, sizeof line, f)) {
        if (line[0] == '#')
            continue;
        char *e;
        unsigned long v = strtoul(line, &e, 0);
        if (e == line)
            continue;
        if (T.nkeys == cap) {
            cap *= 2;
            uint32_t *k = (uint32_t *)realloc(T.keys, (size_t)cap * sizeof *k);
            if (!k)
                break;
            T.keys = k;
        }
        T.keys[T.nkeys++] = (uint32_t)v;
    }
    fclose(f);
    if (!T.keys)
        return -1;
    qsort(T.keys, (size_t)T.nkeys, sizeof *T.keys, cmp_u32);
    return 0;
}

static char *dup(const char *s)
{
    if (!s)
        return NULL;
    size_t n = strlen(s) + 1;
    char *d = (char *)malloc(n);
    if (d)
        memcpy(d, s, n);
    return d;
}

static void free_cfg_strings(void)
{
    free((char *)T.cfg.out);
    free((char *)T.cfg.regions);
    free((char *)T.cfg.portcfg);
    free((char *)T.cfg.input);
    free((char *)T.cfg.keys);
}

static void reset(void)
{
    if (T.out)
        fclose(T.out);
    rg_trace_regions_free(&T.rs);
    free(T.buf);
    free(T.keys);
    free_cfg_strings();
    memset(&T, 0, sizeof T);
}

int rg_trace_open(const rg_trace_config *c)
{
    char err[512];
    if (T.open)
        rg_trace_close("reopened");
    reset();
    if (!c->out || !c->regions) {
        fprintf(stderr, "rg_trace: need an output path and a region file (RG_TRACE_OUT, RG_TRACE_REGIONS)\n");
        return -1;
    }
    T.cfg = *c;
    T.cfg.out = dup(c->out);
    T.cfg.regions = dup(c->regions);
    T.cfg.portcfg = dup(c->portcfg);
    T.cfg.input = dup(c->input);
    T.cfg.keys = dup(c->keys);
    if (!T.cfg.every)
        T.cfg.every = 1;
    if (rg_trace_regions_load(&T.rs, c->regions, err, sizeof err) != 0 ||
        (c->portcfg && rg_trace_portcfg_load(&T.rs, c->portcfg, err, sizeof err) != 0)) {
        fprintf(stderr, "rg_trace: %s\n", err);
        reset();
        return -1;
    }
    if (c->keys && load_keys(c->keys) != 0) {
        reset();
        return -1;
    }
    size_t mx = 64;
    for (int i = 0; i < T.rs.n; i++) {
        size_t m = rg_trace_region_max_bytes(&T.rs.r[i]);
        if (m > mx)
            mx = m;
    }
    T.buf = (uint8_t *)malloc(mx);
    T.bufcap = mx;
    T.out = fopen(c->out, "w");
    if (!T.buf || !T.out) {
        fprintf(stderr, "rg_trace: cannot open %s\n", c->out);
        reset();
        return -1;
    }
    T.key_noted = -1;
    FILE *o = T.out;
    fprintf(o, "# port\trg_trace\n");
    fprintf(o, "# regions\t%s\n", c->regions);
    if (c->portcfg)
        fprintf(o, "# portcfg\t%s\n", c->portcfg);
    fprintf(o, "# input\t%s\n", c->input ? c->input : "-");
    fprintf(o, "# ptrmode\t%s\n", c->ps2_pointers ? "ps2 (stored pointers are PS2 addresses)"
                                                  : "host (stored pointers translated through the address map)");
    if (c->keys)
        fprintf(o, "# keys\t%s\t%d vbls\n", c->keys, T.nkeys);
    else
        fprintf(o, "# every\t%u\n", T.cfg.every);
    if (c->fault)
        fprintf(o, "# fault-armed\t0x%08X\tvbl %u\txor 0x%02X\n", c->fault_addr, c->fault_vbl, c->fault_xor);
    fprintf(o, "# symbols\t%d\n", rg_trace_symbol_count());
    fflush(o);
    T.open = 1;
    return 0;
}

int rg_trace_is_open(void) { return T.open; }

uint32_t rg_trace_read_vbl(uint32_t fallback, int *from_game)
{
    uint32_t v;
    uint8_t b[4];
    const rg_trace_config *c = T.open ? &T.cfg : NULL;
    uint32_t addr = c ? c->vbl_addr : RG_TRACE_GAME_VBL_ADDR;
    int kernel = c ? c->vbl_kernel : 0;
    if (!kernel && rg_trace_read(addr, b, 4, NULL) == 0) {
        v = b[0] | b[1] << 8 | b[2] << 16 | (uint32_t)b[3] << 24;
        if (from_game)
            *from_game = 1;
        return v;
    }
    if (from_game)
        *from_game = 0;
    return fallback;
}

static int wanted(uint32_t vbl)
{
    if (T.keys) {
        int lo = 0, hi = T.nkeys - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (T.keys[mid] == vbl)
                return 1;
            if (T.keys[mid] < vbl)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return 0;
    }
    return vbl % T.cfg.every == 0;
}

static int read_s32(uint32_t a, int32_t *v)
{
    uint8_t b[4];
    if (rg_trace_read(a, b, 4, NULL) != 0)
        return 0;
    *v = (int32_t)(b[0] | b[1] << 8 | b[2] << 16 | (uint32_t)b[3] << 24);
    return 1;
}

int rg_trace_sample(uint64_t frame, uint64_t cycle, uint32_t kernel_vbl)
{
    if (!T.open)
        return 0;
    FILE *o = T.out;
    int game = 0;
    uint32_t vbl = rg_trace_read_vbl(kernel_vbl, &game);
    if (game != T.key_noted) {
        if (game)
            fprintf(o, "# key\t%llu\tgame vbl counter @0x%08X\n", (unsigned long long)frame, T.cfg.vbl_addr);
        else
            fprintf(o, "# key\t%llu\tkernel VBlank count (game counter @0x%08X %s)\n", (unsigned long long)frame,
                    T.cfg.vbl_addr, T.cfg.vbl_kernel ? "ignored: RG_TRACE_VBL_KERNEL" : "unmapped");
        T.key_noted = game;
    }
    T.st.vbl_from_game = game;
    if (!T.st.samples)
        T.st.first_vbl = vbl;
    T.st.last_vbl = vbl;
    T.st.samples++;

    /* deliberate-fault control (docs/TRACE-PORT.md "Controls") */
    if (T.cfg.fault && !T.fault_done && vbl >= T.cfg.fault_vbl) {
        uint8_t *p = (uint8_t *)rg_trace_host_ptr(T.cfg.fault_addr, NULL);
        if (p) {
            *p ^= T.cfg.fault_xor;
            fprintf(o, "# fault\t%llu\t0x%08X ^= 0x%02X\tvbl %u\n", (unsigned long long)frame, T.cfg.fault_addr,
                    T.cfg.fault_xor, vbl);
        } else {
            fprintf(o, "# fault\t%llu\t0x%08X unmapped: not applied\n", (unsigned long long)frame, T.cfg.fault_addr);
        }
        T.fault_done = 1;
    }

    /* the harness's event lines, from the game's own variables when mapped */
    int32_t v;
    if (read_s32(RG_TRACE_GAMEMODE_ADDR, &v) && (!T.have_mode || v != T.mode)) {
        fprintf(o, "# gamemode-change\t%llu\t%d\tvbl %u\n", (unsigned long long)frame, v, vbl);
        T.mode = v;
        T.have_mode = 1;
    }
    if (read_s32(RG_TRACE_OVERLAY_ADDR, &v) && (!T.have_ovl || v != T.ovl)) {
        fprintf(o, "# overlay\t%llu\t%u \n", (unsigned long long)frame, (uint32_t)v);
        T.ovl = v;
        T.have_ovl = 1;
    }

    if (wanted(vbl)) {
        char hx[17], why[160];
        fprintf(o, "%llu\t@cycle\t%08x\n", (unsigned long long)frame, (uint32_t)cycle);
        fprintf(o, "%llu\t@vbl\t%u\n", (unsigned long long)frame, vbl);
        T.st.rows += 2;
        for (int i = 0; i < T.rs.n; i++) {
            rg_trace_region *rg = &T.rs.r[i];
            int untr = 0;
            int n = rg_trace_region_bytes(rg, T.cfg.ps2_pointers, T.buf, T.bufcap, why, sizeof why, &untr);
            T.st.untranslated += (uint64_t)untr;
            if (n < 0) {
                T.st.unmapped_skips++;
                if (!rg->noted) {
                    fprintf(o, "# unmapped\t%llu\t%s\t%s\n", (unsigned long long)frame, rg->name, why);
                    rg->noted = 1;
                }
                continue;
            }
            if ((why[0] || untr) && !(rg->noted & 2)) {
                fprintf(o, "# note\t%llu\t%s\t%s\n", (unsigned long long)frame, rg->name,
                        why[0] ? why : "pointer value outside the address map (left as a host value)");
                rg->noted |= 2;
            }
            rg_trace_hash_hex(hx, T.buf, (size_t)n);
            fprintf(o, "%llu\t%s\t%s\n", (unsigned long long)frame, rg->name, hx);
            T.st.rows++;
        }
        T.st.emitted++;
        fflush(o);
    }

    char reason[96];
    if (T.cfg.stop_vbl && vbl >= T.cfg.stop_vbl) {
        snprintf(reason, sizeof reason, "stop-vbl: frame %llu vbl %u", (unsigned long long)frame, vbl);
        rg_trace_close(reason);
        return 1;
    }
    if (T.cfg.stop_frames && T.st.samples >= T.cfg.stop_frames) {
        snprintf(reason, sizeof reason, "frames: frame %llu", (unsigned long long)frame);
        rg_trace_close(reason);
        return 1;
    }
    return 0;
}

void rg_trace_close(const char *reason)
{
    if (!T.open)
        return;
    fprintf(T.out, "# stop\t%s\n", reason ? reason : "closed");
    fprintf(T.out, "# samples\t%llu\trejected\t0\n", (unsigned long long)T.st.samples);
    fprintf(T.out, "# port-stats\temitted %llu\trows %llu\tunmapped-skips %llu\tuntranslated %llu\n",
            (unsigned long long)T.st.emitted, (unsigned long long)T.st.rows, (unsigned long long)T.st.unmapped_skips,
            (unsigned long long)T.st.untranslated);
    fclose(T.out);
    T.out = NULL;
    T.open = 0;
}

const rg_trace_stats *rg_trace_get_stats(void) { return &T.st; }
