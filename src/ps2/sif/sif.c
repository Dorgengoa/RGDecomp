/* SPDX-License-Identifier: CC0-1.0 */
/* SIF HLE core: registers, events, SIF DMA, RPC registry/calls, commands. See sif.h. */
#include "sif.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iop.h"
#include "rg_iop.h" /* census counters (docs/NATIVE-IOP.md) */

/* ---- state -------------------------------------------------------------- */
typedef struct sev {
    uint64_t due, seq;
    sif_event_fn fn;
    void *arg;
} sev;

typedef struct ee_srv {
    uint32_t sid;
    sif_ee_sink_fn fn;
    void *user;
} ee_srv;

typedef struct cmd_h {
    uint32_t cid;
    sif_cmd_fn fn;
    void *user;
} cmd_h;

#define MAX_EE_SERVERS 16
#define MAX_CMD 64
#define DMA_RING 64
#define FNO_STATS 512
#define MAX_TICKETS 1024

static struct {
    sif_config cfg;
    sif_hooks hooks;
    int have_hooks;
    uint64_t clock; /* internal clock */

    uint32_t mscom, smcom, msflag, smflag, ctrl;
    uint32_t sreg[32];

    sev *ev;
    int nev, cap;
    uint64_t ev_seq;
    int delivering;

    uint32_t dma_next;
    struct { uint32_t id; uint64_t done; } dma[DMA_RING];

    sif_server_info srv[SIF_MAX_SERVERS];
    int nsrv;
    ee_srv ees[MAX_EE_SERVERS];
    int nees;
    cmd_h ee_cmd[MAX_CMD], iop_cmd[MAX_CMD];
    int nee_cmd, niop_cmd;

    uint32_t ticket_next;
    uint8_t busy[MAX_TICKETS]; /* indexed by ticket % MAX_TICKETS */

    sif_report_fn rep;
    void *rep_user;
    uint32_t rep_count[SIF_REP_KINDS];

    sif_call_rec log[SIF_CALL_LOG];
    int nlog;
    struct { uint32_t sid, fno, n; } fs[FNO_STATS];
    int nfs;

    sif_stats st;
    uint32_t bad_bind[16];
    int nbad;
    void (*trace)(const char *, void *);
    void *trace_user;
} S;

static uint64_t clock_now(void)
{
    return S.have_hooks && S.hooks.now ? S.hooks.now(S.hooks.user) : S.clock;
}
static uint64_t iop_clock(void) { return clock_now(); }

uint64_t sif_now(void) { return clock_now(); }
const sif_config *sif_get_config(void) { return &S.cfg; }

static void tracef(const char *fmt, ...)
{
    if (!S.trace)
        return;
    char line[256];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(line, sizeof line, fmt, ap);
    va_end(ap);
    S.trace(line, S.trace_user);
}

static void reportf(int kind, uint32_t sid, uint32_t fno, const char *fmt, ...)
{
    char msg[256];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, sizeof msg, fmt, ap);
    va_end(ap);
    if (kind >= 0 && kind < SIF_REP_KINDS)
        S.rep_count[kind]++;
    if (S.rep)
        S.rep(kind, sid, fno, msg, S.rep_user);
    else
        fprintf(stderr, "[sif] %s\n", msg);
}

void sif_set_report(sif_report_fn fn, void *user) { S.rep = fn; S.rep_user = user; }
uint32_t sif_report_count(int kind) { return (kind >= 0 && kind < SIF_REP_KINDS) ? S.rep_count[kind] : 0; }
void sif_set_trace(void (*fn)(const char *, void *), void *user) { S.trace = fn; S.trace_user = user; }
const sif_stats *sif_get_stats(void) { return &S.st; }

void sif_default_config(sif_config *cfg)
{
    memset(cfg, 0, sizeof *cfg);
}

static void iop_report_bridge(const char *msg) { reportf(SIF_REP_BAD_ADDR, 0, 0, "%s", msg); }

