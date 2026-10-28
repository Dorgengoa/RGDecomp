/* SPDX-License-Identifier: CC0-1.0 */
/* EE SIF SDK surface: boot/kernel wiring, sifcmd, SIF DMA, sifrpc, iopheap, loadfile,
 * iopcontrol. See libsif.h and docs/SIF.md. */
#include "libsif.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iop.h"
#include "ps2k.h"
#include "sif.h"
#include "sif_internal.h"

/* ---- boot and kernel wiring --------------------------------------------------- */
#if RG_IOP_ORACLE /* RG_NATIVE_ONLY: no SIF boot, no SIF0 handler (docs/NATIVE-ONLY.md) */
static struct {
    int booted;
    int use_kernel;
    int dmac_handler; /* ps2k handler id, 0 = not installed */
    int cmd_inited;
} B;

static uint64_t hk_now(void *u)
{
    (void)u;
    return ps2k_now();
}

static void hk_schedule(uint64_t due, void *u)
{
    (void)u;
    uint64_t now = ps2k_now();
    ps2k_post_dmac(DMAC_CH_SIF0, due > now ? due - now : 0);
}

/* DMAC SIF0 handler: the IOP -> EE path. Runs every SIF event that is due. */
static int sif0_dmac_handler(int ch)
{
    (void)ch;
    sif_deliver();
    return 0;
}

static void install_dmac_handler(void)
{
    if (!B.use_kernel || B.dmac_handler > 0)
        return;
    int id = ps2k_add_dmac_handler(DMAC_CH_SIF0, sif0_dmac_handler, 0);
    if (id > 0) {
        B.dmac_handler = id;
        ps2k_enable_dmac(DMAC_CH_SIF0, ps2k_in_handler());
    }
}

void rg_sif_default_boot_config(rg_sif_boot_config *cfg)
{
    memset(cfg, 0, sizeof *cfg);
    cfg->install_sound_placeholders = 1;
    cfg->use_kernel = 1;
}

int rg_sif_boot(const rg_sif_boot_config *cfg)
{
    rg_sif_boot_config d;
    if (!cfg) {
        rg_sif_default_boot_config(&d);
        cfg = &d;
    }
    sif_config sc;
    sif_default_config(&sc);
    sc.rpc_latency = cfg->rpc_latency;
    sc.dma_setup = cfg->dma_setup;
    sc.dma_cycles_per_qword = cfg->dma_cycles_per_qword;
    sc.boot_latency = cfg->boot_latency;
    sif_init(&sc);
    iop_reset();
    iop_log_clear();
    iop_hle_config hc;
    iop_hle_default_config(&hc);
    hc.cdrom_root = cfg->cdrom_root;
    hc.host_root = cfg->host_root;
    hc.install_sound_placeholders = cfg->install_sound_placeholders;
    int r = iop_hle_install(&hc);
    memset(&B, 0, sizeof B);
    B.use_kernel = cfg->use_kernel;
    if (B.use_kernel) {
        sif_hooks h = {hk_now, hk_schedule, NULL};
        sif_set_hooks(&h);
    } else {
        sif_set_hooks(NULL);
    }
    sif_ee_reset_clients();
    fio_reset_client();
    sdr_reset();
    B.booted = 1;
    return r;
}

int rg_sif_booted(void) { return B.booted; }

void sif_ee_ensure_boot(void)
{
    if (!B.booted)
        rg_sif_boot(NULL);
    install_dmac_handler();
}

int sif_ee_can_block(void)
{
    return B.use_kernel && ps2k_get_thread_id() > 0 && !ps2k_in_handler();
}

/* Wait for a condition polled by `done(arg)`: blocks on a sema (signalled by the
 * completion in handler context) when on a guest thread; otherwise delivers events
 * directly. Used by every synchronous SDK call. */
void sif_ee_wait_idle(void)
{
    if (!B.use_kernel || ps2k_get_thread_id() <= 0 || ps2k_in_handler()) {
        sif_deliver_all();
        return;
    }
    /* time moves only through the kernel: charge up to the next due event, then let
     * the kernel deliver the SIF0 interrupt */
    uint64_t due = sif_next_due(), now = ps2k_now();
    if (due != UINT64_MAX && due > now)
        ps2k_charge(due - now);
    ps2k_poll();
}
#endif /* RG_IOP_ORACLE */

