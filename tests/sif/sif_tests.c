/* SPDX-License-Identifier: CC0-1.0 */
/* SIF/IOP HLE tests (docs/SIF.md). Run one: rg-sif-tests <name>; all: no argument.
 * "<name>_control" runs a deliberately-wrong variant that must FAIL. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_iop.h"
#include "rg_iop_fio.h"
#include "iop.h"
#include "libsif.h"
#include "ps2k.h"
#include "sif.h"

static int g_fail;
static int g_control;

#define CHECK(c)                                                                       \
    do {                                                                               \
        if (!(c)) {                                                                    \
            fprintf(stderr, "  CHECK failed %s:%d: %s\n", __FILE__, __LINE__, #c);     \
            g_fail++;                                                                  \
        }                                                                              \
    } while (0)

/* report recorder */
static uint32_t g_rep[SIF_REP_KINDS];
static uint32_t g_rep_sid, g_rep_fno;
static void rec_report(int kind, uint32_t sid, uint32_t fno, const char *msg, void *u)
{
    (void)msg;
    (void)u;
    if (kind >= 0 && kind < SIF_REP_KINDS)
        g_rep[kind]++;
    g_rep_sid = sid;
    g_rep_fno = fno;
}

static void core_setup(uint64_t rpc_latency, uint64_t dma_setup, uint64_t dma_cpq)
{
    memset(g_rep, 0, sizeof g_rep);
    sif_set_report(rec_report, NULL);
    sif_config c;
    sif_default_config(&c);
    c.rpc_latency = rpc_latency;
    c.dma_setup = dma_setup;
    c.dma_cycles_per_qword = dma_cpq;
    sif_init(&c);
    sif_set_hooks(NULL);
    iop_reset();
    iop_log_clear();
}

/* ---- test servers ------------------------------------------------------------- */
static uint8_t g_echo_reply[256];
static uint32_t g_echo_calls;
/* fno 1: reply = send bytes reversed; fno 2: reply = {size, sum}; else unknown */
static void *srv_echo(sif_rpc_ctx *c, void *user)
{
    (void)user;
    g_echo_calls++;
    const uint8_t *d = (const uint8_t *)c->data;
    memset(g_echo_reply, 0, sizeof g_echo_reply);
    if (c->fno == 1) {
        for (uint32_t i = 0; i < c->size && i < sizeof g_echo_reply; i++)
            g_echo_reply[i] = d[c->size - 1 - i];
        return g_echo_reply;
    }
    if (c->fno == 2) {
        uint32_t sum = 0;
        for (uint32_t i = 0; i < c->size; i++)
            sum += d[i];
        memcpy(g_echo_reply, &c->size, 4);
        memcpy(g_echo_reply + 4, &sum, 4);
        return g_echo_reply;
    }
    c->unknown = 1;
    return NULL;
}

static int g_done_count;
static int g_done_order[8];
static void on_done(void *arg)
{
    if (g_done_count < 8)
        g_done_order[g_done_count] = (int)(intptr_t)arg;
    g_done_count++;
}