void sif_init(const sif_config *cfg)
{
    RG_IOP_HLE("sif_init");
    free(S.ev);
    sif_report_fn rep = S.rep;
    void *rep_user = S.rep_user;
    memset(&S, 0, sizeof S);
    S.rep = rep;
    S.rep_user = rep_user;
    if (cfg)
        S.cfg = *cfg;
    else
        sif_default_config(&S.cfg);
    S.smflag = SIF_STAT_SIFINIT | SIF_STAT_CMDINIT | SIF_STAT_BOOTEND;
    S.dma_next = 1;
    S.ticket_next = 1;
    iop_set_clock(iop_clock);
    iop_set_report(iop_report_bridge);
}

void sif_set_hooks(const sif_hooks *h)
{
    if (h) {
        S.hooks = *h;
        S.have_hooks = 1;
    } else {
        memset(&S.hooks, 0, sizeof S.hooks);
        S.have_hooks = 0;
    }
}

/* ---- registers ------------------------------------------------------------ */
uint32_t sif_reg_get(uint32_t reg)
{
    RG_IOP_HLE("sif_reg_get");
    if (reg & SIF_SREG_BASE)
        return S.sreg[reg & 31u];
    switch (reg) {
    case SIF_REG_MSCOM: return S.mscom;
    case SIF_REG_SMCOM: return S.smcom;
    case SIF_REG_MSFLAG: return S.msflag;
    case SIF_REG_SMFLAG: return S.smflag;
    case SIF_REG_CTRL: return S.ctrl;
    default: return 0;
    }
}

uint32_t sif_reg_set(uint32_t reg, uint32_t v)
{
    RG_IOP_HLE("sif_reg_set");
    uint32_t old = sif_reg_get(reg);
    if (reg & SIF_SREG_BASE) {
        S.sreg[reg & 31u] = v;
        return old;
    }
    switch (reg) {
    case SIF_REG_MSCOM: S.mscom = v; break;
    case SIF_REG_SMCOM: S.smcom = v; break;
    case SIF_REG_MSFLAG: S.msflag |= v; break;  /* EE sets */
    case SIF_REG_SMFLAG: S.smflag &= ~v; break; /* EE clears */
    case SIF_REG_CTRL: S.ctrl = v; break;
    default: break;
    }
    return old;
}

void sif_iop_set_smflag(uint32_t bits) { S.smflag |= bits; }
int sif_iop_booted(void) { RG_IOP_HLE("sif_iop_booted"); return (S.smflag & SIF_STAT_BOOTEND) != 0; }

/* ---- events ---------------------------------------------------------------- */
int sif_post(uint64_t delay, sif_event_fn fn, void *arg)
{
    RG_IOP_HLE("sif_post");
    if (S.nev == S.cap) {
        int nc = S.cap ? S.cap * 2 : 64;
        sev *n = (sev *)realloc(S.ev, (size_t)nc * sizeof(sev));
        if (!n)
            return -1;
        S.ev = n;
        S.cap = nc;
    }
    uint64_t due = clock_now() + delay;
    /* keep sorted by (due, seq): insert after every element with due <= this one */
    int i = S.nev;
    while (i > 0 && S.ev[i - 1].due > due)
        i--;
    memmove(&S.ev[i + 1], &S.ev[i], (size_t)(S.nev - i) * sizeof(sev));
    S.ev[i].due = due;
    S.ev[i].seq = S.ev_seq++;
    S.ev[i].fn = fn;
    S.ev[i].arg = arg;
    S.nev++;
    if (S.have_hooks && S.hooks.schedule)
        S.hooks.schedule(due, S.hooks.user);
    return 0;
}