/* ---- RG_IOP=native (docs/NATIVE-IOP.md) ---------------------------------------------- *
 * No IOP exists: registers read as a booted IOP (SMFLAG = SIFINIT|CMDINIT|BOOTEND, as the
 * HLE reports after boot), software registers are a plain array; nothing here calls
 * src/ps2/sif or src/ps2/iop. */
static struct {
    uint32_t sreg[32];
    uint32_t mscom, smcom, msflag, smflag, ctrl;
    int smflag_set;
    int modules; /* sceSifLoadModule ids handed out (1..), as the HLE's LOADFILE */
    sceSifServeData serve; /* non-NULL serve handle for a bind nothing serves */
} N;

uint32_t sif_native_reg_get(uint32_t reg)
{
    if (!N.smflag_set) {
        N.smflag = 0x70000u; /* SIF_STAT_SIFINIT | SIF_STAT_CMDINIT | SIF_STAT_BOOTEND */
        N.smflag_set = 1;
    }
    if (reg & 0x80000000u)
        return N.sreg[reg & 31u];
    switch (reg) {
    case 1: return N.mscom;
    case 2: return N.smcom;
    case 3: return N.msflag;
    case 4: return N.smflag;
    case 5: return N.ctrl;
    default: return 0;
    }
}

uint32_t sif_native_reg_set(uint32_t reg, uint32_t v)
{
    uint32_t old = sif_native_reg_get(reg);
    if (reg & 0x80000000u) {
        N.sreg[reg & 31u] = v;
        return old;
    }
    switch (reg) {
    case 1: N.mscom = v; break;
    case 2: N.smcom = v; break;
    case 3: N.msflag |= v; break;  /* EE writes set */
    case 4: N.smflag &= ~v; break; /* EE writes clear */
    case 5: N.ctrl = v; break;
    default: break;
    }
    return old;
}

#if !RG_IOP_ORACLE
/* Native-only build: the HW SIF registers src/ps2/hwbus maps (0 accesses on the golden
 * route) answer from the native shadow above instead of the SIF HLE's register file. */
uint32_t sif_reg_get(uint32_t reg) { return sif_native_reg_get(reg); }
uint32_t sif_reg_set(uint32_t reg, uint32_t v) { return sif_native_reg_set(reg, v); }
#endif

/* ---- sifcmd ------------------------------------------------------------------------ */
#if RG_IOP_ORACLE
#define MAX_EE_CMD 32
static struct {
    unsigned int cid;
    sceSifCmdHandler fn;
    void *data;
} g_cmd[MAX_EE_CMD];
static int g_ncmd;

void sceSifInitCmd(void)
{
    RG_IOP_API("sceSifInitCmd");
    if (rg_iop_native())
        return;
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    B.cmd_inited = 1;
#endif
}

void sceSifExitCmd(void)
{
    RG_IOP_API("sceSifExitCmd");
    if (rg_iop_native())
        return;
#if RG_IOP_ORACLE
    if (B.dmac_handler > 0) {
        ps2k_remove_dmac_handler(DMAC_CH_SIF0, B.dmac_handler);
        B.dmac_handler = 0;
    }
    B.cmd_inited = 0;
#endif
}

static void ee_cmd_bridge(uint32_t cid, const void *pkt, uint32_t size, void *user)
{
    (void)size;
    (void)user;
    for (int i = 0; i < g_ncmd; i++)
        if (g_cmd[i].cid == cid && g_cmd[i].fn) {
            g_cmd[i].fn((void *)pkt, g_cmd[i].data);
            return;
        }
}
#endif

void sceSifAddCmdHandler(unsigned int cid, sceSifCmdHandler handler, void *data)
{
    RG_IOP_API("sceSifAddCmdHandler");
    if (rg_iop_native())
        return; /* no IOP sends commands */
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    int i;
    for (i = 0; i < g_ncmd; i++)
        if (g_cmd[i].cid == cid)
            break;
    if (i == g_ncmd) {
        if (g_ncmd >= MAX_EE_CMD)
            return;
        g_ncmd++;
    }
    g_cmd[i].cid = cid;
    g_cmd[i].fn = handler;
    g_cmd[i].data = data;
    sif_ee_cmd_set(cid, ee_cmd_bridge, NULL);
#else
    (void)cid, (void)handler, (void)data;
#endif
}