/* ---- dma_iop_ram ---------------------------------------------------------------- */
static void t_dma_iop_ram(void)
{
    core_setup(0, 100, 10);
    static uint8_t a[64], b[48];
    for (int i = 0; i < 64; i++)
        a[i] = (uint8_t)(i * 3 + 1);
    for (int i = 0; i < 48; i++)
        b[i] = (uint8_t)(0xA0 + i);
    sif_dma_xfer x[2] = {
        {(uint32_t)(uintptr_t)a, 0x00100000u, 64, 0},
        {(uint32_t)(uintptr_t)b, 0xBC100100u, 48, SIF_DMA_INT_O}, /* KSEG1/EE-mirror alias */
    };
    uint32_t id = sif1_dma(x, 2);
    CHECK(id != 0);
    uint32_t expect_addr = g_control ? 0x00100010u : 0x00100000u; /* control: wrong address */
    CHECK(memcmp(iop_ram() + expect_addr, a, 64) == 0);
    CHECK(memcmp(iop_ram() + 0x00100100u, b, 48) == 0);
    /* 4 + 3 qwords at 10 cycles + 100 setup = 170 cycles */
    CHECK(sif_dma_stat(id) > 0);
    sif_advance(169);
    CHECK(sif_dma_stat(id) > 0);
    sif_advance(1);
    CHECK(sif_dma_stat(id) < 0);
    CHECK(sif_get_stats()->dma1_bytes == 112);
    /* out of range: nothing copied, reported, id 0 */
    uint8_t before = iop_ram()[IOP_RAM_SIZE - 4];
    sif_dma_xfer bad[2] = {
        {(uint32_t)(uintptr_t)a, IOP_RAM_SIZE - 4, 4, 0},
        {(uint32_t)(uintptr_t)a, IOP_RAM_SIZE - 8, 16, 0},
    };
    CHECK(sif1_dma(bad, 2) == 0);
    CHECK(g_rep[SIF_REP_BAD_ADDR] == 1);
    CHECK(iop_ram()[IOP_RAM_SIZE - 4] == before);
    /* registers */
    CHECK((sif_reg_get(SIF_REG_SMFLAG) & SIF_STAT_BOOTEND) != 0);
    sif_reg_set(SIF_REG_MSFLAG, 0x10);
    sif_reg_set(SIF_REG_MSFLAG, 0x01);
    CHECK(sif_reg_get(SIF_REG_MSFLAG) == 0x11);
    sif_reg_set(SIF_REG_SMFLAG, SIF_STAT_BOOTEND); /* EE write clears */
    CHECK((sif_reg_get(SIF_REG_SMFLAG) & SIF_STAT_BOOTEND) == 0);
    sif_reg_set(SIF_SREG_BASE | 3, 0xDEADBEEF);
    CHECK(sif_reg_get(SIF_SREG_BASE | 3) == 0xDEADBEEF);
    /* heap */
    uint32_t h1 = iop_heap_alloc(0x1004), h2 = iop_heap_alloc(0x10);
    CHECK(h1 == IOP_HEAP_BASE && h2 == IOP_HEAP_BASE + 0x1100);
    CHECK(iop_heap_free(h1) == 0);
    CHECK(iop_heap_alloc(0x800) == IOP_HEAP_BASE); /* first fit reuses the hole */
    CHECK(iop_heap_free(0x12345) == -1);
}

/* ---- rpc_call ---------------------------------------------------------------------- */
static void t_rpc_call(void)
{
    core_setup(0, 0, 0);
    CHECK(sif_server_register(0x7001u, "echo", 0x100, srv_echo, NULL) == 0);
    uint32_t tok = 0;
    CHECK(sif_rpc_bind(0x7001u, &tok) == 0 && tok != 0);
    uint8_t send[8] = {1, 2, 3, 4, 5, 6, 7, 8}, recv[8];
    memset(recv, 0xEE, sizeof recv);
    sif_call c = {0x7001u, 1, send, 8, recv, 8, on_done, (void *)1};
    g_done_count = 0;
    uint32_t t = sif_rpc_call(&c);
    CHECK(t != 0);
    CHECK(g_echo_calls == 1);
    /* the server's buffer in IOP RAM holds the send data */
    const sif_server_info *si = sif_server_find(0x7001u);
    CHECK(si && si->buf_iop >= IOP_STATIC_BASE && si->buf_iop < IOP_HEAP_BASE);
    CHECK(si && memcmp(iop_ram() + si->buf_iop, send, 8) == 0);
    /* the reply is not visible before delivery, even with zero latency */
    CHECK(recv[0] == 0xEE && sif_rpc_busy(t) == 1 && g_done_count == 0);
    CHECK(sif_deliver() == 1);
    CHECK(recv[0] == 8 && recv[7] == 1 && sif_rpc_busy(t) == 0 && g_done_count == 1);
    /* fno 2 */
    uint32_t r2[2] = {0, 0};
    sif_call c2 = {0x7001u, 2, send, 8, r2, 8, NULL, NULL};
    sif_rpc_call(&c2);
    sif_deliver();
    CHECK(r2[0] == 8 && r2[1] == 36);
    CHECK(sif_call_count(0x7001u, 1) == 1 && sif_call_count(0x7001u, 2) == 1);
    CHECK(sif_call_log_get(0)->fno == 2 && sif_call_log_get(1)->fno == 1);
}