static int deliver_until(uint64_t limit)
{
    int n = 0;
    S.delivering++;
    while (S.nev > 0 && S.ev[0].due <= limit) {
        sev e = S.ev[0];
        memmove(&S.ev[0], &S.ev[1], (size_t)(S.nev - 1) * sizeof(sev));
        S.nev--;
        e.fn(e.arg);
        n++;
    }
    S.delivering--;
    return n;
}

int sif_deliver(void) { RG_IOP_HLE("sif_deliver"); return deliver_until(clock_now()); }
int sif_deliver_all(void) { RG_IOP_HLE("sif_deliver_all"); return deliver_until(UINT64_MAX); }
int sif_pending_events(void) { return S.nev; }
uint64_t sif_next_due(void) { return S.nev ? S.ev[0].due : UINT64_MAX; }
int sif_in_delivery(void) { return S.delivering > 0; }

void sif_advance(uint64_t cycles)
{
    RG_IOP_HLE("sif_advance");
    if (S.have_hooks && S.hooks.now)
        return; /* the external clock owns time */
    uint64_t target = S.clock + cycles;
    /* deliver in time order, with the clock at each event's due time */
    while (S.nev > 0 && S.ev[0].due <= target) {
        if (S.ev[0].due > S.clock)
            S.clock = S.ev[0].due;
        deliver_until(S.clock);
    }
    S.clock = target;
}

/* ---- IOP lifecycle ---------------------------------------------------------- */
static void boot_done(void *arg)
{
    (void)arg;
    S.smflag |= SIF_STAT_SIFINIT | SIF_STAT_CMDINIT | SIF_STAT_BOOTEND;
}

void sif_iop_reboot(const char *image)
{
    RG_IOP_HLE("sif_iop_reboot");
    S.smflag &= ~(SIF_STAT_SIFINIT | SIF_STAT_CMDINIT | SIF_STAT_BOOTEND);
    iop_reboot(image);
    /* server buffers lived in IOP RAM that was just cleared: re-reserve them */
    for (int i = 0; i < S.nsrv; i++)
        S.srv[i].buf_iop = S.srv[i].bufsize ? iop_static_alloc(S.srv[i].bufsize) : 0;
    memset(S.sreg, 0, sizeof S.sreg);
    tracef("reboot image='%s'", image ? image : "");
    if (S.cfg.boot_latency == 0)
        boot_done(NULL);
    else
        sif_post(S.cfg.boot_latency, boot_done, NULL);
}

/* ---- DMA -------------------------------------------------------------------- */
uint32_t sif1_dma(const sif_dma_xfer *list, int count)
{
    RG_IOP_HLE("sif1_dma");
    if (!list || count <= 0)
        return 0;
    uint64_t qw = 0;
    for (int i = 0; i < count; i++) {
        uint32_t ph = iop_phys(list[i].addr);
        if (list[i].size && (ph >= IOP_RAM_SIZE || list[i].size > IOP_RAM_SIZE - ph)) {
            reportf(SIF_REP_BAD_ADDR, 0, 0, "SIF1 DMA element %d: IOP dest 0x%08X size 0x%X outside RAM",
                    i, list[i].addr, list[i].size);
            return 0;
        }
    }
    for (int i = 0; i < count; i++) {
        const void *src = (const void *)(uintptr_t)list[i].data;
        if (list[i].size)
            iop_write(list[i].addr, src, list[i].size);
        qw += (list[i].size + 15u) / 16u;
        S.st.dma1_xfers++;
        S.st.dma1_bytes += list[i].size;
        tracef("SIF1 dma ee=0x%08X -> iop=0x%08X size=0x%X mode=0x%X", list[i].data, list[i].addr,
               list[i].size, list[i].mode);
    }
    uint32_t id = S.dma_next++;
    if (S.dma_next == 0)
        S.dma_next = 1;
    S.dma[id % DMA_RING].id = id;
    S.dma[id % DMA_RING].done = clock_now() + S.cfg.dma_setup + qw * S.cfg.dma_cycles_per_qword;
    return id;
}