void sceSifRemoveCmdHandler(unsigned int cid)
{
    RG_IOP_API("sceSifRemoveCmdHandler");
    if (rg_iop_native())
        return;
#if RG_IOP_ORACLE
    for (int i = 0; i < g_ncmd; i++)
        if (g_cmd[i].cid == cid) {
            g_cmd[i] = g_cmd[--g_ncmd];
            break;
        }
    sif_ee_cmd_set(cid, NULL, NULL);
#else
    (void)cid;
#endif
}

unsigned int sceSifSendCmd(unsigned int cid, void *packet, int packet_size, void *src_extra, void *dest_extra,
                           int size_extra)
{
    RG_IOP_API("sceSifSendCmd");
    if (rg_iop_native()) {
        rg_iop_unconverted("sceSifSendCmd", cid);
        (void)packet, (void)packet_size, (void)src_extra, (void)dest_extra, (void)size_extra;
        return 0;
    }
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    return sif_ee_send_cmd(cid, packet, (uint32_t)packet_size, src_extra, (uint32_t)(uintptr_t)dest_extra,
                           (uint32_t)size_extra);
#endif
}

unsigned int isceSifSendCmd(unsigned int cid, void *packet, int packet_size, void *src_extra, void *dest_extra,
                            int size_extra)
{
    return sceSifSendCmd(cid, packet, packet_size, src_extra, dest_extra, size_extra);
}

unsigned int sceSifGetSreg(int reg)
{
    RG_IOP_API("sceSifGetSreg");
    uint32_t r = SIF_SREG_BASE | (unsigned)(reg & 31);
    return RG_IOP_PICK(sif_native_reg_get(r), sif_reg_get(r));
}
unsigned int sceSifSetSreg(int reg, unsigned int v)
{
    RG_IOP_API("sceSifSetSreg");
    uint32_t r = SIF_SREG_BASE | (unsigned)(reg & 31);
    return RG_IOP_PICK(sif_native_reg_set(r, v), sif_reg_set(r, v));
}
void sceSifWriteBackDCache(void *ptr, int size) { (void)ptr; (void)size; }

/* ---- DMA / registers --------------------------------------------------------------- */
unsigned int sceSifSetDma(sceSifDmaData *sdd, int len)
{
    RG_IOP_API("sceSifSetDma");
    if (rg_iop_native()) {
        /* no IOP memory to copy into: a caller still sending data is another lane's */
        rg_iop_unconverted("sceSifSetDma", (uint32_t)len);
        (void)sdd;
        return 1;
    }
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    return sif1_dma((const sif_dma_xfer *)sdd, len);
#endif
}
unsigned int isceSifSetDma(sceSifDmaData *sdd, int len) { return sceSifSetDma(sdd, len); }

/* The game polls this in a DelayThread loop (SifDmaSendSync), which moves virtual
 * time, so a transfer with a non-zero cost completes. */
int sceSifDmaStat(unsigned int id)
{
    RG_IOP_API("sceSifDmaStat");
    (void)id;
    return RG_IOP_PICK(-1, sif_dma_stat(id)); /* native: nothing in flight */
}
int isceSifDmaStat(unsigned int id) { (void)id; return RG_IOP_PICK(-1, sif_dma_stat(id)); }
void sceSifSetDChain(void) {}
void isceSifSetDChain(void) {}
void sceSifStopDma(void) {}
int sceSifGetReg(unsigned int reg)
{
    RG_IOP_API("sceSifGetReg");
    return (int)RG_IOP_PICK(sif_native_reg_get(reg), sif_reg_get(reg));
}
int sceSifSetReg(unsigned int reg, int value)
{
    RG_IOP_API("sceSifSetReg");
    return (int)RG_IOP_PICK(sif_native_reg_set(reg, (uint32_t)value), sif_reg_set(reg, (uint32_t)value));
}

/* ---- sifrpc: client ---------------------------------------------------------------- */
#if RG_IOP_ORACLE
#define MAX_CLIENTS 64
static struct {
    sceSifClientData *cd;
    uint32_t ticket;
} g_cli[MAX_CLIENTS];
static int g_ncli;

/* serve handles handed to bound clients (the game only tests serve != NULL) */
static sceSifServeData g_serve_stub[SIF_MAX_SERVERS];

void sif_ee_reset_clients(void)
{
    g_ncli = 0;
    memset(g_serve_stub, 0, sizeof g_serve_stub);
}