/* ---- rpc_async: latency, FIFO, end function ------------------------------------------ */
static void t_rpc_async(void)
{
    core_setup(1000, 0, 0);
    sif_server_register(0x7001u, "echo", 0x100, srv_echo, NULL);
    uint8_t s1[4] = {1, 2, 3, 4}, s2[4] = {9, 8, 7, 6}, r1[4] = {0}, r2[4] = {0};
    g_done_count = 0;
    sif_call c1 = {0x7001u, 1, s1, 4, r1, 4, on_done, (void *)1};
    sif_call c2 = {0x7001u, 1, s2, 4, r2, 4, on_done, (void *)2};
    uint32_t t1 = sif_rpc_call(&c1);
    sif_advance(10);
    uint32_t t2 = sif_rpc_call(&c2);
    if (g_control)
        sif_deliver_all(); /* control: completes early, ignoring latency */
    sif_advance(989);
    CHECK(sif_rpc_busy(t1) == 1 && sif_rpc_busy(t2) == 1 && g_done_count == 0 && r1[0] == 0);
    sif_advance(1);
    CHECK(sif_rpc_busy(t1) == 0 && sif_rpc_busy(t2) == 1 && g_done_count == 1 && r1[0] == 4);
    sif_advance(10);
    CHECK(sif_rpc_busy(t2) == 0 && g_done_count == 2 && r2[0] == 6);
    CHECK(g_done_order[0] == 1 && g_done_order[1] == 2);
    CHECK(sif_now() == 1010);
}

/* ---- registry --------------------------------------------------------------------- */
static void *srv_other(sif_rpc_ctx *c, void *user)
{
    (void)c;
    static uint32_t r = 0x51;
    (void)user;
    return &r;
}

static void t_registry(void)
{
    core_setup(0, 0, 0);
    CHECK(sif_server_count() == 0);
    sif_server_register(0x7001u, "echo", 0x40, srv_echo, NULL);
    sif_server_register(0x7002u, "other", 0, srv_other, NULL);
    CHECK(sif_server_count() == 2);
    uint32_t b1 = sif_server_find(0x7001u)->buf_iop;
    /* replace keeps the slot and the buffer */
    sif_server_register(0x7001u, "echo2", 0x40, srv_other, NULL);
    CHECK(sif_server_count() == 2 && sif_server_find(0x7001u)->buf_iop == b1);
    CHECK(strcmp(sif_server_find(0x7001u)->name, "echo2") == 0);
    uint32_t r = 0;
    sif_call c = {0x7001u, 9, NULL, 0, &r, 4, NULL, NULL};
    sif_rpc_call(&c);
    sif_deliver();
    CHECK(r == 0x51);
    /* send larger than the buffer: clipped and reported */
    sif_server_register(0x7001u, "echo", 0x40, srv_echo, NULL);
    uint8_t big[0x80];
    memset(big, 1, sizeof big);
    uint32_t r2[2] = {0, 0};
    sif_call c2 = {0x7001u, 2, big, sizeof big, r2, 8, NULL, NULL};
    sif_rpc_call(&c2);
    sif_deliver();
    CHECK(g_rep[SIF_REP_TRUNCATED] == 1 && r2[0] == 0x40 && r2[1] == 0x40);
    CHECK(sif_server_unregister(0x7002u) == 0 && sif_server_count() == 1 && !sif_server_find(0x7002u));
    CHECK(sif_server_unregister(0x7002u) == -1);
    /* the HLE set */
    CHECK(iop_hle_install(NULL) == 0);
    const uint32_t sids[] = {0x80000001u, 0x80000003u, 0x80000006u, 0x80000100u, 0x80000101u,
                             0x80000400u, 0x80000701u, 0x00123456u};
    for (size_t i = 0; i < sizeof sids / sizeof sids[0]; i++)
        CHECK(sif_server_find(sids[i]) != NULL);
    /* a reboot keeps the servers and re-reserves their buffers */
    sif_iop_reboot("cdrom0:\\MODULES\\IOPRP300.IMG;1");
    CHECK(sif_server_find(0x80000001u) && sif_server_find(0x80000001u)->buf_iop != 0);
    CHECK(sif_iop_booted() && iop_reboot_count() == 1);
}