int sif_dma_stat(uint32_t id)
{
    RG_IOP_HLE("sif_dma_stat");
    if (id == 0 || S.dma[id % DMA_RING].id != id)
        return -1;
    return clock_now() >= S.dma[id % DMA_RING].done ? -1 : 1;
}

void sif0_write(void *ee_dst, const void *src, uint32_t size)
{
    RG_IOP_HLE("sif0_write");
    if (size && ee_dst && src)
        memmove(ee_dst, src, size);
    S.st.sif0_writes++;
    S.st.sif0_bytes += size;
}

/* ---- servers ----------------------------------------------------------------- */
static sif_server_info *srv_find(uint32_t sid)
{
    for (int i = 0; i < S.nsrv; i++)
        if (S.srv[i].sid == sid)
            return &S.srv[i];
    return NULL;
}

int sif_server_register(uint32_t sid, const char *name, uint32_t bufsize, sif_server_fn fn, void *user)
{
    RG_IOP_HLE("sif_server_register");
    sif_server_info *s = srv_find(sid);
    if (!s) {
        if (S.nsrv >= SIF_MAX_SERVERS)
            return -1;
        s = &S.srv[S.nsrv++];
        memset(s, 0, sizeof *s);
    }
    s->sid = sid;
    snprintf(s->name, sizeof s->name, "%s", name ? name : "?");
    if (bufsize != s->bufsize || !s->buf_iop) {
        s->bufsize = bufsize;
        s->buf_iop = bufsize ? iop_static_alloc(bufsize) : 0;
        if (bufsize && !s->buf_iop) {
            reportf(SIF_REP_OTHER, sid, 0, "server 0x%08X: no IOP RAM for a 0x%X buffer", sid, bufsize);
            s->bufsize = 0;
        }
    }
    s->fn = fn;
    s->user = user;
    return 0;
}

int sif_server_unregister(uint32_t sid)
{
    sif_server_info *s = srv_find(sid);
    if (!s)
        return -1;
    int i = (int)(s - S.srv);
    memmove(&S.srv[i], &S.srv[i + 1], (size_t)(S.nsrv - i - 1) * sizeof(sif_server_info));
    S.nsrv--;
    return 0;
}

const sif_server_info *sif_server_find(uint32_t sid) { RG_IOP_HLE("sif_server_find"); return srv_find(sid); }
int sif_server_count(void) { return S.nsrv; }
const sif_server_info *sif_server_get(int i) { return (i >= 0 && i < S.nsrv) ? &S.srv[i] : NULL; }

static uint32_t token_of(const sif_server_info *s) { return 0x5F000000u | (uint32_t)(s - S.srv + 1); }

int sif_rpc_bind(uint32_t sid, uint32_t *token)
{
    RG_IOP_HLE_ID("sif_rpc_bind", sid);
    sif_server_info *s = srv_find(sid);
    S.st.rpc_binds++;
    if (!s) {
        /* the SDK idiom re-binds in a loop until serve != NULL: report each SID once */
        int seen = 0;
        for (int i = 0; i < S.nbad; i++)
            if (S.bad_bind[i] == sid)
                seen = 1;
        if (!seen) {
            if (S.nbad < 16)
                S.bad_bind[S.nbad++] = sid;
            reportf(SIF_REP_UNKNOWN_SERVER, sid, 0, "bind to unknown RPC server 0x%08X (reported once)", sid);
        }
        if (token)
            *token = 0;
        return -1;
    }
    s->binds++;
    if (token)
        *token = token_of(s);
    tracef("bind sid=0x%08X (%s)", sid, s->name);
    return 0;
}

static void fno_count(uint32_t sid, uint32_t fno)
{
    for (int i = 0; i < S.nfs; i++)
        if (S.fs[i].sid == sid && S.fs[i].fno == fno) {
            S.fs[i].n++;
            return;
        }
    if (S.nfs < FNO_STATS) {
        S.fs[S.nfs].sid = sid;
        S.fs[S.nfs].fno = fno;
        S.fs[S.nfs].n = 1;
        S.nfs++;
    }
}