static int cli_slot(sceSifClientData *cd)
{
    for (int i = 0; i < g_ncli; i++)
        if (g_cli[i].cd == cd)
            return i;
    if (g_ncli >= MAX_CLIENTS)
        return -1;
    g_cli[g_ncli].cd = cd;
    g_cli[g_ncli].ticket = 0;
    return g_ncli++;
}
#endif

void sceSifInitRpc(unsigned int mode)
{
    RG_IOP_API("sceSifInitRpc");
    (void)mode;
    if (rg_iop_native())
        return;
    sceSifInitCmd();
}

void sceSifExitRpc(void) {}

int sceSifBindRpc(sceSifClientData *cd, unsigned int sid, unsigned int mode)
{
    RG_IOP_API_ID("sceSifBindRpc", sid);
    (void)mode;
    if (rg_iop_native()) {
        /* nothing native serves an IOP RPC id: a binder is an unconverted IOP user.
         * The handle is non-NULL so a caller polling `serve` does not spin forever. */
        rg_iop_unconverted("sceSifBindRpc", sid);
        memset(cd, 0, sizeof *cd);
        cd->command = sid;
        cd->serve = &N.serve;
        return 0;
    }
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    uint32_t token;
    memset(cd, 0, sizeof *cd);
    cd->command = sid;
    if (sif_rpc_bind(sid, &token) == 0) {
        const sif_server_info *s = sif_server_find(sid);
        int idx = (int)(token & 0xFFFFu) - 1;
        if (idx < 0 || idx >= SIF_MAX_SERVERS)
            idx = 0;
        g_serve_stub[idx].command = sid;
        g_serve_stub[idx].buff = (void *)(uintptr_t)(s ? s->buf_iop : 0);
        g_serve_stub[idx].size = s ? (int)s->bufsize : 0;
        cd->buff = g_serve_stub[idx].buff;
        cd->serve = &g_serve_stub[idx];
    }
    cli_slot(cd);
    return 0;
#endif
}

#if RG_IOP_ORACLE
typedef struct call_wait {
    sceSifEndFunc end;
    void *para;
    int sema;    /* >= 0: signal at completion (kernel sema ids start at 0, VALIDATION.md 2c) */
    int done;
} call_wait;

static void call_done(void *arg)
{
    call_wait *w = (call_wait *)arg;
    if (w->end)
        w->end(w->para);
    w->done = 1;
    if (w->sema >= 0)
        ps2k_signal_sema(w->sema, ps2k_in_handler());
}

static void call_done_async(void *arg)
{
    call_wait *w = (call_wait *)arg;
    if (w->end)
        w->end(w->para);
    free(w);
}

int sif_ee_rpc_sync(uint32_t sid, uint32_t fno, const void *send, uint32_t ssize, void *recv, uint32_t rsize)
{
    sif_ee_ensure_boot();
    call_wait w = {0, 0, -1, 0};
    if (sif_ee_can_block())
        w.sema = ps2k_create_sema(0, 1, 0, 0);
    sif_call c = {sid, fno, send, ssize, recv, rsize, call_done, &w};
    uint32_t t = sif_rpc_call(&c);
    if (w.sema >= 0) {
        ps2k_wait_sema(w.sema);
        ps2k_delete_sema(w.sema, 0);
    } else {
        while (!w.done)
            sif_ee_wait_idle();
    }
    return t ? 0 : -1;
}
#endif /* RG_IOP_ORACLE */