/* ---- unknown server / function ------------------------------------------------------ */
static void t_unknown(void)
{
    core_setup(0, 0, 0);
    sif_server_register(0x7001u, "echo", 0x40, srv_echo, NULL);
    uint32_t tok = 123;
    CHECK(sif_rpc_bind(0x7FFFu, &tok) == -1 && tok == 0);
    CHECK(g_rep[SIF_REP_UNKNOWN_SERVER] == 1 && g_rep_sid == 0x7FFFu);
    uint32_t r = 0xAAAA;
    g_done_count = 0;
    sif_call c = {0x7FFFu, 3, NULL, 0, &r, 4, on_done, NULL};
    CHECK(sif_rpc_call(&c) == 0);
    sif_deliver();
    CHECK(g_rep[SIF_REP_UNKNOWN_SERVER] == 2 && g_rep_fno == 3);
    CHECK(r == 0xAAAA && g_done_count == 1); /* untouched, but the waiter is released */
    CHECK(sif_call_log_get(0)->status == 1);
    sif_call c2 = {0x7001u, 0x55, NULL, 0, &r, 4, NULL, NULL};
    CHECK(sif_rpc_call(&c2) != 0);
    sif_deliver();
    CHECK(g_rep[SIF_REP_UNKNOWN_FNO] == 1 && g_rep_sid == 0x7001u && g_rep_fno == 0x55);
    CHECK(sif_call_log_get(0)->status == 2 && sif_server_find(0x7001u)->unknown_calls == 1);
    CHECK(sif_iop_call_ee(0x80000704u, 0, NULL, 0) == -1 && g_rep[SIF_REP_NO_EE_SERVER] == 1);
    CHECK(sif_iop_send_cmd(0x12, NULL, 0) == -1 && g_rep[SIF_REP_NO_HANDLER] == 1);
    /* unknown module still loads (recorded, flagged) */
    iop_set_report(NULL);
    CHECK(iop_module_load("cdrom0:\\MODULES\\FOO.IRX;1", NULL, 0) == 1);
    CHECK(iop_module_get(0)->known == 0 && strcmp(iop_module_get(0)->name, "FOO") == 0);
}

/* ---- SDK end to end on the EE kernel ------------------------------------------------- */
static const char *g_tmpdir;
static int g_end_in_handler = -1, g_end_calls;
static void sdk_end(void *p)
{
    g_end_calls++;
    g_end_in_handler = ps2k_in_handler();
    *(int *)p = 1;
}
static int g_spu2_arg = -1;
static int spu2_cb(int bits, void *common)
{
    g_spu2_arg = bits + (int)(intptr_t)common;
    return 0;
}

static const char *const k_mods[] = {"sio2man", "padman", "mcman", "mcserv", "libsd", "sdrdrv", "modhsyn", "modmidi",
                                     "modmsin", "cdvdstm", "sksound", "skhsynth", "skmidi", "skmsin", "pcmplay"};