uint32_t sif_call_count(uint32_t sid, uint32_t fno)
{
    for (int i = 0; i < S.nfs; i++)
        if (S.fs[i].sid == sid && S.fs[i].fno == fno)
            return S.fs[i].n;
    return 0;
}

int sif_call_log_count(void) { return S.nlog; }
const sif_call_rec *sif_call_log_get(int back)
{
    if (back < 0 || back >= S.nlog || back >= SIF_CALL_LOG)
        return NULL;
    return &S.log[(S.nlog - 1 - back) % SIF_CALL_LOG];
}

typedef struct rpc_done {
    uint32_t ticket;
    void *recv;
    uint32_t rsize;
    sif_done_fn done;
    void *done_arg;
    uint8_t *reply; /* malloc'd copy, rsize bytes, or NULL */
} rpc_done;

static void rpc_complete(void *arg)
{
    rpc_done *d = (rpc_done *)arg;
    if (d->reply && d->recv && d->rsize)
        sif0_write(d->recv, d->reply, d->rsize);
    S.busy[d->ticket % MAX_TICKETS] = 0;
    if (d->done)
        d->done(d->done_arg);
    free(d->reply);
    free(d);
}

uint32_t sif_rpc_call(const sif_call *c)
{
    RG_IOP_HLE_ID("sif_rpc_call", ((c->sid & 0xFFFFFu) << 12) | (c->fno & 0xFFFu));
    sif_server_info *s = srv_find(c->sid);
    uint32_t ticket = S.ticket_next++;
    if (S.ticket_next == 0)
        S.ticket_next = 1;
    S.st.rpc_calls++;
    fno_count(c->sid, c->fno);
    sif_call_rec *rec = &S.log[S.nlog % SIF_CALL_LOG];
    S.nlog++;
    rec->seq = (uint32_t)S.nlog;
    rec->sid = c->sid;
    rec->fno = c->fno;
    rec->ssize = c->ssize;
    rec->rsize = c->rsize;
    rec->when = clock_now();
    rec->status = 0;

    rpc_done *d = (rpc_done *)calloc(1, sizeof *d);
    if (!d)
        return 0;
    d->ticket = ticket;
    d->recv = c->recv;
    d->rsize = c->rsize;
    d->done = c->done;
    d->done_arg = c->done_arg;

    if (!s) {
        rec->status = 1;
        reportf(SIF_REP_UNKNOWN_SERVER, c->sid, c->fno, "call to unknown RPC server 0x%08X fno 0x%X", c->sid, c->fno);
        d->recv = NULL;
        S.busy[ticket % MAX_TICKETS] = 1;
        sif_post(S.cfg.rpc_latency, rpc_complete, d);
        return 0;
    }
    s->calls++;
    sif_rpc_ctx ctx;
    memset(&ctx, 0, sizeof ctx);
    ctx.sid = c->sid;
    ctx.fno = c->fno;
    ctx.rsize = c->rsize;
    ctx.ee_recv = c->recv;
    uint32_t n = c->ssize;
    if (s->buf_iop) {
        if (n > s->bufsize) {
            reportf(SIF_REP_TRUNCATED, c->sid, c->fno, "server 0x%08X fno 0x%X: send 0x%X > buffer 0x%X",
                    c->sid, c->fno, n, s->bufsize);
            n = s->bufsize;
        }
        ctx.data = iop_ptr(s->buf_iop, s->bufsize);
        ctx.data_iop = s->buf_iop;
        if (n && c->send)
            memmove(ctx.data, c->send, n);
        S.st.dma1_xfers++;
        S.st.dma1_bytes += n;
    } else {
        ctx.data = (void *)c->send; /* bufferless server: read the caller's data in place */
    }
    ctx.size = n;
    tracef("call sid=0x%08X fno=0x%X ssize=0x%X rsize=0x%X", c->sid, c->fno, c->ssize, c->rsize);
    void *reply = s->fn ? s->fn(&ctx, s->user) : NULL;
    if (ctx.unknown) {
        rec->status = 2;
        s->unknown_calls++;
        reportf(SIF_REP_UNKNOWN_FNO, c->sid, c->fno, "server 0x%08X (%s): unknown function 0x%X", c->sid,
                s->name, c->fno);
    }
    if (reply && c->recv && c->rsize) {
        d->reply = (uint8_t *)malloc(c->rsize);
        if (d->reply)
            memcpy(d->reply, reply, c->rsize);
    }
    S.busy[ticket % MAX_TICKETS] = 1;
    sif_post(S.cfg.rpc_latency, rpc_complete, d);
    return ticket;
}