int sceSifCallRpc(sceSifClientData *cd, unsigned int fno, unsigned int mode, void *send, int ssize, void *recv,
                  int rsize, sceSifEndFunc end, void *endpara)
{
    RG_IOP_API_ID("sceSifCallRpc", cd ? ((cd->command & 0xFFFFFu) << 12) | (fno & 0xFFFu) : 0);
    if (rg_iop_native()) {
        /* as a call to an unknown server: the receive buffer stays untouched and the
         * end function runs (here, at once), so a waiter never hangs */
        if (!cd)
            return -1;
        rg_iop_unconverted("sceSifCallRpc", ((cd->command & 0xFFFFFu) << 12) | (fno & 0xFFFu));
        (void)mode;
        (void)send;
        (void)ssize;
        (void)recv;
        (void)rsize;
        if (end)
            end(endpara);
        return 0;
    }
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    if (!cd)
        return -1;
    int slot = cli_slot(cd);
    cd->func = end;
    cd->para = endpara;
    cd->rpcd.mode = mode;
    uint32_t sid = cd->command;
    if (ssize < 0)
        ssize = 0;
    if (rsize < 0)
        rsize = 0;
    if (mode & SIF_RPCM_NOWAIT) {
        call_wait *w = (call_wait *)calloc(1, sizeof *w);
        if (!w)
            return -1;
        w->end = end;
        w->para = endpara;
        sif_call c = {sid, fno, send, (uint32_t)ssize, recv, (uint32_t)rsize, call_done_async, w};
        uint32_t t = sif_rpc_call(&c);
        if (slot >= 0)
            g_cli[slot].ticket = t;
        cd->rpcd.paddr = t ? (void *)cd : NULL;
        return 0;
    }
    call_wait w = {end, endpara, -1, 0};
    if (sif_ee_can_block())
        w.sema = ps2k_create_sema(0, 1, 0, 0);
    sif_call c = {sid, fno, send, (uint32_t)ssize, recv, (uint32_t)rsize, call_done, &w};
    uint32_t t = sif_rpc_call(&c);
    if (slot >= 0)
        g_cli[slot].ticket = t;
    if (w.sema >= 0) {
        ps2k_wait_sema(w.sema);
        ps2k_delete_sema(w.sema, 0);
    } else {
        while (!w.done)
            sif_ee_wait_idle();
    }
    return 0;
#endif
}

int sceSifCheckStatRpc(sceSifRpcData *rd)
{
    RG_IOP_API("sceSifCheckStatRpc");
    (void)rd;
    if (rg_iop_native())
        return 0;
#if RG_IOP_ORACLE
    sceSifClientData *cd = (sceSifClientData *)rd; /* rpcd is the first member */
    for (int i = 0; i < g_ncli; i++)
        if (g_cli[i].cd == cd)
            return sif_rpc_busy(g_cli[i].ticket);
    return 0;
#endif
}

/* ---- sifrpc: EE-side servers -------------------------------------------------------- */
#if RG_IOP_ORACLE
typedef struct ee_req {
    sceSifServeData *sd;
    uint32_t fno, size;
    struct ee_req *next;
    uint8_t data[];
} ee_req;

static sceSifQueueData * SCE_P32 g_queues;
static ee_req *g_req_head, *g_req_tail;
#endif

void sceSifSetRpcQueue(sceSifQueueData *qd, int thread_id)
{
    RG_IOP_API("sceSifSetRpcQueue");
    if (rg_iop_native()) {
        memset(qd, 0, sizeof *qd);
        qd->key = thread_id;
        return; /* no IOP calls the EE */
    }
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    memset(qd, 0, sizeof *qd);
    qd->key = thread_id;
    qd->next = g_queues;
    g_queues = qd;
#endif
}

#if RG_IOP_ORACLE
static void ee_sink(uint32_t sid, uint32_t fno, const void *data, uint32_t size, void *user)
{
    (void)sid;
    sceSifServeData *sd = (sceSifServeData *)user;
    ee_req *r = (ee_req *)malloc(sizeof(ee_req) + size);
    if (!r)
        return;
    r->sd = sd;
    r->fno = fno;
    r->size = size;
    r->next = NULL;
    if (size)
        memcpy(r->data, data, size);
    if (g_req_tail)
        g_req_tail->next = r;
    else
        g_req_head = r;
    g_req_tail = r;
    if (sd->base && sd->base->key > 0)
        ps2k_wakeup_thread(sd->base->key, ps2k_in_handler());
}
#endif

void sceSifRegisterRpc(sceSifServeData *sd, unsigned int sid, sceSifRpcFunc func, void *buff, sceSifRpcFunc cfunc,
                       void *cbuff, sceSifQueueData *qd)
{
    RG_IOP_API("sceSifRegisterRpc");
    if (rg_iop_native()) {
        rg_iop_unconverted("sceSifRegisterRpc", sid);
        (void)sd, (void)func, (void)buff, (void)cfunc, (void)cbuff, (void)qd;
        return;
    }
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    memset(sd, 0, sizeof *sd);
    sd->command = sid;
    sd->func = func;
    sd->buff = buff;
    sd->cfunc = cfunc;
    sd->cbuff = cbuff;
    sd->base = qd;
    if (qd) {
        sceSifServeData * SCE_P32 *pp = &qd->link;
        while (*pp)
            pp = &(*pp)->link;
        *pp = sd;
    }
    sif_ee_server_attach(sid, ee_sink, sd);
#endif
}