static void sdk_main(void *arg)
{
    (void)arg;
    /* IOP reboot + sync, as IopRebootWithImage */
    while (!sceSifRebootIop_11fcd0("cdrom0:\\MODULES\\IOPRP300.IMG;1")) {
    }
    uint64_t t0 = ps2k_now();
    while (!sceSifSyncIop_11fc80()) {
    }
    CHECK(ps2k_now() - t0 >= 5000); /* boot_latency */
    sceSifInitRpc_119b60(0);
    CHECK(sceSifInitIopHeap() == 0);
    sceFsReset();

    /* modules, as LoadIopModules */
    for (size_t i = 0; i < sizeof k_mods / sizeof k_mods[0]; i++) {
        char p[128];
        snprintf(p, sizeof p, "cdrom0:\\MODULES\\%s", k_mods[i]);
        for (char *q = p + 16; *q; q++)
            if (*q >= 'a' && *q <= 'z')
                *q = (char)(*q - 32);
        strcat(p, ".IRX;1");
        const char *args = i == 12 ? "maxtrack=5\0maxentry=16" : NULL;
        CHECK(sceSifLoadModule_11f7a0(p, args ? 0x16 : 0, args) == (int)i + 1);
    }
    CHECK(iop_module_count() == 15 && iop_module_find("SKMIDI") &&
          strcmp(iop_module_find("SKMIDI")->args, "maxtrack=5|maxentry=16") == 0);
    for (int i = 0; i < iop_module_count(); i++)
        CHECK(iop_module_get(i)->known);

    /* bind: the game polls client+0x24 */
    static sceSifClientData cd;
    do {
        CHECK(sceSifBindRpc(&cd, 0x123456, 0) >= 0);
    } while (((volatile uint32_t *)&cd)[9] == 0);
    CHECK((void *)((uint32_t *)&cd)[9] == (void *)cd.serve);

    /* iop heap + SIF DMA, as SoundRpcInit / SifDmaSendSync */
    uint32_t iaddr = (uint32_t)(uintptr_t)sceSifAllocIopHeap(0x1004);
    CHECK(iaddr >= IOP_HEAP_BASE && iaddr < IOP_HEAP_END && (iaddr & 0xFF) == 0);
    static uint8_t blk[0x1000];
    for (int i = 0; i < 0x1000; i++)
        blk[i] = (uint8_t)(i ^ 0x5A);
    sceSifDmaData d = {(unsigned)(uintptr_t)blk, iaddr, 0x1000, 0};
    unsigned id = sceSifSetDma(&d, 1);
    CHECK(id != 0);
    int polls = 0;
    while (sceSifDmaStat(id) >= 0) {
        ps2k_delay_thread(10);
        polls++;
    }
    CHECK(polls >= 1); /* 256 qwords * 4 + 2000 cycles > one 10 us delay */
    CHECK(memcmp(iop_ram() + iaddr, blk, 0x1000) == 0);
    CHECK(sceSifFreeSysMemory_11ea40((void *)(uintptr_t)iaddr) == 0);

    /* synchronous call: blocks for the latency, end function runs in handler context */
    static uint32_t buf[16];
    int flag = 0;
    buf[0] = 0x12345678;
    uint64_t t1 = ps2k_now();
    sceSifCallRpc(&cd, 0x8000, 0, buf, 0x40, buf, 0x40, sdk_end, &flag);
    CHECK(ps2k_now() - t1 >= 50000);
    CHECK(flag == 1 && g_end_in_handler == 1 && buf[0] == 0); /* placeholder replies zeros */

    /* asynchronous call: CheckStatRpc busy until the SIF0 interrupt */
    flag = 0;
    buf[0] = 0x777;
    sceSifCallRpc(&cd, 0x8090, SIF_RPCM_NOWAIT, buf, 0x40, buf, 0x40, sdk_end, &flag);
    CHECK(sceSifCheckStatRpc(&cd.rpcd) == 1 && flag == 0 && buf[0] == 0x777);
    int waits = 0;
    while (sceSifCheckStatRpc(&cd.rpcd)) {
        ps2k_delay_thread(100);
        waits++;
    }
    CHECK(waits >= 1 && flag == 1 && g_end_in_handler == 1 && buf[0] == 0);
    CHECK(sif_call_count(0x123456, 0x8090) == 1);

    /* FILEIO */
    int fd = sceOpen_11b928("host0:SIF_FIO_TEST.BIN", SCE_WRONLY | SCE_CREAT | SCE_TRUNC);
    if (fd < 0)
        fprintf(stderr, "  open for write -> %d\n", fd);
    CHECK(fd >= 0);
    CHECK(sceWrite_11c1e0(fd, "PS2-SIF-FILEIO!", 15) == 15);
    CHECK(sceClose_11bbb8(fd) == 0);
    fd = sceOpen_11b928("cdrom0:\\SIF_FIO_TEST.BIN;1", SCE_RDONLY);
    CHECK(fd >= 0);
    CHECK(sceLseek_11bd30(fd, 0, SCE_SEEK_END) == 15);
    CHECK(sceLseek_11bd30(fd, 4, SCE_SEEK_SET) == 4);
    char rb[32] = {0};
    CHECK(sceRead_11bf70(fd, rb, 32) == 11 && memcmp(rb, "SIF-FILEIO!", 11) == 0);
    CHECK(sceClose_11bbb8(fd) == 0);
    CHECK(sceOpen_11b928("cdrom0:\\NOPE.BIN;1", SCE_RDONLY) < 0);
    CHECK(sceOpen_11b928("mc0:/BASLUS/x", SCE_RDONLY) < 0);

    /* libsdr: sdremote to the sdr_driver placeholder, then an IOP -> EE callback */
    CHECK(sceSdRemoteInit_122890(0) == 0);
    int cbt = sceSdRemoteCallbackInit_122d70(10);
    CHECK(cbt > 0);
    CHECK(sceSdRemote_1229e8(1, 0x8010, 0x980, 0x3FFF) == 0);
    CHECK(sif_call_count(0x80000701u, 0x8010) == 1 && sif_call_count(0x80000701u, 0xE620) == 1);
    static uint32_t blk64[16] = {0, 2, 7};
    CHECK(sceSdRemote_1229e8(1, 0x90F0, blk64, 0x40) == 0);
    CHECK(sif_call_count(0x80000701u, 0x90F0) == 1);
    CHECK(sceSdRemote_1229e8(1, 0x8170, spu2_cb, 100) == 0); /* old handler NULL */
    uint32_t cbmsg[2] = {0x400, 7};
    CHECK(sif_iop_call_ee(0x80000704u, 0, cbmsg, 8) == 0);
    ps2k_delay_thread(1000); /* the callback thread (prio 10) runs when main blocks */
    CHECK(g_spu2_arg == 107);
    sceSdRemoteCallbackQuit_122e70();
}