int sif_rpc_busy(uint32_t ticket) { return ticket ? S.busy[ticket % MAX_TICKETS] : 0; }

/* ---- EE-side servers ----------------------------------------------------------- */
static ee_srv *ees_find(uint32_t sid)
{
    for (int i = 0; i < S.nees; i++)
        if (S.ees[i].sid == sid)
            return &S.ees[i];
    return NULL;
}

int sif_ee_server_attach(uint32_t sid, sif_ee_sink_fn fn, void *user)
{
    RG_IOP_HLE("sif_ee_server_attach");
    ee_srv *e = ees_find(sid);
    if (!e) {
        if (S.nees >= MAX_EE_SERVERS)
            return -1;
        e = &S.ees[S.nees++];
    }
    e->sid = sid;
    e->fn = fn;
    e->user = user;
    return 0;
}

int sif_ee_server_detach(uint32_t sid)
{
    ee_srv *e = ees_find(sid);
    if (!e)
        return -1;
    int i = (int)(e - S.ees);
    memmove(&S.ees[i], &S.ees[i + 1], (size_t)(S.nees - i - 1) * sizeof(ee_srv));
    S.nees--;
    return 0;
}

int sif_ee_server_present(uint32_t sid) { return ees_find(sid) != NULL; }

typedef struct ee_call {
    uint32_t sid, fno, size;
    uint8_t data[];
} ee_call;

static void ee_call_deliver(void *arg)
{
    ee_call *c = (ee_call *)arg;
    ee_srv *e = ees_find(c->sid);
    if (e && e->fn)
        e->fn(c->sid, c->fno, c->data, c->size, e->user);
    else
        reportf(SIF_REP_NO_EE_SERVER, c->sid, c->fno, "EE server 0x%08X went away before delivery", c->sid);
    free(c);
}

int sif_iop_call_ee(uint32_t sid, uint32_t fno, const void *data, uint32_t size)
{
    RG_IOP_HLE("sif_iop_call_ee");
    if (!ees_find(sid)) {
        reportf(SIF_REP_NO_EE_SERVER, sid, fno, "IOP call to unregistered EE server 0x%08X fno 0x%X", sid, fno);
        return -1;
    }
    ee_call *c = (ee_call *)malloc(sizeof(ee_call) + size);
    if (!c)
        return -1;
    c->sid = sid;
    c->fno = fno;
    c->size = size;
    if (size && data)
        memcpy(c->data, data, size);
    S.st.ee_calls++;
    tracef("IOP->EE call sid=0x%08X fno=0x%X size=0x%X", sid, fno, size);
    return sif_post(S.cfg.rpc_latency, ee_call_deliver, c);
}

/* ---- commands ------------------------------------------------------------------- */
static cmd_h *cmd_find(cmd_h *tab, int n, uint32_t cid)
{
    for (int i = 0; i < n; i++)
        if (tab[i].cid == cid)
            return &tab[i];
    return NULL;
}