sceSifServeData *sceSifRemoveRpc(sceSifServeData *sd, sceSifQueueData *qd)
{
    RG_IOP_API("sceSifRemoveRpc");
    (void)qd;
    if (rg_iop_native())
        return sd;
#if RG_IOP_ORACLE
    if (qd) {
        for (sceSifServeData * SCE_P32 *pp = &qd->link; *pp; pp = &(*pp)->link)
            if (*pp == sd) {
                *pp = sd->link;
                break;
            }
    }
    sif_ee_server_detach(sd->command);
    return sd;
#endif
}

sceSifQueueData *sceSifRemoveRpcQueue(sceSifQueueData *qd)
{
    RG_IOP_API("sceSifRemoveRpcQueue");
    if (rg_iop_native())
        return qd;
#if RG_IOP_ORACLE
    for (sceSifQueueData * SCE_P32 *pp = &g_queues; *pp; pp = &(*pp)->next)
        if (*pp == qd) {
            *pp = qd->next;
            return qd;
        }
    return NULL;
#endif
}

sceSifServeData *sceSifGetNextRequest(sceSifQueueData *qd)
{
    RG_IOP_API("sceSifGetNextRequest");
    (void)qd;
    if (rg_iop_native())
        return NULL;
#if RG_IOP_ORACLE
    ee_req *prev = NULL;
    for (ee_req *r = g_req_head; r; prev = r, r = r->next) {
        if (r->sd->base != qd)
            continue;
        if (prev)
            prev->next = r->next;
        else
            g_req_head = r->next;
        if (g_req_tail == r)
            g_req_tail = prev;
        sceSifServeData *sd = r->sd;
        if (sd->buff && r->size)
            memcpy(sd->buff, r->data, r->size);
        sd->fno = r->fno;
        sd->size = (int)r->size;
        free(r);
        qd->active = 1;
        return sd;
    }
    qd->active = 0;
    return NULL;
#endif
}

void sceSifExecRequest(sceSifServeData *sd)
{
    RG_IOP_API("sceSifExecRequest");
    (void)sd;
    if (rg_iop_native())
        return;
#if RG_IOP_ORACLE
    if (sd->func)
        ((sceSifRpcFunc)sd->func)(sd->fno, sd->buff, sd->size); /* the IOP side ignores EE replies here */
#endif
}

void sceSifRpcLoop(sceSifQueueData *qd)
{
    for (;;) {
        sceSifServeData *sd;
        while ((sd = sceSifGetNextRequest(qd)) != NULL)
            sceSifExecRequest(sd);
        ps2k_sleep_thread();
    }
}

/* ---- iopheap --------------------------------------------------------------------------- */
#if RG_IOP_ORACLE
static int g_heap_bound;
#endif

int sceSifInitIopHeap(void)
{
    RG_IOP_API("sceSifInitIopHeap");
    if (rg_iop_native())
        return 0;
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    uint32_t tok;
    g_heap_bound = sif_rpc_bind(0x80000003u, &tok) == 0;
    return g_heap_bound ? 0 : -1;
#endif
}

static uint32_t heap_rpc(uint32_t fno, uint32_t a0)
{
    if (rg_iop_native()) {
        /* no IOP memory: an allocation is a budget handle only (an IOP-heap user left
         * in native mode is another lane's transport, counted as unconverted) */
        switch (fno) {
        case 1:
        case 4: rg_iop_unconverted("sceSifAllocIopHeap", 0); return rg_iop_native_heap_handle(a0);
        case 2: return 0;
        case 5: return 0x200000u;               /* QueryMemSize: 2 MiB */
        case 6: case 7: return 0x130000u;       /* the HLE heap's size, all free */
        default: return 0;
        }
    }
#if RG_IOP_ORACLE
    if (!g_heap_bound && sceSifInitIopHeap() < 0)
        return 0;
    uint32_t send[4] = {a0, 0, 0, 0}, recv[4] = {0, 0, 0, 0};
    if (sif_ee_rpc_sync(0x80000003u, fno, send, 4, recv, 4) < 0)
        return 0;
    return recv[0];
#endif
}