static void t_sdk_kernel(void)
{
    memset(g_rep, 0, sizeof g_rep);
    sif_set_report(rec_report, NULL);
    ps2k_config kc;
    ps2k_default_config(&kc);
    kc.vblank_enable = 0;
    CHECK(ps2k_init(&kc) == 0);
    rg_sif_boot_config bc;
    rg_sif_default_boot_config(&bc);
    bc.cdrom_root = g_tmpdir;
    bc.host_root = g_tmpdir;
    bc.rpc_latency = 50000;
    bc.dma_setup = 2000;
    bc.dma_cycles_per_qword = 4;
    bc.boot_latency = 5000;
    CHECK(rg_sif_boot(&bc) == 0);
    int r = ps2k_run(sdk_main, NULL, 50);
    CHECK(r == PS2K_RUN_MAIN_EXIT);
    for (int k = 0; k < SIF_REP_KINDS; k++)
        if (g_rep[k] && k != SIF_REP_OTHER)
            fprintf(stderr, "  unexpected report kind %d x%u\n", k, g_rep[k]);
    CHECK(g_rep[SIF_REP_UNKNOWN_SERVER] == 0 && g_rep[SIF_REP_UNKNOWN_FNO] == 0);
    if (getenv("RG_SIF_DUMP"))
        iop_module_dump(stdout);
}


/* ---- RG_IOP=native: the SDK answers without the HLE (docs/NATIVE-IOP.md) ----------------
 * The game's boot sequence (IopRebootWithImage, LoadIopModules), the register reads, the
 * fileio round trip through host0:/cdrom0: and the "no IOP" answers for RPC / DMA / heap /
 * sdremote, on the kernel, with no rg_sif_boot: the HLE entry counter must stay 0.
 * Control: one HLE call (sif_reg_get) must show up in the counter. */