static int cmd_set(cmd_h *tab, int *n, uint32_t cid, sif_cmd_fn fn, void *user)
{
    cmd_h *h = cmd_find(tab, *n, cid);
    if (!fn) {
        if (h) {
            int i = (int)(h - tab);
            memmove(&tab[i], &tab[i + 1], (size_t)(*n - i - 1) * sizeof(cmd_h));
            (*n)--;
        }
        return 0;
    }
    if (!h) {
        if (*n >= MAX_CMD)
            return -1;
        h = &tab[(*n)++];
    }
    h->cid = cid;
    h->fn = fn;
    h->user = user;
    return 0;
}

int sif_ee_cmd_set(uint32_t cid, sif_cmd_fn fn, void *user) { RG_IOP_HLE("sif_ee_cmd_set"); return cmd_set(S.ee_cmd, &S.nee_cmd, cid, fn, user); }
int sif_iop_cmd_set(uint32_t cid, sif_cmd_fn fn, void *user) { return cmd_set(S.iop_cmd, &S.niop_cmd, cid, fn, user); }

uint32_t sif_ee_send_cmd(uint32_t cid, const void *pkt, uint32_t psize, const void *extra_src, uint32_t extra_dest,
                         uint32_t extra_size)
{
    RG_IOP_HLE("sif_ee_send_cmd");
    if (extra_size && extra_src) {
        sif_dma_xfer x = {(uint32_t)(uintptr_t)extra_src, extra_dest, extra_size, 0};
        if (!sif1_dma(&x, 1))
            return 0;
    }
    S.st.cmds_to_iop++;
    tracef("EE->IOP cmd 0x%08X psize=0x%X extra=0x%X", cid, psize, extra_size);
    if (cid == SIF_CMD_SET_SREG && pkt && psize >= 24) {
        /* header (16 bytes) + {reg, value} */
        const uint32_t *w = (const uint32_t *)pkt;
        S.sreg[w[4] & 31u] = w[5];
    } else {
        cmd_h *h = cmd_find(S.iop_cmd, S.niop_cmd, cid);
        if (h)
            h->fn(cid, pkt, psize, h->user);
        else if (!(cid & SIF_CMD_SYS))
            reportf(SIF_REP_NO_HANDLER, cid, 0, "EE->IOP command 0x%08X has no IOP handler", cid);
    }
    uint32_t id = S.dma_next++;
    if (S.dma_next == 0)
        S.dma_next = 1;
    S.dma[id % DMA_RING].id = id;
    S.dma[id % DMA_RING].done = clock_now();
    return id;
}

typedef struct cmd_pkt {
    uint32_t cid, size;
    uint8_t data[];
} cmd_pkt;

static void ee_cmd_deliver(void *arg)
{
    cmd_pkt *p = (cmd_pkt *)arg;
    cmd_h *h = cmd_find(S.ee_cmd, S.nee_cmd, p->cid);
    if (h)
        h->fn(p->cid, p->data, p->size, h->user);
    else
        reportf(SIF_REP_NO_HANDLER, p->cid, 0, "IOP->EE command 0x%08X: handler removed", p->cid);
    free(p);
}

int sif_iop_send_cmd(uint32_t cid, const void *pkt, uint32_t psize)
{
    RG_IOP_HLE("sif_iop_send_cmd");
    if (!cmd_find(S.ee_cmd, S.nee_cmd, cid)) {
        reportf(SIF_REP_NO_HANDLER, cid, 0, "IOP->EE command 0x%08X has no EE handler", cid);
        return -1;
    }
    cmd_pkt *p = (cmd_pkt *)malloc(sizeof(cmd_pkt) + psize);
    if (!p)
        return -1;
    p->cid = cid;
    p->size = psize;
    if (psize && pkt)
        memcpy(p->data, pkt, psize);
    S.st.cmds_to_ee++;
    return sif_post(S.cfg.rpc_latency, ee_cmd_deliver, p);
}