void *sceSifAllocIopHeap(unsigned int size) { RG_IOP_API("sceSifAllocIopHeap"); return (void *)(uintptr_t)heap_rpc(1, size); }
int sceSifFreeIopHeap(void *addr) { RG_IOP_API("sceSifFreeIopHeap"); return (int)heap_rpc(2, (uint32_t)(uintptr_t)addr); }
void *sceSifAllocSysMemory(int type, unsigned int size, void *addr)
{
    RG_IOP_API("sceSifAllocSysMemory");
    (void)type;
    (void)addr;
    return (void *)(uintptr_t)heap_rpc(4, size);
}
int sceSifFreeSysMemory(void *addr) { return sceSifFreeIopHeap(addr); }
unsigned int sceSifQueryMemSize(void) { RG_IOP_API("sceSifQueryMemSize"); return heap_rpc(5, 0); }
unsigned int sceSifQueryMaxFreeMemSize(void) { RG_IOP_API("sceSifQueryMaxFreeMemSize"); return heap_rpc(6, 0); }
unsigned int sceSifQueryTotalFreeMemSize(void) { RG_IOP_API("sceSifQueryTotalFreeMemSize"); return heap_rpc(7, 0); }

/* ---- loadfile / iopcontrol ---------------------------------------------------------------- */
#if RG_IOP_ORACLE
static int g_lf_bound;
#endif

int sceSifLoadFileReset(void)
{
    RG_IOP_API("sceSifLoadFileReset");
#if RG_IOP_ORACLE
    g_lf_bound = 0;
#endif
    return 0;
}

int sceSifLoadStartModule(const char *path, int argsz, const char *args, int *result)
{
    RG_IOP_API("sceSifLoadStartModule");
    if (rg_iop_native()) {
        /* nothing to load: the game's modules are native services (fileio, pad,
         * card, sound).  Ids 1.. and start result 0, as the HLE's LOADFILE. */
        (void)path;
        (void)argsz;
        (void)args;
        if (result)
            *result = 0;
        return ++N.modules;
    }
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    if (!g_lf_bound) {
        uint32_t tok;
        if (sif_rpc_bind(0x80000006u, &tok) < 0)
            return -1;
        g_lf_bound = 1;
        int32_t dummy = 0;
        sif_ee_rpc_sync(0x80000006u, 0xFF, NULL, 0, &dummy, 4);
    }
    uint8_t req[512];
    int32_t rep[2] = {-1, 0};
    memset(req, 0, sizeof req);
    if (argsz < 0)
        argsz = 0;
    if (argsz > 252)
        argsz = 252;
    memcpy(req, &argsz, 4);
    if (path)
        strncpy((char *)req + 4, path, 251);
    if (args && argsz)
        memcpy(req + 256, args, (size_t)argsz);
    if (sif_ee_rpc_sync(0x80000006u, 0, req, sizeof req, rep, 8) < 0)
        return -1;
    if (result)
        *result = rep[1];
    return rep[0];
#endif
}

int sceSifLoadModule(const char *path, int argsz, const char *args)
{
    return sceSifLoadStartModule(path, argsz, args, NULL);
}

int sceSifResetIop(const char *arg, int mode)
{
    RG_IOP_API("sceSifResetIop");
    (void)mode;
    if (rg_iop_native()) {
        (void)arg;
        N.modules = 0;
        return 1; /* no IOP to reboot */
    }
#if RG_IOP_ORACLE
    sif_ee_ensure_boot();
    sif_iop_reboot(arg);
    /* bindings and in-flight calls do not survive an IOP reboot */
    sif_ee_reset_clients();
    g_heap_bound = 0;
    g_lf_bound = 0;
    fio_reset_client();
    sdr_reset();
    return 1;
#endif
}

int sceSifRebootIop(const char *img) { RG_IOP_API("sceSifRebootIop"); return sceSifResetIop(img, 0); }

int sceSifSyncIop(void)
{
    RG_IOP_API("sceSifSyncIop");
    if (rg_iop_native())
        return 1;
#if RG_IOP_ORACLE
    if (sif_iop_booted())
        return 1;
    /* The game spins `while (!sceSifSyncIop());` with no kernel call: move time to
     * the boot event here so the loop terminates (a deliberate spin-site fix). */
    sif_ee_wait_idle();
    if (!B.use_kernel)
        sif_advance(sif_next_due() == UINT64_MAX ? 0 : sif_next_due() - sif_now());
    return sif_iop_booted();
#endif
}

int sceSifIsAliveIop(void)
{
    RG_IOP_API("sceSifIsAliveIop");
    return RG_IOP_PICK(1, sif_iop_booted());

}