static int g_nend;
static void native_end(void *p) { (void)p; g_nend++; }
static void m_native_sdk(void *a)
{
    (void)a;
    uint64_t hle0 = rg_iop_hle_total();
    CHECK(sceSifRebootIop_11fcd0("rom0:UDNL cdrom0:\\MODULES\\IOPRP300.IMG;1") == 1);
    CHECK(sceSifSyncIop_11fc80() == 1);
    sceSifInitRpc_119b60(0);
    CHECK(sceSifInitIopHeap() == 0);
    CHECK(sceFsReset() == 0);
    for (int i = 0; i < 15; i++)
        CHECK(sceSifLoadModule_11f7a0("cdrom0:\\MODULES\\X.IRX;1", 0, NULL) == i + 1);
    CHECK(sceSifIsAliveIop() == 1);
    CHECK(((unsigned)sceSifGetReg(SIF_REG_SMFLAG) & 0x70000u) == 0x70000u); /* booted */
    sceSifSetReg(SIF_REG_SMFLAG, 0x10000);                                   /* EE writes clear */
    CHECK(((unsigned)sceSifGetReg(SIF_REG_SMFLAG) & 0x70000u) == 0x60000u);
    sceSifSetSreg(3, 0xABCD);
    CHECK(sceSifGetSreg(3) == 0xABCD);
    /* fileio: host files directly */
    int fd = sceOpen_11b928("host0:SIF_NATIVE_FIO.BIN", SCE_WRONLY | SCE_CREAT | SCE_TRUNC);
    CHECK(fd >= 1);
    CHECK(sceWrite_11c1e0(fd, "NATIVE-FILEIO!", 14) == 14);
    CHECK(sceClose_11bbb8(fd) == 0);
    fd = sceOpen_11b928("cdrom0:\\SIF_NATIVE_FIO.BIN;1", SCE_RDONLY);
    CHECK(fd >= 1);
    CHECK(sceLseek_11bd30(fd, 0, SCE_SEEK_END) == 14);
    CHECK(sceLseek_11bd30(fd, 7, SCE_SEEK_SET) == 7);
    char rb[32] = {0};
    CHECK(sceRead_11bf70(fd, rb, 32) == 7 && memcmp(rb, "FILEIO!", 7) == 0);
    CHECK(sceClose_11bbb8(fd) == 0 && sceClose_11bbb8(fd) < 0);
    CHECK(sceOpen_11b928("cdrom0:\\NOPE.BIN;1", SCE_RDONLY) < 0);
    CHECK(sceOpen_11b928("mc0:/BASLUS/x", SCE_RDONLY) < 0);
    /* no IOP server: bind answers (the game polls +0x24), calls run their end function,
     * DMA completes at once, heap handles are aligned budget handles; all counted */
    uint64_t unc0 = rg_iop_unconverted_total();
    static sceSifClientData cd;
    CHECK(sceSifBindRpc(&cd, 0x123456, 0) == 0 && ((volatile uint32_t *)&cd)[9] != 0);
    static uint32_t buf[16];
    buf[0] = 0x55;
    g_nend = 0;
    CHECK(sceSifCallRpc(&cd, 0x8000, 0, buf, 0x40, buf, 0x40, native_end, NULL) == 0);
    CHECK(g_nend == 1 && buf[0] == 0x55 && sceSifCheckStatRpc(&cd.rpcd) == 0);
    uint32_t h = (uint32_t)(uintptr_t)sceSifAllocIopHeap(0x1004);
    CHECK(h != 0 && (h & 0xFF) == 0);
    sceSifDmaData d = {(unsigned)(uintptr_t)buf, h, 0x40, 0};
    unsigned id = sceSifSetDma(&d, 1);
    CHECK(id != 0 && sceSifDmaStat(id) < 0);
    CHECK(sceSdRemoteInit_122890(0) == 0 && sceSdRemote_1229e8(1, 0x8010, 0x980, 0x3FFF) == 0);
    CHECK(rg_iop_unconverted_total() - unc0 >= 6);
    if (g_control)
        (void)sif_reg_get(SIF_REG_SMFLAG); /* control: one HLE entry */
    uint64_t hle = rg_iop_hle_total() - hle0;
    if (hle)
        fprintf(stderr, "  %llu HLE entries in native mode\n", (unsigned long long)hle);
    CHECK(hle == 0);
    CHECK(rg_iop_hle_count("sif_rpc_call") == 0 && rg_iop_api_count("sceSifLoadStartModule") >= 15);
}

static void t_native_sdk(void)
{
    ps2k_config kc;
    ps2k_default_config(&kc);
    kc.vblank_enable = 0;
    CHECK(ps2k_init(&kc) == 0);
    rg_iop_set_mode(RG_IOP_MODE_NATIVE);
    rg_fio_set_roots(g_tmpdir, g_tmpdir);
    int r = ps2k_run(m_native_sdk, NULL, 50);
    CHECK(r == PS2K_RUN_MAIN_EXIT);
    rg_iop_set_mode(RG_IOP_MODE_HLE);
}

static const struct {
    const char *name;
    void (*fn)(void);
} tests[] = {
    {"dma_iop_ram", t_dma_iop_ram}, {"rpc_call", t_rpc_call}, {"rpc_async", t_rpc_async},
    {"registry", t_registry},       {"unknown", t_unknown},   {"sdk_kernel", t_sdk_kernel},
    {"native_sdk", t_native_sdk},
};

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    rg_iop_set_mode(RG_IOP_MODE_HLE); /* this suite tests the SIF/IOP HLE itself (docs/NATIVE-IOP.md) */
    g_tmpdir = getenv("RG_SIF_TMP");
    if (!g_tmpdir)
        g_tmpdir = ".";
    int ran = 0;
    for (size_t i = 0; i < sizeof tests / sizeof tests[0]; i++) {
        char ctl[64];
        snprintf(ctl, sizeof ctl, "%s_control", tests[i].name);
        int want = argc < 2 || strcmp(argv[1], tests[i].name) == 0;
        int want_ctl = argc >= 2 && strcmp(argv[1], ctl) == 0;
        if (!want && !want_ctl)
            continue;
        g_control = want_ctl;
        int before = g_fail;
        tests[i].fn();
        printf("%-24s %s\n", want_ctl ? ctl : tests[i].name, g_fail == before ? "PASS" : "FAIL");
        ran++;
    }
    if (!ran) {
        fprintf(stderr, "unknown test '%s'\n", argc > 1 ? argv[1] : "");
        return 2;
    }
    return g_fail ? 1 : 0;
}
