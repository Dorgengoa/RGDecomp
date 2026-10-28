/* SPDX-License-Identifier: CC0-1.0 */
/* Pad + memory card HLE tests (docs/PADMC.md). Run one: rg-padmc-tests <name>;
 * "<name>_control" runs a deliberately-wrong variant that must FAIL.
 * Every test runs on the EE kernel HLE (virtual clock, VBlanks) with the SIF boot.
 *
 * RG_IOP=native in the environment runs libpad / libmc on the native pad and save
 * services instead of padman / mcserv (docs/NATIVE-IOP.md; ctest padmc.native.*); the
 * checks of HLE internals (DMA buffer bytes, SIF call counts) apply to hle only.
 * `npad_equiv` runs both services side by side in one process. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif

#include "libmc.h"
#include "libpad.h"
#include "libsif.h"
#include "mccard.h"
#include "mcserv.h"
#include "padman.h"
#include "ps2k.h"
#include "rg_iop.h"
#include "rg_npad.h"
#include "sif.h"

static int g_fail;
static int g_control;
static int g_native; /* RG_IOP=native: libpad / libmc on the native services */
static const char *g_tmp = ".";

#define CHECK(c)                                                                   \
    do {                                                                           \
        if (!(c)) {                                                                \
            fprintf(stderr, "  CHECK failed %s:%d: %s\n", __FILE__, __LINE__, #c); \
            g_fail++;                                                              \
        }                                                                          \
    } while (0)

/* ---- helpers ------------------------------------------------------------------------ */
static void rmtree(const char *dir)
{
#ifdef _WIN32
    char pat[1024];
    snprintf(pat, sizeof pat, "%s/*", dir);
    struct _finddata_t fd;
    intptr_t h = _findfirst(pat, &fd);
    if (h != -1) {
        do {
            if (!strcmp(fd.name, ".") || !strcmp(fd.name, ".."))
                continue;
            char p[1024];
            snprintf(p, sizeof p, "%s/%s", dir, fd.name);
            if (fd.attrib & _A_SUBDIR)
                rmtree(p);
            else
                remove(p);
        } while (_findnext(h, &fd) == 0);
        _findclose(h);
    }
    _rmdir(dir);
#else
    DIR *d = opendir(dir);
    if (d) {
        struct dirent *e;
        while ((e = readdir(d))) {
            if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
                continue;
            char p[1024];
            snprintf(p, sizeof p, "%s/%s", dir, e->d_name);
            struct stat st;
            if (stat(p, &st) == 0 && S_ISDIR(st.st_mode))
                rmtree(p);
            else
                remove(p);
        }
        closedir(d);
    }
    rmdir(dir);
#endif
}

static void tmpdir(const char *name, char *out, int n, int wipe)
{
    snprintf(out, (size_t)n, "%s/padmc_%s", g_tmp, name);
    if (wipe)
        rmtree(out);
}

static uint64_t g_violations;
static void on_violation(const char *call, const char *why)
{
    fprintf(stderr, "  kernel violation: %s: %s\n", call, why);
    g_violations++;
}

static void boot(int vblank, uint64_t rpc_latency)
{
    ps2k_config kc;
    ps2k_default_config(&kc);
    kc.vblank_enable = vblank;
    kc.stop_at_cycles = 147456000ull * 600; /* 10 virtual minutes: a hang fails, never stalls ctest */
    CHECK(ps2k_init(&kc) == 0);
    ps2k_set_violation_hook(on_violation);
    rg_sif_boot_config bc;
    rg_sif_default_boot_config(&bc);
    bc.cdrom_root = g_tmp;
    bc.host_root = g_tmp;
    bc.rpc_latency = rpc_latency;
    CHECK(rg_sif_boot(&bc) == 0);
}

static void run_main(void (*fn)(void *))
{
    int r = ps2k_run(fn, NULL, 50);
    if (r != PS2K_RUN_MAIN_EXIT)
        fprintf(stderr, "  ps2k_run -> %d\n", r);
    CHECK(r == PS2K_RUN_MAIN_EXIT);
    CHECK(g_violations == 0);
}

/* VBlank wait for test threads (what sceGsSyncV(0) does for the game) */
static int g_vsema = -1;
static int vb_handler(int cause)
{
    (void)cause;
    ps2k_signal_sema(g_vsema, 1);
    return 0;
}
static void vsync_setup(void)
{
    g_vsema = ps2k_create_sema(0, 1, 0, 0);
    ps2k_add_intc_handler(PS2K_INTC_VBLANK_START, vb_handler, 0);
    ps2k_enable_intc(PS2K_INTC_VBLANK_START, 0);
}
static void vsync(void)
{
    while (ps2k_poll_sema(g_vsema, 0) >= 0) {
    }
    ps2k_wait_sema(g_vsema);
}
/* used by the game's own pad code (PadWaitReady_1849e0, PadPortOpen_184ed0) */
void sceGsSyncV(int mode)
{
    (void)mode;
    vsync();
}

static uint8_t g_buf0[256] __attribute__((aligned(64)));
static uint8_t g_buf1[256] __attribute__((aligned(64)));

/* pad service of the run (padman for hle, rg_npad for native) */
typedef struct pinfo {
    int locked, mode_id;
    uint8_t align[6];
} pinfo;
static void pad_reset(int keep_lock)
{
    if (g_native) {
        rg_npad_config c;
        rg_npad_default_config(&c);
        c.keep_analog_lock = keep_lock;
        rg_npad_reset(&c);
    } else {
        padman_config c;
        padman_default_config(&c);
        c.keep_analog_lock = keep_lock;
        padman_reset(&c);
    }
}
static void pad_info(int port, pinfo *o)
{
    memset(o, 0, sizeof *o);
    if (g_native) {
        rg_npad_info i;
        rg_npad_port_get(port, &i);
        o->locked = i.locked;
        o->mode_id = i.mode_id;
        memcpy(o->align, i.align, 6);
    } else {
        padman_port_info i;
        padman_port_get(port, &i);
        o->locked = i.locked;
        o->mode_id = i.mode_id;
        memcpy(o->align, i.align, 6);
    }
}
static int pad_cmd_frames(void) { return g_native ? 3 : padman_get_config()->cmd_frames; }

/* the game's decode (PadReadData_184df0): active-high word + sticks */
typedef struct decoded {
    int word, rx, ry, lx, ly, mode;
} decoded;
static int decode(const uint8_t *d, int len, decoded *o)
{
    memset(o, 0, sizeof *o);
    if (len <= 0 || d[0] != 0)
        return 0;
    int n = (d[1] & 0xF) * 2;
    o->word = n >= 2 ? (((d[2] << 8) | d[3]) ^ 0xFFFF) & 0xFFFF : 0;
    if (n >= 6) {
        o->rx = d[4];
        o->ry = d[5];
        o->lx = d[6];
        o->ly = d[7];
    }
    o->mode = d[1] >> 4;
    return 1;
}

static void pad_up(void)
{
    memset(g_buf0, 0, sizeof g_buf0); /* .bss at boot */
    memset(g_buf1, 0, sizeof g_buf1);
    vsync_setup();
    vsync();
    CHECK(scePadInit(0) == 1);
}

/* step until STABLE (or give up) */
static int wait_state(int port, int want, int max)
{
    for (int i = 0; i < max; i++) {
        if (scePadGetState(port, 0) == want)
            return i;
        vsync();
    }
    return -1;
}

/* ---- pad: state machine ------------------------------------------------------------- */
static void m_pad_stable(void *a)
{
    (void)a;
    pad_up();
    CHECK(scePadGetState(0, 0) == scePadStateClosed); /* retail: 99 when not open */
    CHECK(scePadPortOpen(0, 0, g_buf0 + 4) == 0);       /* not 64-byte aligned */
    CHECK(scePadPortOpen(0, 0, g_buf0) == 1);
    CHECK(scePadPortOpen(0, 0, g_buf0) == 0);           /* already open */
    CHECK(scePadPortOpen(1, 0, g_buf1) == 1);
    int seq[8];
    for (int i = 0; i < 8; i++) {
        seq[i] = scePadGetState(0, 0);
        vsync();
    }
    /* open frame: libpad's init (EXECCMD); +1 FINDPAD; +2,+3 FINDCTP1; +4 STABLE */
    int want[8] = {5, 1, 2, 2, 6, 6, 6, 6};
    if (g_control)
        want[1] = 6; /* control: STABLE right after open */
    for (int i = 0; i < 8; i++) {
        if (seq[i] != want[i])
            fprintf(stderr, "  frame +%d: state %d want %d\n", i, seq[i], want[i]);
        CHECK(seq[i] == want[i]);
    }
    CHECK(scePadGetState(1, 0) == scePadStateDiscon); /* nothing in port 2 */
    CHECK(scePadInfoMode(1, 0, InfoModeCurID, 0) == 0);
    /* DS2 powers up digital: the game's phase 0 -> 0x28 path */
    CHECK(scePadInfoMode(0, 0, InfoModeCurID, 0) == 4);
    CHECK(scePadInfoMode(0, 0, InfoModeCurExID, 0) == 4);
    CHECK(scePadInfoMode(0, 0, InfoModeIdTable, -1) == 2);
    CHECK(scePadInfoMode(0, 0, InfoModeIdTable, 1) == 7);
    CHECK(scePadInfoMode(0, 0, InfoModeIdTable, 2) == 0);
    unsigned char rd[32];
    /* length 0x20 in every mode (VALIDATION.md 4; measured in 0x73, assumed for 0x41) */
    CHECK(scePadRead(0, 0, rd) == 32 && rd[0] == 0 && rd[1] == 0x41);
    /* SetMainMode(analog, lock): BUSY -> EXECCMD for cmd_frames, then STABLE */
    CHECK(scePadSetMainMode(0, 0, 1, 3) == 1);
    CHECK(scePadGetReqState(0, 0) == scePadReqStateBusy);
    CHECK(scePadGetState(0, 0) == scePadStateExecCmd);
    CHECK(scePadInfoMode(0, 0, InfoModeCurID, 0) == 0); /* busy: no mode info */
    int n = wait_state(0, scePadStateStable, 10);
    CHECK(n == pad_cmd_frames());
    CHECK(scePadGetReqState(0, 0) == scePadReqStateComplete);
    CHECK(scePadInfoMode(0, 0, InfoModeCurID, 0) == 7);
    CHECK(scePadInfoMode(0, 0, InfoModeCurExID, 0) == 7);
    CHECK(scePadInfoAct(0, 0, -1, 0) == 2);
    /* actData as the real padman fills it (VALIDATION.md 4): 01 02 00 0a, 01 01 01 14 */
    CHECK(scePadInfoAct(0, 0, 0, InfoActFunc) == 1 && scePadInfoAct(0, 0, 0, InfoActSub) == 2);
    CHECK(scePadInfoAct(0, 0, 0, InfoActSize) == 0 && scePadInfoAct(0, 0, 0, InfoActCurr) == 10);
    CHECK(scePadInfoAct(0, 0, 1, InfoActFunc) == 1 && scePadInfoAct(0, 0, 1, InfoActSub) == 1);
    CHECK(scePadInfoAct(0, 0, 1, InfoActSize) == 1 && scePadInfoAct(0, 0, 1, InfoActCurr) == 20);
    CHECK(scePadInfoAct(0, 0, 2, InfoActSize) == 0);
    unsigned char align[6] = {0, 1, 0xFF, 0xFF, 0xFF, 0xFF};
    CHECK(scePadSetActAlign(0, 0, align) == 1);
    CHECK(scePadGetState(0, 0) == scePadStateExecCmd);
    CHECK(scePadSetMainMode(0, 0, 0, 3) == 0); /* one command at a time */
    CHECK(wait_state(0, scePadStateStable, 10) > 0);
    pinfo pi;
    pad_info(0, &pi);
    CHECK(pi.locked == 1 && pi.mode_id == 0x73 && pi.align[0] == 0 && pi.align[1] == 1);
    /* VALIDATION.md 4: scePadRead returns and copies 32 bytes in 0x73:
     * 00 73 btn btn rx ry lx ly, zeros, byte 31 = 0x5A */
    memset(rd, 0xEE, sizeof rd);
    CHECK(scePadRead(0, 0, rd) == 32 && rd[0] == 0 && rd[1] == 0x73);
    CHECK(rd[2] == 0xFF && rd[3] == 0xFF && rd[31] == 0x5A);
    for (int i = 8; i < 31; i++)
        CHECK(rd[i] == 0);
    /* InfoMode byte sources (retail 0x12BCA0) */
    CHECK(scePadInfoMode(0, 0, InfoModeCurExOffs, 0) == 1);
    CHECK(scePadInfoMode(0, 0, InfoModeIdTable, 0) == 4);
    /* DMA buffer bytes as the real padman's (VALIDATION.md 4 table): hle only, the
     * native service has no DMA buffer (the buffer stays as the test left it) */
    if (!g_native) {
        const uint8_t *h = padman_newest_half(g_buf0);
        static const uint8_t act[16] = {1, 2, 0, 10, 1, 1, 1, 20, 0, 0, 0, 0, 0, 0, 0, 0};
        static const uint8_t x40[4] = {2, 0, 1, 0}, x50[4] = {4, 0, 7, 0};
        static const uint8_t x64[12] = {2, 0x73, 3, 1, 2, 1, 2, 1, 0, 1, 3, 0};
        static const uint8_t x70[3] = {6, 0, 1};
        uint32_t plen;
        memcpy(&plen, h + PAD_OFS_LENGTH, 4);
        CHECK(plen == 0x20);
        CHECK(memcmp(h + 0x28, align, 6) == 0);
        CHECK(memcmp(h + 0x30, act, 16) == 0);
        CHECK(memcmp(h + 0x40, x40, 4) == 0);
        CHECK(memcmp(h + 0x50, x50, 4) == 0);
        CHECK(memcmp(h + 0x64, x64, 12) == 0);
        CHECK(memcmp(h + 0x70, x70, 3) == 0);
        /* InfoMode byte sources (retail 0x12BCA0) */
        CHECK(scePadInfoMode(0, 0, InfoModeCurExOffs, 0) == 1);
        CHECK(scePadInfoMode(0, 0, InfoModeIdTable, 0) == 4);
    }
    CHECK(scePadGetPortMax() == 2 && scePadGetSlotMax(0) == 1);
    CHECK(scePadGetModVersion() == (int)PADMAN_MOD_VERSION);
    /* the two halves alternate and the newer one has the larger frame counter */
    if (!g_native) {
        uint32_t f0, f1;
        memcpy(&f0, g_buf0 + PAD_OFS_FRAME, 4);
        memcpy(&f1, g_buf0 + PAD_HALF + PAD_OFS_FRAME, 4);
        CHECK((f0 > f1 ? f0 - f1 : f1 - f0) == 1);
        CHECK(sif_call_count(PADMAN_SID, 1) >= 6);
    } else {
        CHECK(sif_call_count(PADMAN_SID, 1) == 0); /* native: no RPC at all */
        uint8_t zero[sizeof g_buf0];
        memset(zero, 0, sizeof zero);
        CHECK(memcmp(g_buf0, zero, sizeof zero) == 0); /* and nothing written to the buffer */
    }
    CHECK(scePadPortClose(1, 0) == 1 && scePadGetState(1, 0) == scePadStateClosed);
    CHECK(scePadEnd() == 1);
}
static void t_pad_stable(void)
{
    boot(1, 2000);
    pad_reset(0);
    run_main(m_pad_stable);
}

/* ---- pad: report -> DS2 frame mapping --------------------------------------------------- */
static void m_pad_mapping(void *a)
{
    (void)a;
    pad_up();
    CHECK(scePadPortOpen(0, 0, g_buf0) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) >= 0);
    rg_pad_report r;
    rg_pad_report_neutral(&r);
    r.buttons = RG_PAD_CROSS | RG_PAD_START | RG_PAD_UP;
    r.lx = 0x10;
    r.ly = 0xF0;
    r.rx = 0x33;
    r.ry = 0x44;
    rg_pad_push_report(0, &r);
    vsync();
    unsigned char rd[32];
    decoded d;
    /* digital: 32 bytes reported (VALIDATION.md 4), no sticks */
    CHECK(scePadRead(0, 0, rd) == 32);
    CHECK(decode(rd, 4, &d) && d.mode == 4 && d.word == 0x1840 && d.lx == 0);
    CHECK(rd[2] == 0xE7 && rd[3] == 0xBF);
    if (g_control)
        CHECK(rd[2] == 0x18 && rd[3] == 0x40); /* control: active-high on the wire */
    CHECK(scePadSetMainMode(0, 0, 1, 3) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) > 0);
    int len = scePadRead(0, 0, rd);
    CHECK(len == 32);
    CHECK(decode(rd, len, &d) && d.mode == 7 && d.word == 0x1840);
    CHECK(d.rx == 0x33 && d.ry == 0x44 && d.lx == 0x10 && d.ly == 0xF0);
    /* every DS2 button bit round-trips */
    for (int b = 0; b < 16; b++) {
        r.buttons = (uint16_t)(1u << b);
        rg_pad_push_report(0, &r);
        vsync();
        len = scePadRead(0, 0, rd);
        CHECK(decode(rd, len, &d) && d.word == (1 << b));
    }
    /* pressure mode: 0x79, 32 bytes reported, pressures 0xFF for pressed buttons (derived) */
    CHECK(scePadEnterPressMode(0, 0) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) > 0);
    r.buttons = RG_PAD_CROSS | RG_PAD_R2;
    rg_pad_push_report(0, &r);
    vsync();
    len = scePadRead(0, 0, rd);
    CHECK(len == 32 && rd[1] == 0x79 && rd[31] == 0x5A);
    CHECK(rd[8 + RG_PAD_P_CROSS] == 0xFF && rd[8 + RG_PAD_P_R2] == 0xFF && rd[8 + RG_PAD_P_CIRCLE] == 0);
    r.has_pressure = 1;
    r.pressure[RG_PAD_P_CROSS] = 0x40;
    rg_pad_push_report(0, &r);
    vsync();
    len = scePadRead(0, 0, rd);
    CHECK(rd[8 + RG_PAD_P_CROSS] == 0x40);
    CHECK(scePadExitPressMode(0, 0) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) > 0);
    CHECK(scePadRead(0, 0, rd) == 32 && rd[1] == 0x73);
}
static void t_pad_mapping(void)
{
    boot(1, 2000);
    pad_reset(0);
    run_main(m_pad_mapping);
}

/* ---- pad: scripted replay is deterministic ---------------------------------------------- */
static uint64_t g_hash;
static uint16_t g_words[64];
static rg_pad_script *g_script;
static uint64_t fnv(uint64_t h, const void *p, size_t n)
{
    const uint8_t *b = (const uint8_t *)p;
    for (size_t i = 0; i < n; i++) {
        h ^= b[i];
        h *= 0x100000001B3ull;
    }
    return h;
}
static void m_pad_replay(void *a)
{
    (void)a;
    pad_up();
    CHECK(scePadPortOpen(0, 0, g_buf0) == 1);
    rg_pad_script_set_offset(g_script, (int64_t)ps2k_vblank_count());
    uint64_t h = 0xCBF29CE484222325ull;
    for (int f = 0; f < 64; f++) {
        unsigned char rd[32] = {0};
        int len = scePadRead(0, 0, rd);
        decoded d;
        g_words[f] = decode(rd, len, &d) ? (uint16_t)d.word : 0xFFFF;
        h = fnv(h, rd, sizeof rd);
        h = fnv(h, g_buf0, sizeof g_buf0);
        uint64_t t = ps2k_now();
        h = fnv(h, &t, sizeof t);
        vsync();
    }
    g_hash = h;
}
static void t_pad_replay(void)
{
    const char *text = "# replay\n10 12 CROSS\n15 20 START+UP\n30 30 circle\n";
    const char *shifted = "11 13 CROSS\n16 21 START+UP\n31 31 CIRCLE\n";
    uint64_t hashes[2];
    uint16_t words[2][64];
    for (int run = 0; run < 2; run++) {
        char err[128] = {0};
        g_script = rg_pad_script_parse(run == 1 && g_control ? shifted : text, err, sizeof err);
        CHECK(g_script != NULL);
        boot(1, 2000);
        pad_reset(0);
        rg_pad_set_input_source(rg_pad_script_source, g_script);
        run_main(m_pad_replay);
        rg_pad_set_input_source(NULL, NULL);
        hashes[run] = g_hash;
        memcpy(words[run], g_words, sizeof g_words);
        rg_pad_script_free(g_script);
        g_script = NULL;
    }
    CHECK(hashes[0] == hashes[1]);
    CHECK(memcmp(words[0], words[1], sizeof words[0]) == 0);
    /* frames 0..3: no data yet (finding), then the script lands on its own frames */
    CHECK(words[0][3] == 0xFFFF && words[0][4] == 0);
    CHECK(words[0][9] == 0 && words[0][10] == RG_PAD_CROSS && words[0][12] == RG_PAD_CROSS);
    CHECK(words[0][13] == 0 && words[0][15] == (RG_PAD_START | RG_PAD_UP) && words[0][21] == 0);
    CHECK(words[0][30] == RG_PAD_CIRCLE && words[0][31] == 0);
    /* parser errors are reported, not guessed */
    char err[128] = {0};
    CHECK(rg_pad_script_parse("1 2 JUMP\n", err, sizeof err) == NULL && strstr(err, "line 1"));
    CHECK(rg_pad_script_parse("5 2 CROSS\n", err, sizeof err) == NULL);
}

/* ---- pad: vibration + hot-plug ------------------------------------------------------------- */
static int g_rum_n, g_rum_port, g_rum_small, g_rum_large;
static void on_rumble(void *u, int port, uint8_t s, uint8_t l)
{
    (void)u;
    g_rum_n++;
    g_rum_port = port;
    g_rum_small = s;
    g_rum_large = l;
}
static int g_unplug_from = -1, g_unplug_to = -1;
static uint64_t g_vb_base;
static int src_plug(void *u, int port, uint64_t vb, rg_pad_report *out)
{
    (void)u;
    rg_pad_report_neutral(out);
    int f = (int)(vb - g_vb_base);
    out->connected = port == 0 && !(f >= g_unplug_from && f < g_unplug_to);
    return 1;
}
static void m_pad_rumble(void *a)
{
    (void)a;
    pad_up();
    CHECK(scePadPortOpen(0, 0, g_buf0) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) >= 0);
    unsigned char dir[6] = {1, 200, 0, 0, 0, 0};
    CHECK(scePadSetActDirect(0, 0, dir) == 1);
    CHECK(g_rum_n == 0); /* motors not mapped until SetActAlign */
    CHECK(scePadSetMainMode(0, 0, 1, 3) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) > 0);
    unsigned char align[6] = {0, 1, 0xFF, 0xFF, 0xFF, 0xFF};
    CHECK(scePadSetActAlign(0, 0, align) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) > 0);
    CHECK(g_rum_n == 1 && g_rum_small == 1 && g_rum_large == 200); /* the latched direct bytes */
    unsigned char off[6] = {0};
    CHECK(scePadSetActDirect(0, 0, off) == 1);
    CHECK(g_rum_n == 2 && g_rum_small == 0 && g_rum_large == 0);
    CHECK(scePadSetActDirect(0, 0, dir) == 1 && g_rum_n == 3);
    CHECK(scePadSetActDirect(0, 0, dir) == 1 && g_rum_n == 3); /* unchanged: no call */
    /* unplug: DISCONN, motors off, comes back digital after FIND/CTP1 */
    g_vb_base = ps2k_vblank_count();
    g_unplug_from = 2;
    g_unplug_to = 6;
    rg_pad_set_input_source(src_plug, NULL);
    CHECK(wait_state(0, scePadStateDiscon, 10) >= 0);
    CHECK(g_rum_n == 4 && g_rum_small == 0 && g_rum_large == 0);
    CHECK(scePadSetActDirect(0, 0, dir) == 0);
    CHECK(wait_state(0, scePadStateFindPad, 10) >= 0);
    CHECK(wait_state(0, scePadStateStable, 10) >= 0);
    CHECK(scePadInfoMode(0, 0, InfoModeCurID, 0) == 4);
    rg_pad_set_input_source(NULL, NULL);
}
static void t_pad_rumble(void)
{
    boot(1, 2000);
    pad_reset(0);
    g_rum_n = 0;
    rg_pad_set_rumble_hook(on_rumble, NULL);
    run_main(m_pad_rumble);
    rg_pad_set_rumble_hook(NULL, NULL);
}

/* ---- pad: analog lock kept (keep_analog_lock, the runtime's default) ------------------------ */
/* PadIsAnalogMode_184960: state STABLE (6) or FINDCTP1 (2), and InfoMode(port, 0, 1, 0) == 7.
 * When it is false GameFrameUpdate_27c4c0 raises the "analog required" pause (reason 4/5). */
static int analog_ok(int port)
{
    int st = scePadGetState(port, 0);
    return (st == 6 || st == 2) && scePadInfoMode(port, 0, InfoModeCurID, 0) == 7;
}
static int src_busy(void *u, int port, uint64_t vb, rg_pad_report *out)
{
    (void)u;
    rg_pad_report_neutral(out);
    int f = (int)(vb - g_vb_base);
    out->connected = port == 0 && !(f >= g_unplug_from && f < g_unplug_to);
    /* every button pattern and stick extreme the host can send (no "analog" button exists) */
    uint32_t h = (uint32_t)vb * 2654435761u;
    out->buttons = (uint16_t)(h >> 16);
    out->lx = (uint8_t)(h >> 3);
    out->ly = (uint8_t)(f & 1 ? 0x00 : 0xFF);
    out->rx = (uint8_t)(h >> 11);
    out->ry = 0x80;
    return 1;
}
static void m_pad_analog_lock(void *a)
{
    (void)a;
    pad_up();
    g_vb_base = ps2k_vblank_count();
    g_unplug_from = g_unplug_to = -1;
    rg_pad_set_input_source(src_busy, NULL);
    CHECK(scePadPortOpen(0, 0, g_buf0) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) >= 0);
    /* the boot path is the hardware one: powers up digital, and a pad the game never locked
     * still comes back digital after an unplug */
    CHECK(scePadInfoMode(0, 0, InfoModeCurID, 0) == 4);
    g_vb_base = ps2k_vblank_count();
    g_unplug_from = 1;
    g_unplug_to = 4;
    CHECK(wait_state(0, scePadStateDiscon, 10) >= 0);
    CHECK(wait_state(0, scePadStateStable, 20) >= 0);
    CHECK(scePadInfoMode(0, 0, InfoModeCurID, 0) == 4);
    /* the game's SetMainMode(analog, lock) */
    CHECK(scePadSetMainMode(0, 0, 1, 3) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) > 0);
    unsigned char rd[32];
    pinfo pi;
    /* 600 VBlanks of arbitrary input: always 0x73, locked, PadIsAnalogMode true */
    int bad = 0;
    for (int i = 0; i < 600; i++) {
        vsync();
        pad_info(0, &pi);
        if (!(scePadRead(0, 0, rd) == 32 && rd[1] == 0x73 && pi.locked && pi.mode_id == 0x73 && analog_ok(0)))
            bad++;
    }
    CHECK(bad == 0);
    /* a digital request is ignored once locked */
    CHECK(scePadSetMainMode(0, 0, 0, 2) == 1);
    CHECK(wait_state(0, scePadStateStable, 20) > 0);
    CHECK(analog_ok(0));
    /* unplug + replug (a host device change): back to STABLE in 0x73, still locked,
     * without the game re-issuing SetMainMode */
    g_vb_base = ps2k_vblank_count();
    g_unplug_from = 1;
    g_unplug_to = 5;
    CHECK(wait_state(0, scePadStateDiscon, 10) >= 0);
    CHECK(wait_state(0, scePadStateStable, 20) >= 0);
    pad_info(0, &pi);
    int want_id = g_control ? 0x41 : 0x73; /* control: expects the hardware power cycle */
    if (pi.mode_id != 0x73)
        fprintf(stderr, "  after replug: mode 0x%02X locked %d\n", pi.mode_id, pi.locked);
    CHECK(pi.mode_id == want_id && pi.locked == !g_control);
    CHECK(scePadRead(0, 0, rd) == 32 && rd[1] == want_id);
    CHECK(analog_ok(0) == !g_control);
    rg_pad_set_input_source(NULL, NULL);
}
static void t_pad_analog_lock(void)
{
    boot(1, 2000);
    padman_config c;
    padman_default_config(&c);
    CHECK(c.keep_analog_lock == 0); /* hardware behaviour unless asked (pad_rumble) */
    rg_npad_config nc;
    rg_npad_default_config(&nc);
    CHECK(nc.keep_analog_lock == 0);
    pad_reset(1);
    run_main(m_pad_analog_lock);
}


/* ---- pad: native service == padman HLE, answer by answer (docs/NATIVE-IOP.md) ---------------
 * The same scripted session (input with unplugs, port 2 plugged for a while, every libpad
 * command incl. ones refused while busy, reads, closes and reopens) runs once on padman
 * over SIF and once on the native service, each from a fresh kernel; every API return,
 * every read's 32 bytes, every rumble call and the virtual time per frame are logged and
 * must be identical.  keep_analog_lock off and on.  Control: the native run gets
 * cmd_frames 2 instead of 3 and must differ. */
#define EQ_FRAMES 420
#define EQ_MAX (EQ_FRAMES * 160)
static int32_t g_eq_log[2][EQ_MAX];
static int g_eq_n[2];
static int g_eq_run;
static uint64_t g_eq_base;
static void eq_put(int32_t v)
{
    if (g_eq_n[g_eq_run] < EQ_MAX)
        g_eq_log[g_eq_run][g_eq_n[g_eq_run]++] = v;
}
static void eq_rumble(void *u, int port, uint8_t s, uint8_t l)
{
    (void)u;
    eq_put(0x7E000000 | (port << 16) | (s << 8) | l);
}
static int eq_src(void *u, int port, uint64_t vb, rg_pad_report *out)
{
    (void)u;
    rg_pad_report_neutral(out);
    int f = (int)(vb - g_eq_base);
    uint32_t h = (uint32_t)(vb * 2654435761u) ^ (uint32_t)port * 0x9E3779B9u;
    if (port == 0)
        out->connected = !((f >= 150 && f < 156) || (f >= 300 && f < 303));
    else
        out->connected = f >= 40 && f < 260;
    out->buttons = (uint16_t)(h >> 13);
    out->lx = (uint8_t)h;
    out->ly = (uint8_t)(h >> 8);
    out->rx = (uint8_t)(h >> 16);
    out->ry = (uint8_t)(h >> 24);
    out->has_pressure = (f & 4) != 0;
    for (int i = 0; i < RG_PAD_P_COUNT; i++)
        out->pressure[i] = (uint8_t)(h >> i);
    return 1;
}
static void eq_frame(void)
{
    for (int port = 0; port < 2; port++) {
        eq_put(scePadGetState(port, 0));
        eq_put(scePadGetReqState(port, 0));
        for (int term = 1; term <= 4; term++)
            for (int offs = -1; offs <= 2; offs++)
                eq_put(scePadInfoMode(port, 0, term, offs));
        for (int act = -1; act <= 2; act++)
            for (int term = 0; term <= 4; term++)
                eq_put(scePadInfoAct(port, 0, act, term));
        eq_put(scePadInfoPressMode(port, 0));
        unsigned char rd[32];
        memset(rd, 0xEE, sizeof rd);
        int n = scePadRead(port, 0, rd);
        eq_put(n);
        for (int i = 0; i < 32; i += 4)
            eq_put((int32_t)(rd[i] | rd[i + 1] << 8 | rd[i + 2] << 16 | (uint32_t)rd[i + 3] << 24));
    }
    eq_put((int32_t)(ps2k_now() & 0x7FFFFFFF));
}
static void m_npad_equiv(void *a)
{
    (void)a;
    memset(g_buf0, 0, sizeof g_buf0);
    memset(g_buf1, 0, sizeof g_buf1);
    vsync_setup();
    vsync();
    eq_put(scePadGetPortMax()); /* before init: no server / not inited */
    eq_put(scePadInit(0));
    eq_put(scePadGetModVersion());
    eq_put(scePadGetPortMax());
    eq_put(scePadGetSlotMax(0));
    eq_put(scePadGetSlotMax(1));
    eq_put(scePadGetSlotMax(2));
    eq_put(scePadPortOpen(0, 1, g_buf0)); /* slot 1: no controller */
    g_eq_base = ps2k_vblank_count();
    eq_put(scePadPortOpen(0, 0, g_buf0));
    eq_put(scePadPortOpen(1, 0, g_buf1));
    static const unsigned char al[6] = {0, 1, 0xFF, 0xFF, 0xFF, 0xFF};
    static const unsigned char al2[6] = {1, 0, 0xFF, 0xFF, 0xFF, 0xFF};
    for (int f = 0; f < EQ_FRAMES; f++) {
        unsigned char dir[6] = {(unsigned char)(f & 1), (unsigned char)(f * 7), 0, 0, 0, 0};
        switch (f) {
        case 5: case 12: eq_put(scePadSetMainMode(0, 0, 1, 3)); eq_put(scePadSetMainMode(0, 0, 1, 3)); break;
        case 18: eq_put(scePadSetActAlign(0, 0, al)); eq_put(scePadSetMainMode(0, 0, 0, 2)); break;
        case 30: eq_put(scePadEnterPressMode(0, 0)); break;
        case 50: eq_put(scePadSetActAlign(1, 0, al2)); eq_put(scePadSetMainMode(1, 0, 1, 2)); break;
        case 60: eq_put(scePadSetButtonInfo(1, 0, 0xFFF)); eq_put(scePadEnterPressMode(1, 0)); break;
        case 70: eq_put(scePadExitPressMode(0, 0)); eq_put(scePadSetMainMode(0, 0, 2, 3)); break;
        case 90: eq_put(scePadSetReqState(0, 0, 1)); eq_put(scePadSetReqState(1, 0, 2)); break;
        case 100: eq_put(scePadSetMainMode(0, 0, 0, 2)); break;
        case 120: eq_put(scePadSetMainMode(0, 0, 1, 3)); eq_put(scePadSetActAlign(0, 0, al)); break;
        case 200: eq_put(scePadPortClose(1, 0)); eq_put(scePadPortClose(1, 0)); break;
        case 210: eq_put(scePadPortOpen(1, 0, g_buf1)); break;
        case 280: eq_put(scePadSetMainMode(0, 0, 0, 2)); break;
        case 340: eq_put(scePadPortClose(0, 0)); break;
        case 345: eq_put(scePadPortOpen(0, 0, g_buf0)); break;
        case 400: eq_put(scePadEnd()); eq_put(scePadEnd()); break;
        case 405: eq_put(scePadPortOpen(0, 0, g_buf0)); break;
        default: break;
        }
        if (f % 3 == 0) {
            eq_put(scePadSetActDirect(0, 0, dir));
            eq_put(scePadSetActDirect(1, 0, dir));
        }
        eq_frame();
        vsync();
    }
}
static void t_npad_equiv(void)
{
    for (int lock = 0; lock < 2; lock++) {
        for (int run = 0; run < 2; run++) {
            g_eq_run = run;
            g_eq_n[run] = 0;
            boot(1, 0); /* the runtime's SIF latency (0): the native path has no transport time */
            g_native = run == 1;
            rg_iop_set_mode(g_native ? RG_IOP_MODE_NATIVE : RG_IOP_MODE_HLE);
            if (g_native) {
                rg_npad_config c;
                rg_npad_default_config(&c);
                c.keep_analog_lock = lock;
                if (g_control)
                    c.cmd_frames = 2;
                rg_npad_reset(&c);
            } else {
                padman_config c;
                padman_default_config(&c);
                c.keep_analog_lock = lock;
                padman_reset(&c);
            }
            rg_pad_set_input_source(eq_src, NULL);
            rg_pad_set_rumble_hook(eq_rumble, NULL);
            run_main(m_npad_equiv);
            rg_pad_set_input_source(NULL, NULL);
            rg_pad_set_rumble_hook(NULL, NULL);
        }
        int n = g_eq_n[0] < g_eq_n[1] ? g_eq_n[0] : g_eq_n[1];
        int first = -1;
        for (int i = 0; i < n && first < 0; i++)
            if (g_eq_log[0][i] != g_eq_log[1][i])
                first = i;
        if (first >= 0) {
            fprintf(stderr, "  lock %d: first difference at entry %d: hle %d native %d\n", lock, first,
                    g_eq_log[0][first], g_eq_log[1][first]);
            for (int i = first - 60 < 0 ? 0 : first - 60; i < first + 8 && i < n; i++)
                fprintf(stderr, "    [%d] %d %d%s\n", i, g_eq_log[0][i], g_eq_log[1][i],
                        g_eq_log[0][i] != g_eq_log[1][i] ? "  <--" : "");
        }
        else
            printf("  lock %d: %d answers identical\n", lock, n);
        CHECK(g_eq_n[0] == g_eq_n[1] && g_eq_n[0] > EQ_FRAMES * 90);
        CHECK(first < 0);
    }
    g_native = 0;
    rg_iop_set_mode(RG_IOP_MODE_HLE);
}

/* ---- pad: the game's own pad code (game/src/main/pad) on this libpad ------------------------ */
#ifdef RG_PADMC_GAME_PAD
uint8_t D_004B2570[0x270] __attribute__((aligned(16)));
uint8_t D_004B27E0[0x2A0] __attribute__((aligned(16)));
uint8_t D_004B2A80[0x100] __attribute__((aligned(64)));
uint8_t D_004B2B80[0x100] __attribute__((aligned(64)));
int D_0047E03C;
extern void PadOpenPorts_1c6bf0(void);
extern int PadUpdateConnection_184a50(void *, int, int, int);
extern unsigned char PadIsAnalogMode_184960(void *);
extern void PadUpdateVibration_184250(void *, int);
static void m_pad_game(void *a)
{
    (void)a;
    vsync_setup();
    vsync();
    PadOpenPorts_1c6bf0(); /* scePadInit, two PortOpens, PadWaitReady loop */
    int32_t phase, word;
    memcpy(&phase, D_004B2570 + 4 + 0x14, 4);
    CHECK(phase == 0x63);
    CHECK(PadIsAnalogMode_184960(D_004B2570) == 1);
    pinfo pi;
    pad_info(0, &pi);
    CHECK(pi.mode_id == 0x73 && pi.locked && pi.align[0] == 0 && pi.align[1] == 1);
    CHECK(scePadGetState(1, 0) == scePadStateDiscon);
    rg_pad_report r;
    rg_pad_report_neutral(&r);
    r.buttons = RG_PAD_START;
    r.lx = 0x00;
    rg_pad_push_report(0, &r);
    vsync();
    CHECK(PadUpdateConnection_184a50(D_004B2570 + 4, 0, 0, 0) == 1);
    memcpy(&word, D_004B2570 + 4, 4);
    CHECK(word == 0x0800);
    int32_t lx;
    memcpy(&lx, D_004B2570 + 0xC, 4); /* PadGetAnalogLX_1840d0 reads obj+0xC */
    CHECK(lx == 0);
    /* vibration through the game's own path */
    D_004B2570[0x2C] = 1;
    D_004B2570[0x2D] = 180;
    int32_t dur = 100;
    memcpy(D_004B2570 + 0x44, &dur, 4);
    memcpy(D_004B2570 + 0x48, &dur, 4);
    PadUpdateVibration_184250(D_004B2570, 1);
    CHECK(g_rum_n >= 1 && g_rum_port == 0 && g_rum_small == 1 && g_rum_large == 180);
}
static void t_pad_game(void)
{
    boot(1, 2000);
    pad_reset(0);
    g_rum_n = 0;
    rg_pad_set_rumble_hook(on_rumble, NULL);
    run_main(m_pad_game);
    rg_pad_set_rumble_hook(NULL, NULL);
}
#endif

/* ---- memory card ------------------------------------------------------------------------ */
static int mc_wait(int *cmd)
{
    int c = -99, res = -999;
    int r = sceMcSync(0, &c, &res);
    CHECK(r == sceMcExecFinish);
    if (cmd)
        *cmd = c;
    return res;
}

static void mc_boot(const char *name, uint32_t free_clusters, int p0, int p1, int wipe)
{
    char dir[1024];
    tmpdir(name, dir, sizeof dir, wipe);
    mccard_config c;
    mccard_default_config(&c);
    static char root[1024];
    snprintf(root, sizeof root, "%s", dir);
    c.root = root;
    c.slot_policy[0] = p0;
    c.slot_policy[1] = p1;
    if (free_clusters)
        c.free_clusters = free_clusters;
    c.clock = rg_mc_virtual_clock;
    CHECK(mccard_init(&c) == 0);
    rg_mc_reset();
}

static const char *SAVE_DIR = "/BASCUS-97490LV5RG_00";

static void m_mc_files(void *a)
{
    (void)a;
    int type = -1, freec = -1, fmt = -1, cmd = 0;
    int ir = sceMcInit();
    if (ir)
        fprintf(stderr, "  sceMcInit -> %d\n", ir);
    CHECK(ir == 0);
    CHECK(sceMcGetInfo(0, 0, &type, &freec, &fmt) == 0);
    CHECK(mc_wait(&cmd) == -1 && cmd == sceMcFuncNoCardInfo); /* first look: a "new" card */
    CHECK(type == 2 && fmt == 1 && freec == 8000);
    CHECK(sceMcGetInfo(0, 0, &type, &freec, &fmt) == 0 && mc_wait(NULL) == 0);
    CHECK(sceMcMkdir(0, 0, SAVE_DIR) == 0);
    CHECK(mc_wait(&cmd) == 0 && cmd == sceMcFuncNoMkdir);
    CHECK(sceMcMkdir(0, 0, SAVE_DIR) == 0 && mc_wait(NULL) == -4); /* exists */
    /* the save file, then icon.sys (964 bytes), as the game writes them */
    static uint8_t data[5000], back[5000];
    for (int i = 0; i < 5000; i++)
        data[i] = (uint8_t)(i * 7 + 3);
    char path[128];
    snprintf(path, sizeof path, "%s/BASCUS-97490LV5RG_00", SAVE_DIR);
    CHECK(sceMcOpen(0, 0, path, MC_O_CREAT | MC_O_WRONLY) == 0);
    int fd = mc_wait(&cmd);
    CHECK(fd >= 0 && cmd == sceMcFuncNoOpen);
    CHECK(sceMcWrite(fd, data, 5000) == 0 && mc_wait(&cmd) == 5000 && cmd == sceMcFuncNoWrite);
    CHECK(sceMcClose(fd) == 0 && mc_wait(NULL) == 0);
    static uint8_t icon[964];
    memset(icon, 'I', sizeof icon);
    snprintf(path, sizeof path, "%s/icon.sys", SAVE_DIR);
    CHECK(sceMcOpen(0, 0, path, MC_O_CREAT | MC_O_WRONLY) == 0);
    fd = mc_wait(NULL);
    CHECK(sceMcWrite(fd, icon, sizeof icon) == 0 && mc_wait(NULL) == 964);
    CHECK(sceMcFlush(fd) == 0 && mc_wait(&cmd) == 0 && cmd == sceMcFuncNoFlush);
    CHECK(sceMcClose(fd) == 0 && mc_wait(NULL) == 0);
    /* read back (in 0x800 chunks like McLoadStep_373890) */
    snprintf(path, sizeof path, "%s/BASCUS-97490LV5RG_00", SAVE_DIR);
    CHECK(sceMcOpen(0, 1, path, MC_O_RDONLY) == 0);
    fd = mc_wait(NULL);
    int got = 0;
    for (;;) {
        CHECK(sceMcRead(fd, back + got, 0x800) == 0);
        int n = mc_wait(&cmd);
        CHECK(cmd == sceMcFuncNoRead && n >= 0);
        if (n <= 0)
            break;
        got += n;
        if (got >= 5000)
            break;
    }
    CHECK(got == 5000 && memcmp(data, back, 5000) == 0);
    CHECK(sceMcSeek(fd, 100, 0) == 0 && mc_wait(NULL) == 100);
    CHECK(sceMcRead(fd, back, 10) == 0 && mc_wait(NULL) == 10 && memcmp(back, data + 100, 10) == 0);
    CHECK(sceMcSeek(fd, 0, 2) == 0 && mc_wait(NULL) == 5000);
    CHECK(sceMcWrite(fd, data, 10) == 0 && mc_wait(NULL) == -5); /* opened read-only */
    CHECK(sceMcClose(fd) == 0 && mc_wait(NULL) == 0);
    /* listings: creation order, "." and "..", sizes, attributes */
    static sceMcTblGetDir t[16];
    memset(t, 0, sizeof t);
    snprintf(path, sizeof path, "%s/*", SAVE_DIR);
    CHECK(sceMcGetDir(0, 0, path, 0, 16, t) == 0);
    CHECK(mc_wait(&cmd) == 4 && cmd == sceMcFuncNoGetDir);
    CHECK(!strcmp((char *)t[0].EntryName, ".") && !strcmp((char *)t[1].EntryName, ".."));
    CHECK(!strcmp((char *)t[2].EntryName, "BASCUS-97490LV5RG_00") && t[2].FileSizeByte == 5000);
    CHECK(!strcmp((char *)t[3].EntryName, "icon.sys") && t[3].FileSizeByte == 0x3C4);
    CHECK(t[2].AttrFile == MC_ATTR_DEFAULT_FILE && t[0].AttrFile == MC_ATTR_DEFAULT_DIR);
    CHECK(t[2]._Create.Year == 2006 && t[2]._Create.Month == 1 && t[2]._Create.Day == 31);
    CHECK(sceMcGetDir(0, 0, path, 0, 2, t) == 0 && mc_wait(NULL) == 2); /* paged */
    CHECK(sceMcGetDir(0, 0, path, 1, 2, t) == 0 && mc_wait(NULL) == 2 && !strcmp((char *)t[1].EntryName, "icon.sys"));
    CHECK(sceMcGetDir(0, 0, path, 1, 2, t) == 0 && mc_wait(NULL) == 0);
    CHECK(sceMcGetDir(0, 0, "/BASCUS-97490LV5RG_??", 0, 16, t) == 0 && mc_wait(NULL) == 1);
    CHECK(t[0].FileSizeByte == 4 && (t[0].AttrFile & MC_ATTR_SUBDIR)); /* dir: entry count */
    CHECK(sceMcGetDir(0, 0, "/BISCPS-*", 0, 16, t) == 0 && mc_wait(NULL) == 0);
    /* free space: dir 2 clusters (4 entries), file 5, icon 1, root grows by 1 */
    CHECK(sceMcGetInfo(0, 0, &type, &freec, &fmt) == 0 && mc_wait(NULL) == 0);
    int want_free = 8000 - 2 - 5 - 1 - 1;
    if (g_control)
        want_free = 8000;
    CHECK(freec == want_free);
    /* chdir + relative names, rename, set attributes, delete */
    char pwd[1024] = "x";
    CHECK(sceMcChdir(0, 0, SAVE_DIR, pwd) == 0 && mc_wait(&cmd) == 0 && cmd == sceMcFuncNoChDir);
    CHECK(!strcmp(pwd, "/"));
    CHECK(sceMcRename(0, 0, "icon.sys", "icon.bak") == 0 && mc_wait(&cmd) == 0 && cmd == sceMcFuncNoRename);
    CHECK(sceMcRename(0, 0, "nothere", "x") == 0 && mc_wait(NULL) == -4);
    sceMcTblGetDir info;
    memset(&info, 0, sizeof info);
    info.AttrFile = MC_ATTR_READABLE; /* read-only */
    CHECK(sceMcSetFileInfo(0, 0, "icon.bak", &info, MC_INFO_ATTR) == 0 && mc_wait(&cmd) == 0);
    CHECK(cmd == sceMcFuncNoFileInfo);
    CHECK(sceMcOpen(0, 0, "icon.bak", MC_O_WRONLY) == 0 && mc_wait(NULL) == -5);
    CHECK(sceMcGetDir(0, 0, "icon.*", 0, 4, t) == 0 && mc_wait(NULL) == 1);
    CHECK(!strcmp((char *)t[0].EntryName, "icon.bak") && (t[0].AttrFile & 0x7) == MC_ATTR_READABLE);
    CHECK(sceMcDelete(0, 0, SAVE_DIR) == 0 && mc_wait(&cmd) == -6 && cmd == sceMcFuncNoDelete); /* not empty */
    CHECK(sceMcDelete(0, 0, "icon.bak") == 0 && mc_wait(NULL) == 0);
    CHECK(sceMcGetEntSpace(0, 0, SAVE_DIR) == 0 && mc_wait(NULL) == 1); /* 3 entries: 1 free slot */
    /* the host side: plain files under <root>/slot0/ */
    char hp[1024];
    mccard_host_path(0, "/BASCUS-97490LV5RG_00/BASCUS-97490LV5RG_00", hp, sizeof hp);
    struct stat st;
    CHECK(stat(hp, &st) == 0 && st.st_size == 5000);
    CHECK(sceMcEnd() == 1);
    CHECK(sceMcSync(1, NULL, NULL) == sceMcExecIdle);
}
static void t_mc_files(void)
{
    boot(1, 5000);
    mc_boot("files", 0, MC_SLOT_AUTO, MC_SLOT_IF_EXISTS, 1);
    run_main(m_mc_files);
    mccard_shutdown();
}

static void m_mc_errors(void *a)
{
    (void)a;
    int type = -1, freec = -1, fmt = -1, res = 0;
    CHECK(sceMcGetInfo(0, 0, &type, &freec, &fmt) == sceMcErrNoInit); /* before sceMcInit */
    CHECK(sceMcSync(1, NULL, NULL) == sceMcExecIdle);
    CHECK(sceMcInit() == 0);
    /* no card in slot 2 */
    CHECK(sceMcGetInfo(1, 0, &type, &freec, &fmt) == 0);
    res = mc_wait(NULL);
    CHECK(res == MC_RES_NOCARD && res < -10 && type == 0 && freec == 0 && fmt == 0);
    CHECK(sceMcOpen(1, 0, "/x", MC_O_RDONLY) == 0 && mc_wait(NULL) == MC_RES_NOCARD);
    /* unformatted card in slot 1: -2 until formatted, then a clean 0 */
    CHECK(sceMcGetInfo(0, 0, &type, &freec, &fmt) == 0 && mc_wait(NULL) == -2);
    CHECK(type == 2 && fmt == 0 && freec == 0);
    CHECK(sceMcMkdir(0, 0, "/A") == 0 && mc_wait(NULL) == -2);
    uint64_t t0 = ps2k_now();
    CHECK(sceMcFormat(0, 0) == 0 && mc_wait(NULL) == 0);
    CHECK(ps2k_now() - t0 >= mcserv_get_config()->format_cycles);
    CHECK(sceMcGetInfo(0, 0, &type, &freec, &fmt) == 0 && mc_wait(NULL) == 0);
    CHECK(fmt == 1 && freec == 20);
    /* missing file / missing parent / bad name */
    CHECK(sceMcOpen(0, 0, "/nope", MC_O_RDONLY) == 0 && mc_wait(NULL) == -4);
    CHECK(sceMcOpen(0, 0, "/nodir/f", MC_O_CREAT | MC_O_WRONLY) == 0 && mc_wait(NULL) == -4);
    CHECK(sceMcOpen(0, 0, "", MC_O_RDONLY) == sceMcErrBadName);
    CHECK(sceMcOpen(0, 0, NULL, MC_O_RDONLY) == sceMcErrBadName);
    CHECK(sceMcChdir(0, 0, "/nope", NULL) == 0 && mc_wait(NULL) == -4);
    CHECK(sceMcClose(57) == 0 && mc_wait(NULL) < 0);
    /* busy: a second issue before sceMcSync collects the first */
    CHECK(sceMcGetInfo(0, 0, NULL, NULL, NULL) == 0);
    CHECK(sceMcGetInfo(0, 0, NULL, NULL, NULL) == sceMcErrBusy);
    CHECK(mc_wait(NULL) == 0);
    /* full card: 20 clusters; root dir + file */
    CHECK(sceMcOpen(0, 0, "/big", MC_O_CREAT | MC_O_RDWR) == 0);
    int fd = mc_wait(NULL);
    CHECK(fd >= 0);
    static uint8_t blk[30 * 1024];
    CHECK(sceMcWrite(fd, blk, 10 * 1024) == 0 && mc_wait(NULL) == 10 * 1024);
    CHECK(sceMcWrite(fd, blk, 30 * 1024) == 0 && mc_wait(NULL) == -3);
    CHECK(sceMcGetInfo(0, 0, &type, &freec, &fmt) == 0 && mc_wait(NULL) == 0 && freec == 9); /* 20 - root growth 1 - file 10 */
    CHECK(sceMcClose(fd) == 0 && mc_wait(NULL) == 0);
    /* handle limit */
    int fds[20], nopen = 0;
    for (int i = 0; i < 20; i++) {
        CHECK(sceMcOpen(0, 0, "/big", MC_O_RDONLY) == 0);
        fds[i] = mc_wait(NULL);
        if (fds[i] >= 0)
            nopen++;
    }
    CHECK(nopen == mccard_get_config()->max_fds && fds[19] == -7);
    for (int i = 0; i < 20; i++)
        if (fds[i] >= 0)
            CHECK(sceMcClose(fds[i]) == 0 && mc_wait(NULL) == 0);
    CHECK(mccard_open_count() == 0);
    /* hot-plug: eject -> no card, reinsert -> "changed" (-1) once */
    mccard_eject(0);
    CHECK(sceMcGetInfo(0, 0, &type, NULL, NULL) == 0 && mc_wait(NULL) == MC_RES_NOCARD && type == 0);
    CHECK(mccard_insert(0, MC_SLOT_IF_EXISTS) == 0);
    CHECK(sceMcGetInfo(0, 0, &type, NULL, NULL) == 0 && mc_wait(NULL) == -1 && type == 2);
    CHECK(sceMcEnd() == 1);
    CHECK(sceMcOpen(0, 0, "/big", MC_O_RDONLY) == sceMcErrBusy); /* retail: lock sema gone */
    int ls, ds, pc;
    rg_mc_debug_state(&ls, &ds, &pc);
    CHECK(ls == -1 && pc == 0);
}
static void t_mc_errors(void)
{
    boot(1, 5000);
    mc_boot("errors", 20, MC_SLOT_UNFORMATTED, MC_SLOT_IF_EXISTS, 1);
    mcserv_config sc;
    mcserv_default_config(&sc);
    sc.format_cycles = 147456000ull / 10;
    mcserv_configure(&sc);
    run_main(m_mc_errors);
    mcserv_configure(NULL);
    mccard_shutdown();
}

/* async completion on the virtual clock */
static void m_mc_async(void *a)
{
    (void)a;
    const uint64_t L = g_native ? 0 : 10000; /* the SIF RPC latency: none natively */
    const mcserv_config *sc = mcserv_get_config();
    CHECK(sceMcInit() == 0);
    CHECK(sceMcOpen(0, 0, "/f", MC_O_CREAT | MC_O_WRONLY) == 0);
    int fd = mc_wait(NULL);
    static uint8_t blk[8192];
    /* blocking: completes exactly at issue + RPC latency + card time */
    uint64_t t0 = ps2k_now();
    CHECK(sceMcWrite(fd, blk, 8192) == 0);
    uint64_t expect = L + sc->op_cycles + 8 * sc->write_cycles_per_kb;
    int c = 0, res = 0;
    int first = sceMcSync(1, &c, &res);
    CHECK(c == sceMcFuncNoWrite);
    if (g_control)
        CHECK(first == sceMcExecFinish); /* control: result visible at once */
    else
        CHECK(first == sceMcExecRun);
    CHECK(sceMcSync(0, &c, &res) == sceMcExecFinish && res == 8192);
    CHECK(ps2k_now() - t0 == expect);
    /* polling: sceMcSync(1) lets virtual time pass; GetInfo outputs appear only at the end */
    int type = -7;
    t0 = ps2k_now();
    CHECK(sceMcGetInfo(0, 0, &type, NULL, NULL) == 0);
    int polls = 0;
    CHECK(type == -7);
    while (sceMcSync(1, &c, &res) == sceMcExecRun) {
        /* the output lands at the completion time, not at issue */
        CHECK(type == -7 || ps2k_now() - t0 >= L + sc->op_cycles);
        polls++;
        if (polls > 100000)
            break;
    }
    CHECK(type == 2 && polls > 0);
    uint64_t e2 = L + sc->op_cycles, pc = 2000; /* rg_mc default poll_cycles */
    CHECK(ps2k_now() - t0 >= e2 && ps2k_now() - t0 < e2 + 2 * pc);
    CHECK(polls == (int)((e2 + pc - 1) / pc));
    /* another thread runs while a blocking Sync waits (the kernel switches) */
    CHECK(sceMcClose(fd) == 0 && mc_wait(NULL) == 0);
    CHECK(sceMcEnd() == 1);
}
static void t_mc_async(void)
{
    boot(0, 10000);
    mc_boot("async", 0, MC_SLOT_AUTO, MC_SLOT_EMPTY, 1);
    rg_mc_configure(NULL);
    run_main(m_mc_async);
    mccard_shutdown();
}

/* persistence: creation order, attributes, times and data survive a reload */
static void persist_write(const char *name, int wipe)
{
    mc_boot(name, 0, MC_SLOT_AUTO, MC_SLOT_EMPTY, wipe);
    CHECK(mccard_open(0, "/B", MC_O_MKDIR) == 0);
    CHECK(mccard_open(0, "/A", MC_O_MKDIR) == 0);
    int fd = mccard_open(0, "/A/data.bin", MC_O_CREAT | MC_O_WRONLY);
    CHECK(fd >= 0);
    CHECK(mccard_write(fd, "persist me", 10) == 10);
    CHECK(mccard_close(fd) == 0);
    fd = mccard_open(0, "/A/we<rd:name.", MC_O_CREAT | MC_O_WRONLY); /* host-hostile name */
    CHECK(fd >= 0 && mccard_close(fd) == 0);
    mc_dirent info;
    memset(&info, 0, sizeof info);
    info.attr = MC_ATTR_READABLE | MC_ATTR_HIDDEN;
    info.created.year = 2001;
    info.created.month = 2;
    info.created.day = 3;
    CHECK(mccard_setinfo(0, "/A/data.bin", &info, MC_INFO_ATTR | MC_INFO_CTIME) == 0);
    mccard_shutdown();
}
static void persist_read(const char *name)
{
    mc_boot(name, 0, MC_SLOT_IF_EXISTS, MC_SLOT_EMPTY, 0);
    CHECK(mccard_present(0) && mccard_formatted(0));
    mc_dirent t[8];
    int n = mccard_getdir(0, "/*", 0, 8, t);
    CHECK(n == 4 && !strcmp(t[2].name, "B") && !strcmp(t[3].name, "A")); /* creation order */
    n = mccard_getdir(0, "/A/*", 0, 8, t);
    CHECK(n == 4 && !strcmp(t[2].name, "data.bin") && !strcmp(t[3].name, "we<rd:name."));
    CHECK(t[2].attr == ((MC_ATTR_DEFAULT_FILE & ~MC_ATTR_USER_MASK) | MC_ATTR_READABLE | MC_ATTR_HIDDEN));
    CHECK(t[2].created.year == 2001 && t[2].created.day == 3 && t[2].size == 10);
    int fd = mccard_open(0, "/A/data.bin", MC_O_RDONLY);
    char b[16] = {0};
    CHECK(fd >= 0 && mccard_read(fd, b, 16) == 10 && !memcmp(b, "persist me", 10));
    CHECK(mccard_close(fd) == 0);
    int type, fr, fm;
    mccard_getinfo(0, &type, &fr, &fm);
    CHECK(fr == 8000 - 1 /* root: 4 entries */ - 2 /* A: 4 entries */ - 1 /* B */ - 1 /* data */);
    mccard_shutdown();
}
static void t_mc_persist(void)
{
    persist_write("persist", 1);
    persist_read(g_control ? "persist_elsewhere" : "persist");
}
static void t_mc_persist_write(void) { persist_write("persist2", 1); }
static void t_mc_persist_read(void) { persist_read("persist2"); }

/* ==== the game's save path (docs/SAVES.md) ==================================================
 * Pure model tests: the call sequences, names, sizes and open modes are the ones the game's
 * save state machines issue (game/src/main/file/Mc*.c, read off the decomp), and the verdicts
 * mirror the game's decisions: McGetInfoStep_375640 (card classification),
 * McCardCheckFreeSpace_376220 + SaveCalcSizeKB_3735e0 (free-space check),
 * McSetErrorResult_375890 (result -> message code), McSaveSlotScanStep_374b00 (slot verdict)
 * and title_TitleStateCardCheck_4ed3c0 (the boot warning). No game data or game code. */
#define G_DATA_SIZE 0x1BC00 /* D_004658F8: the save file */
#define G_HDR_READ 0x800    /* D_004658F0: what the slot scan reads */
#define G_ICON_SYS 0x3C4
#define G_ICO_SIZE 0x5A40   /* stand-in for RG.ICO (the real size comes from the disc) */

static char g_p[256];
static const char *g_dir(int s) { snprintf(g_p, sizeof g_p, "/BASCUS-97490LV5RG_%02d", s); return g_p; }
static const char *g_data(int s)
{
    snprintf(g_p, sizeof g_p, "/BASCUS-97490LV5RG_%02d/BASCUS-97490LV5RG_%02d", s, s);
    return g_p;
}
static const char *g_icon(int s, int err)
{
    snprintf(g_p, sizeof g_p, "/BASCUS-97490LV5RG_%02d/%s", s, err ? "icon.err" : "icon.sys");
    return g_p;
}
static const char *g_ico(int s) { snprintf(g_p, sizeof g_p, "/BASCUS-97490LV5RG_%02d/RG.ICO", s); return g_p; }

/* SaveCalcSizeKB_3735e0: ceil(data/1K) + ceil(icon/1K) + 3 + 2 */
static int g_size_kb(int ico) { return (G_DATA_SIZE + 0x3FF) / 1024 + (ico + 0x3FF) / 1024 + 5; }

/* McGetInfoStep_375640's slot record {f0 present, f4 type, f8 formatted, f10 free, f18 changed} */
typedef struct g_ent {
    int present, type, formatted, freec, changed, result;
} g_ent;
static int g_getinfo(int port, g_ent *e)
{
    memset(e, 0, sizeof *e);
    int type = -1, fr = -1, fm = -1;
    CHECK(sceMcGetInfo(port, 1, &type, &fr, &fm) == 0);
    int b = mc_wait(NULL);
    e->type = type, e->freec = fr, e->formatted = fm;
    e->present = 1, e->changed = 1, e->result = b;
    if (b == 0)
        e->changed = 0;
    else if (b == -1)
        e->formatted = 1;
    else if (b == -2)
        e->formatted = 0;
    else if (b < -10)
        e->present = 0;
    return b;
}
/* McCardCheckFreeSpace_376220: 0 usable, 1 no PS2 card, 2 formatted but too full */
static int g_free_check(const g_ent *e, int need)
{
    if (!e->present || e->type != 2)
        return 1;
    if (e->formatted && e->freec < need)
        return 2;
    return 0;
}
/* McSetErrorResult_375890: libmc result -> the save manager's status word (mode 4 = save) */
static int g_err_code(int res, int mode)
{
    int out = 0;
    if (res == -2)
        out = 7;
    if (res == -3)
        out = 4;
    if (res == -1 || (res >= -19 && res <= -11) || (res >= -49 && res <= -40) || (res >= -59 && res <= -50) ||
        (res >= -79 && res <= -70))
        out = mode == 4 ? 6 : 8;
    return out;
}
/* title_TitleStateCardCheck_4ed3c0 after both slots: message id, or 0 = straight to the title */
static int g_boot_msg(const g_ent *e0, int saves0, const g_ent *e1, int saves1, int need)
{
    int r1 = g_free_check(e0, need), r2 = g_free_check(e1, need);
    if (r1 == 0 || r2 == 0 || saves0 > 0 || saves1 > 0)
        return 0;
    if (r1 == 1 && r2 == 1)
        return 0xC9; /* no memory card */
    if (r1 == 2 && r2 == 2)
        return 0xCB; /* not enough free space on either */
    return 0xCA;     /* not enough free space, needs N KB (formatted with the size) */
}

/* a synthetic save file: the game's header words (+4 = 0x25, +0x10 payload length,
 * +0x30 = 0x300) and a checksum standing in for the MD5 at +0x40 */
static uint32_t fnv32(const uint8_t *p, size_t n)
{
    uint32_t h = 2166136261u;
    for (size_t i = 0; i < n; i++)
        h = (h ^ p[i]) * 16777619u;
    return h;
}
static void g_make_save(uint8_t *b, uint32_t seed)
{
    for (int i = 0; i < G_DATA_SIZE; i++)
        b[i] = (uint8_t)((i * 131u + seed * 7u) >> 3);
    memset(b, 0, 0x50);
    b[4] = 0x25;
    b[8] = 1; /* the save counter McSaveStep_374110 stores (latest + 1) */
    uint32_t pl = G_DATA_SIZE - 0x50, hl = 0x300;
    memcpy(b + 0x10, &pl, 4);
    memcpy(b + 0x30, &hl, 4);
    memcpy(b + 0x50, &seed, 4);
    uint32_t h = fnv32(b + 0x50, 0x300);
    memcpy(b + 0x40, &h, 4);
}
/* SaveHeaderValidate_3e5100 stand-in: 0 ok, 9 bad magic, 0xB checksum */
static int g_check_hdr(const uint8_t *b, int n)
{
    if (n < G_HDR_READ)
        return 7;
    if (b[4] != 0x25 || b[5] != 0)
        return 9;
    uint32_t h;
    memcpy(&h, b + 0x40, 4);
    return h == fnv32(b + 0x50, 0x300) ? 0 : 0xB;
}
static void g_make_iconsys(uint8_t *b, const char *line1)
{
    memset(b, 0, G_ICON_SYS);
    memcpy(b, "PS2D", 4);
    /* title in full-width Shift-JIS, line break after the first line */
    int o = 0xC0, n = (int)strlen(line1);
    for (int i = 0; i < n && o < 0x100; i++) {
        unsigned c = (unsigned char)line1[i], w = 0x8140;
        if (c >= 'A' && c <= 'Z')
            w = 0x8260 + c - 'A';
        else if (c >= 'a' && c <= 'z')
            w = 0x8281 + c - 'a';
        else if (c >= '0' && c <= '9')
            w = 0x824F + c - '0';
        b[o++] = (uint8_t)(w >> 8);
        b[o++] = (uint8_t)w;
    }
    b[6] = (uint8_t)(o - 0xC0);
    memcpy(b + o, "\x82\x6b\x82\x85\x82\x96", 6); /* second line "Lev" */
    memcpy(b + 0x104, "RG.ICO", 7);
    memcpy(b + 0x144, "RG.ICO", 7);
    memcpy(b + 0x184, "RG.ICO", 7);
}

/* the chunked write loops of the save steps: first chunk `first`, then 0x200 */
static int g_write_all(int fd, const uint8_t *p, int n, int first)
{
    int done = 0, cmd = 0;
    while (done < n) {
        int k = done == 0 ? first : 0x200;
        if (k > n - done)
            k = n - done;
        CHECK(sceMcWrite(fd, p + done, k) == 0);
        int r = mc_wait(&cmd);
        CHECK(cmd == sceMcFuncNoWrite);
        if (r < 0)
            return r;
        done += r;
    }
    return 0;
}
/* flush (cmd 10) then close (cmd 3), as McSaveCreateStep_375090 checks */
static int g_flush_close(int fd)
{
    int cmd = 0, r;
    CHECK(sceMcFlush(fd) == 0);
    r = mc_wait(&cmd);
    CHECK(cmd == sceMcFuncNoFlush);
    if (r < 0)
        return r;
    CHECK(sceMcClose(fd) == 0);
    r = mc_wait(&cmd);
    CHECK(cmd == sceMcFuncNoClose);
    return r < 0 ? r : 0;
}
/* McSaveCreateStep_375090: mkdir (-4 tolerated), icon.sys (0x202), RG.ICO (0x203) */
static int g_create(int port, int s, const uint8_t *iconsys, const uint8_t *ico, int icolen)
{
    int cmd = 0, r;
    CHECK(sceMcMkdir(port, 1, g_dir(s)) == 0);
    r = mc_wait(&cmd);
    CHECK(cmd == sceMcFuncNoMkdir);
    if (r < 0 && r != -4)
        return r;
    CHECK(sceMcOpen(port, 1, g_icon(s, 0), MC_O_CREAT | MC_O_WRONLY) == 0);
    int fd = mc_wait(NULL);
    if (fd < 0)
        return fd;
    if ((r = g_write_all(fd, iconsys, G_ICON_SYS, G_ICON_SYS)) < 0 || (r = g_flush_close(fd)) < 0)
        return r;
    CHECK(sceMcOpen(port, 1, g_ico(s), MC_O_CREAT | MC_O_RDWR) == 0);
    fd = mc_wait(NULL);
    if (fd < 0)
        return fd;
    if ((r = g_write_all(fd, ico, icolen, 0x200)) < 0 || (r = g_flush_close(fd)) < 0)
        return r;
    return 0;
}
/* McSaveStep_374110: icon.sys -> icon.err, data (0x202, 0x200 chunks), icon.err
 * rewritten (mode 3), icon.err -> icon.sys, then GetInfo must answer 0 */
static int g_save(int port, int s, const uint8_t *data, const uint8_t *iconsys)
{
    int cmd = 0, r;
    CHECK(sceMcRename(port, 1, g_icon(s, 0), "icon.err") == 0);
    r = mc_wait(&cmd);
    CHECK(cmd == sceMcFuncNoRename);
    if (r < 0)
        return r;
    CHECK(sceMcOpen(port, 1, g_data(s), MC_O_CREAT | MC_O_WRONLY) == 0);
    int fd = mc_wait(NULL);
    if (fd < 0)
        return fd;
    if ((r = g_write_all(fd, data, G_DATA_SIZE, 0x200)) < 0 || (r = g_flush_close(fd)) < 0)
        return r;
    CHECK(sceMcOpen(port, 1, g_icon(s, 1), MC_O_RDWR) == 0);
    fd = mc_wait(NULL);
    if (fd < 0)
        return fd;
    if ((r = g_write_all(fd, iconsys, G_ICON_SYS, G_ICON_SYS)) < 0 || (r = g_flush_close(fd)) < 0)
        return r;
    CHECK(sceMcRename(port, 1, g_icon(s, 1), "icon.sys") == 0);
    if ((r = mc_wait(NULL)) < 0)
        return r;
    g_ent e;
    r = g_getinfo(port, &e);
    return r; /* McSaveStep state 0x12D: anything but 0 is status 0xC */
}
enum { G_EMPTY = 0, G_VALID, G_BADDATA, G_BROKEN };
/* McSaveDirScan_3748c0 + McSaveSlotScanStep_374b00 for slots 0..n-1; returns the GetDir
 * result of the root listing (< 0: the scan's error) */
static int g_scan(int port, int *st, int n)
{
    static sceMcTblGetDir root[50], ent[6], ic[9];
    static uint8_t hdr[G_HDR_READ];
    int cmd = 0;
    memset(root, 0, sizeof root);
    CHECK(sceMcGetDir(port, 1, "/BASCUS-97490LV5RG_??", 0, 0x32, root) == 0);
    int nr = mc_wait(&cmd);
    CHECK(cmd == sceMcFuncNoGetDir);
    if (nr < 0)
        return nr;
    for (int s = 0; s < n; s++) {
        char want[64];
        snprintf(want, sizeof want, "BASCUS-97490LV5RG_%02d", s);
        int have = 0;
        for (int i = 0; i < 50; i++)
            if (!strcmp((char *)root[i].EntryName, want))
                have = 1;
        st[s] = G_EMPTY;
        if (!have)
            continue;
        char pat[96];
        snprintf(pat, sizeof pat, "/BASCUS-97490LV5RG_%02d/*", s);
        CHECK(sceMcGetDir(port, 1, pat, 0, 6, ent) == 0);
        int r = mc_wait(&cmd);
        CHECK(cmd == sceMcFuncNoGetDir);
        if (r < 0) {
            st[s] = -100 + r;
            continue;
        }
        memset(ic, 0, sizeof ic);
        CHECK(sceMcGetDir(port, 1, g_icon(s, 0), 0, 1, ic) == 0);
        r = mc_wait(NULL);
        if (r <= 0 || ic[0].FileSizeByte != G_ICON_SYS) {
            st[s] = G_BROKEN;
            continue;
        }
        CHECK(sceMcOpen(port, 1, g_data(s), MC_O_RDONLY) == 0);
        int fd = mc_wait(NULL);
        if (fd < 0) {
            st[s] = G_BROKEN;
            continue;
        }
        memset(hdr, 0, sizeof hdr);
        CHECK(sceMcRead(fd, hdr, G_HDR_READ) == 0);
        int got = mc_wait(NULL);
        CHECK(sceMcClose(fd) == 0 && mc_wait(NULL) == 0);
        if (got < 0) {
            st[s] = G_BROKEN;
            continue;
        }
        /* SlotRecordStore_3e52f0 only accepts 0x800 bytes; f5C 0 / 10 = valid */
        int v = g_check_hdr(hdr, G_HDR_READ);
        st[s] = (v == 0 || v == 10) ? G_VALID : G_BADDATA;
    }
    return nr;
}
/* McLoadStep_373890: open mode 1, 0x800-byte reads until the size or a 0 read */
static int g_load(int port, int s, uint8_t *dst)
{
    CHECK(sceMcOpen(port, 1, g_data(s), MC_O_RDONLY) == 0);
    int fd = mc_wait(NULL);
    if (fd < 0)
        return fd;
    int got = 0;
    for (;;) {
        int k = G_DATA_SIZE - got < 0x800 ? G_DATA_SIZE - got : 0x800;
        CHECK(sceMcRead(fd, dst + got, k) == 0);
        int r = mc_wait(NULL);
        if (r < 0)
            return r;
        got += r;
        if (got >= G_DATA_SIZE || r == 0)
            break;
    }
    CHECK(sceMcClose(fd) == 0 && mc_wait(NULL) == 0);
    return got;
}
static uint8_t g_save_a[G_DATA_SIZE], g_save_b[G_DATA_SIZE], g_back[G_DATA_SIZE];
static uint8_t g_iconsys[G_ICON_SYS], g_icofile[G_ICO_SIZE];
static void g_fixtures(void)
{
    g_make_save(g_save_a, 1);
    g_make_save(g_save_b, 2);
    g_make_iconsys(g_iconsys, "Rogue Galaxy");
    for (int i = 0; i < G_ICO_SIZE; i++)
        g_icofile[i] = (uint8_t)(i ^ 0x5A);
}
static int host_file_equals(int port, const char *card_path, const uint8_t *want, long n)
{
    char hp[1024];
    mccard_host_path(port, card_path, hp, sizeof hp);
    FILE *f = fopen(hp, "rb");
    if (!f)
        return 0;
    static uint8_t buf[G_DATA_SIZE + 16];
    long got = (long)fread(buf, 1, sizeof buf, f);
    fclose(f);
    return got == n && memcmp(buf, want, (size_t)n) == 0;
}

/* --- 1. what GetInfo and the free-space check give the game in each card state ----------- */
static void m_mc_card_states(void *a)
{
    (void)a;
    const int need = g_size_kb(G_ICO_SIZE);
    CHECK(need == 111 + 23 + 5);
    CHECK(sceMcInit() == 0);
    g_ent e0, e1;
    /* slot 1: unformatted card; slot 2: none */
    CHECK(g_getinfo(0, &e0) == -2 && e0.present && e0.type == 2 && !e0.formatted);
    CHECK(g_getinfo(1, &e1) == MC_RES_NOCARD && !e1.present && e1.type == 0);
    CHECK(g_free_check(&e0, need) == 0); /* an unformatted card passes: the game offers to format */
    CHECK(g_free_check(&e1, need) == 1);
    CHECK(g_boot_msg(&e0, 0, &e1, 0, need) == 0);
    int st[4];
    CHECK(g_scan(0, st, 4) == -2 && g_err_code(-2, 3) == 7); /* "not formatted" */
    CHECK(g_scan(1, st, 4) == MC_RES_NOCARD && g_err_code(MC_RES_NOCARD, 3) == 8);
    CHECK(sceMcFormat(0, 1) == 0 && mc_wait(NULL) == 0); /* McFormatStep_3736b0 */
    CHECK(g_getinfo(0, &e0) == 0 && e0.formatted && e0.freec == 8000 && !e0.changed);
    CHECK(g_scan(0, st, 4) == 0 && st[0] == G_EMPTY);
    /* no card anywhere: the boot warning 0xC9 */
    mccard_eject(0);
    CHECK(g_getinfo(0, &e0) == MC_RES_NOCARD);
    CHECK(g_boot_msg(&e0, 0, &e1, 0, need) == 0xC9);
    /* a fresh card is "changed" once (-1): McGetInfoStep keeps f18 = 1, so the load / save
     * steps' McCardIsReady(.., 1) wants one more GetInfo, which answers 0 */
    CHECK(mccard_insert(0, MC_SLOT_AUTO) == 0);
    CHECK(g_getinfo(0, &e0) == -1 && e0.formatted && e0.changed);
    CHECK(g_getinfo(0, &e0) == 0 && !e0.changed);
    /* the GetInfo of McPollCardChange_372db0 passes NULL free / format */
    int type = -1;
    CHECK(sceMcGetInfo(0, 1, &type, NULL, NULL) == 0 && mc_wait(NULL) == 0 && type == 2);
    CHECK(sceMcEnd() == 1);
}
static void t_mc_card_states(void)
{
    boot(1, 5000);
    mc_boot("states", 0, MC_SLOT_UNFORMATTED, MC_SLOT_EMPTY, 1);
    mcserv_config sc;
    mcserv_default_config(&sc);
    sc.format_cycles = 147456000ull / 100;
    mcserv_configure(&sc);
    run_main(m_mc_card_states);
    mcserv_configure(NULL);
    mccard_shutdown();
}

/* --- 2. a full save cycle: create, save, overwrite, scan, load; free-space bookkeeping ---- */
static void m_mc_save_cycle(void *a)
{
    (void)a;
    const int need = g_size_kb(G_ICO_SIZE);
    CHECK(sceMcInit() == 0);
    g_ent e;
    CHECK(g_getinfo(0, &e) == -1);
    int free0 = e.freec;
    CHECK(g_create(0, 0, g_iconsys, g_icofile, G_ICO_SIZE) == 0);
    /* a new save is "create" then "save" (normal_TransSaveNewFileTickCb_519020) */
    CHECK(g_save(0, 0, g_save_a, g_iconsys) == 0);
    CHECK(g_getinfo(0, &e) == 0);
    int used = free0 - e.freec;
    /* the card's real cost never exceeds the game's estimate (dir 3 + root 1 + files) */
    CHECK(used == 3 + 1 + 1 + 23 + 111);
    CHECK(used <= need);
    /* the directory as the scan and the PS2 browser see it: creation order */
    static sceMcTblGetDir t[8];
    char pat[64];
    snprintf(pat, sizeof pat, "%s/*", g_dir(0));
    CHECK(sceMcGetDir(0, 1, pat, 0, 6, t) == 0 && mc_wait(NULL) == 5);
    CHECK(!strcmp((char *)t[2].EntryName, "icon.sys") && t[2].FileSizeByte == G_ICON_SYS);
    CHECK(!strcmp((char *)t[3].EntryName, "RG.ICO") && t[3].FileSizeByte == G_ICO_SIZE);
    CHECK(!strcmp((char *)t[4].EntryName, "BASCUS-97490LV5RG_00") && t[4].FileSizeByte == G_DATA_SIZE);
    int st[3];
    CHECK(g_scan(0, st, 3) == 1 && st[0] == G_VALID && st[1] == G_EMPTY);
    CHECK(g_load(0, 0, g_back) == G_DATA_SIZE && !memcmp(g_back, g_save_a, G_DATA_SIZE));
    /* overwrite (mode 4 only) keeps the size; a second slot */
    CHECK(g_save(0, 0, g_save_b, g_iconsys) == 0);
    CHECK(g_load(0, 0, g_back) == G_DATA_SIZE && !memcmp(g_back, g_save_b, G_DATA_SIZE));
    CHECK(g_create(0, 1, g_iconsys, g_icofile, G_ICO_SIZE) == 0 && g_save(0, 1, g_save_a, g_iconsys) == 0);
    CHECK(g_scan(0, st, 3) == 2 && st[0] == G_VALID && st[1] == G_VALID && st[2] == G_EMPTY);
    CHECK(g_getinfo(0, &e) == 0 && free0 - e.freec == 2 * used - 1); /* root: 4 entries, no growth */
    /* host side: plain files, the generated index names the save */
    CHECK(host_file_equals(0, g_data(0), g_save_b, G_DATA_SIZE));
    char ix[1024];
    snprintf(ix, sizeof ix, "%s/card1.txt", mccard_root());
    FILE *f = fopen(ix, "rb");
    static char txt[4096];
    size_t n = f ? fread(txt, 1, sizeof txt - 1, f) : 0;
    if (f)
        fclose(f);
    txt[n] = 0;
    CHECK(strstr(txt, "BASCUS-97490LV5RG_00") && strstr(txt, "Rogue Galaxy / Lev"));
    CHECK(sceMcEnd() == 1);
}
static void t_mc_save_cycle(void)
{
    boot(1, 5000);
    g_fixtures();
    mc_boot("cycle", 0, MC_SLOT_AUTO, MC_SLOT_EMPTY, 1);
    run_main(m_mc_save_cycle);
    mccard_shutdown();
}

/* --- 3. a full card: the boot warnings and the save's -3 --------------------------------- */
static void m_mc_full(void *a)
{
    (void)a;
    const int need = g_size_kb(G_ICO_SIZE);
    CHECK(sceMcInit() == 0);
    g_ent e0, e1;
    CHECK(g_getinfo(0, &e0) == -1 && g_getinfo(1, &e1) == -1);
    /* both cards formatted with need - 1 KB free: "not enough space" on both */
    CHECK(e0.freec == need - 1 && g_free_check(&e0, need) == 2);
    CHECK(g_boot_msg(&e0, 0, &e1, 0, need) == 0xCB);
    g_ent none = {0};
    CHECK(g_boot_msg(&e0, 0, &none, 0, need) == 0xCA);
    CHECK(g_boot_msg(&e0, 1, &e1, 0, need) == 0); /* a save on either card: no warning */
    /* saving anyway: the data file is the first thing that does not fit -> -3 -> status 4 */
    CHECK(g_create(0, 0, g_iconsys, g_icofile, G_ICO_SIZE) == 0);
    int r = g_save(0, 0, g_save_a, g_iconsys);
    CHECK(r == MC_RES_FULLDEVICE && g_err_code(r, 4) == 4);
    /* that save is left broken (icon.err), exactly as on a PS2 */
    int st[1];
    CHECK(g_scan(0, st, 1) == 1 && st[0] == G_BROKEN);
    CHECK(g_getinfo(1, &e1) == 0 && e1.freec == need - 1);
    CHECK(sceMcEnd() == 1);
}
static void t_mc_full(void)
{
    boot(1, 5000);
    g_fixtures();
    const int need = g_size_kb(G_ICO_SIZE);
    /* an empty card's free count is free_clusters (the root's first cluster is in it) */
    mc_boot("full", (uint32_t)(need - 1), MC_SLOT_AUTO, MC_SLOT_AUTO, 1);
    run_main(m_mc_full);
    mccard_shutdown();
}
static void m_mc_exact_fit(void *a)
{
    (void)a;
    CHECK(sceMcInit() == 0);
    g_ent e;
    CHECK(g_getinfo(0, &e) == -1 && e.freec == g_size_kb(G_ICO_SIZE) && g_free_check(&e, e.freec) == 0);
    CHECK(g_create(0, 0, g_iconsys, g_icofile, G_ICO_SIZE) == 0);
    CHECK(g_save(0, 0, g_save_a, g_iconsys) == 0);
    int st[1];
    CHECK(g_scan(0, st, 1) == 1 && st[0] == G_VALID);
    CHECK(sceMcEnd() == 1);
}
static void t_mc_exact_fit(void)
{
    boot(1, 5000);
    g_fixtures();
    mc_boot("fit", (uint32_t)g_size_kb(G_ICO_SIZE), MC_SLOT_AUTO, MC_SLOT_EMPTY, 1);
    run_main(m_mc_exact_fit);
    mccard_shutdown();
}

/* --- 4. corrupt saves: what the slot scan concludes -------------------------------------- */
static void put_host(int port, const char *card_path, const void *p, size_t n)
{
    char hp[1024];
    mccard_host_path(port, card_path, hp, sizeof hp);
    FILE *f = fopen(hp, "wb");
    CHECK(f != NULL);
    if (f) {
        if (n)
            fwrite(p, 1, n, f);
        fclose(f);
    }
}
static void m_mc_corrupt(void *a)
{
    (void)a;
    CHECK(sceMcInit() == 0);
    g_ent e;
    CHECK(g_getinfo(0, &e) == -1 || e.result == 0);
    int st[6];
    CHECK(g_scan(0, st, 6) == 6);
    CHECK(st[0] == G_VALID);   /* intact */
    CHECK(st[1] == (g_control ? G_VALID : G_BROKEN)); /* interrupted overwrite: icon.err, no icon.sys */
    CHECK(st[2] == G_BROKEN);  /* icon.sys of the wrong size */
    CHECK(st[3] == G_BROKEN);  /* data file missing */
    CHECK(st[4] == G_BADDATA); /* data present but its checksum is wrong */
    CHECK(st[5] == G_BADDATA); /* data shorter than the 0x800-byte header */
    /* a short file reads short, then 0: McLoadStep_373890 stops on the 0 read */
    CHECK(sceMcOpen(0, 1, g_data(5), MC_O_RDONLY) == 0);
    int fd = mc_wait(NULL);
    static uint8_t b[0x800];
    CHECK(sceMcRead(fd, b, 0x800) == 0 && mc_wait(NULL) == 100);
    CHECK(sceMcRead(fd, b, 0x800) == 0 && mc_wait(NULL) == 0);
    CHECK(sceMcClose(fd) == 0 && mc_wait(NULL) == 0);
    CHECK(sceMcEnd() == 1);
}
static void t_mc_corrupt(void)
{
    boot(1, 5000);
    g_fixtures();
    mc_boot("corrupt", 0, MC_SLOT_AUTO, MC_SLOT_EMPTY, 1);
    /* lay the cards out on the host, as a hand-copied or damaged save would be */
    for (int s = 0; s < 6; s++) {
        CHECK(mccard_open(0, g_dir(s), MC_O_MKDIR) == 0);
        if (s == 1)
            put_host(0, g_icon(s, 1), g_iconsys, G_ICON_SYS);
        else
            put_host(0, g_icon(s, 0), g_iconsys, s == 2 ? G_ICON_SYS - 4 : G_ICON_SYS);
        put_host(0, g_ico(s), g_icofile, G_ICO_SIZE);
        if (s == 3)
            continue;
        if (s == 4) {
            static uint8_t bad[G_DATA_SIZE];
            memcpy(bad, g_save_a, sizeof bad);
            bad[0x60] ^= 0xFF;
            put_host(0, g_data(s), bad, sizeof bad);
        } else {
            put_host(0, g_data(s), g_save_a, s == 5 ? 100 : G_DATA_SIZE);
        }
    }
    mccard_shutdown();
    mc_boot("corrupt", 0, MC_SLOT_IF_EXISTS, MC_SLOT_EMPTY, 0); /* adopt the host files */
    run_main(m_mc_corrupt);
    mccard_shutdown();
}

static int newest_snapshot(int port, int s, char *out, int n);
static int newest_backup_holds(int port, int s, const uint8_t *want);
static void copy_file(const char *from, const char *to);

/* --- 5. a write failure mid-save: the card pulled during the data write --------------------- */
static void m_mc_write_fail(void *a)
{
    (void)a;
    CHECK(sceMcInit() == 0);
    g_ent e;
    g_getinfo(0, &e);
    CHECK(g_create(0, 0, g_iconsys, g_icofile, G_ICO_SIZE) == 0 && g_save(0, 0, g_save_a, g_iconsys) == 0);
    CHECK(mccard_backup_count(0, g_dir(0)) == 0); /* nothing to back up before the first save */
    /* overwrite with B; the card goes away on the 40th card operation (inside the data) */
    mccard_inject_fault(0, 40, MC_RES_NOCARD);
    int r = g_save(0, 0, g_save_b, g_iconsys);
    CHECK(r == MC_RES_NOCARD && g_err_code(r, 4) == 6); /* "removed during save" */
    CHECK(!mccard_present(0));
    CHECK(g_getinfo(0, &e) == MC_RES_NOCARD && !e.present);
    /* the host still holds save A whole (the partial write was never committed), and a
     * backup of A was taken before the overwrite began */
    CHECK(host_file_equals(0, g_data(0), g_control ? g_save_b : g_save_a, G_DATA_SIZE));
    CHECK(mccard_backup_count(0, g_dir(0)) == 1);
    /* the card comes back: the slot is broken (icon.err), as the game would show it */
    CHECK(mccard_insert(0, MC_SLOT_IF_EXISTS) == 0);
    CHECK(g_getinfo(0, &e) == -1);
    int st[1];
    CHECK(g_scan(0, st, 1) == 1 && st[0] == G_BROKEN);
    /* a failing flush (-5) and a full card (-3) report through the same path */
    mccard_inject_fault(0, 3, MC_RES_DENIEDPERMIT);
    CHECK(sceMcOpen(0, 1, "/f", MC_O_CREAT | MC_O_WRONLY) == 0);
    int fd = mc_wait(NULL);
    CHECK(fd >= 0 && sceMcWrite(fd, g_save_a, 10) == 0 && mc_wait(NULL) == 10);
    CHECK(sceMcFlush(fd) == 0 && mc_wait(NULL) == MC_RES_DENIEDPERMIT);
    CHECK(sceMcClose(fd) == 0 && mc_wait(NULL) == 0);
    CHECK(mccard_open_count() == 0);
    CHECK(sceMcEnd() == 1);
}
static void t_mc_write_fail(void)
{
    boot(1, 5000);
    g_fixtures();
    mc_boot("wfail", 0, MC_SLOT_AUTO, MC_SLOT_EMPTY, 1);
    run_main(m_mc_write_fail);
    mccard_inject_fault(0, 0, 0);
    /* restore the backup by hand (copy the snapshot's files back, drop icon.err; what
     * `ps2card.py restore` does) and the slot is valid again with save A */
    mccard_shutdown();
    mc_boot("wfail", 0, MC_SLOT_IF_EXISTS, MC_SLOT_EMPTY, 0);
    CHECK(mccard_backup_count(0, g_dir(0)) == 1);
    CHECK(newest_backup_holds(0, 0, g_save_a));
    char snap[1100], from[1300], hp[1024];
    CHECK(newest_snapshot(0, 0, snap, sizeof snap));
    static const char *names[] = {"icon.sys", "RG.ICO", "BASCUS-97490LV5RG_00"};
    for (int i = 0; i < 3; i++) {
        char cp[128];
        snprintf(from, sizeof from, "%s/%s", snap, names[i]);
        snprintf(cp, sizeof cp, "%s/%s", g_dir(0), names[i]);
        mccard_host_path(0, cp, hp, sizeof hp);
        copy_file(from, hp);
    }
    mccard_host_path(0, g_icon(0, 1), hp, sizeof hp);
    CHECK(remove(hp) == 0);
    mccard_shutdown();
    mc_boot("wfail", 0, MC_SLOT_IF_EXISTS, MC_SLOT_EMPTY, 0);
    int fd = mccard_open(0, g_data(0), MC_O_RDONLY);
    static uint8_t b[G_DATA_SIZE];
    CHECK(fd >= 0 && mccard_read(fd, b, G_DATA_SIZE) == G_DATA_SIZE && !memcmp(b, g_save_a, G_DATA_SIZE));
    mccard_close(fd);
    mccard_shutdown();
}

/* --- 6. backups: one per overwrite, the previous save, a keep limit; format keeps a copy ---- */
/* the newest snapshot (names sort in time order) holds `want` as slot s's data file */
static int newest_snapshot(int port, int s, char *out, int n)
{
    char bdir[1024], best[256] = "";
    mccard_backup_dir(port, g_dir(s), bdir, sizeof bdir);
#ifdef _WIN32
    char pat[1100];
    snprintf(pat, sizeof pat, "%s/*", bdir);
    struct _finddata_t fd;
    intptr_t h = _findfirst(pat, &fd);
    if (h == -1)
        return 0;
    do {
        if (fd.name[0] != '.' && (fd.attrib & _A_SUBDIR) && strcmp(fd.name, best) > 0)
            snprintf(best, sizeof best, "%s", fd.name);
    } while (_findnext(h, &fd) == 0);
    _findclose(h);
#else
    DIR *d = opendir(bdir);
    if (!d)
        return 0;
    struct dirent *e;
    while ((e = readdir(d)))
        if (e->d_name[0] != '.' && strcmp(e->d_name, best) > 0)
            snprintf(best, sizeof best, "%s", e->d_name);
    closedir(d);
#endif
    if (!best[0])
        return 0;
    snprintf(out, (size_t)n, "%s/%s", bdir, best);
    return 1;
}
static int file_equals(const char *p, const uint8_t *want, long n)
{
    FILE *f = fopen(p, "rb");
    if (!f)
        return 0;
    static uint8_t buf[G_DATA_SIZE + 16];
    long got = (long)fread(buf, 1, sizeof buf, f);
    fclose(f);
    return got == n && memcmp(buf, want, (size_t)n) == 0;
}
static int newest_backup_holds(int port, int s, const uint8_t *want)
{
    char snap[1100], p[1300];
    if (!newest_snapshot(port, s, snap, sizeof snap))
        return 0;
    snprintf(p, sizeof p, "%s/BASCUS-97490LV5RG_%02d", snap, s);
    return file_equals(p, want, G_DATA_SIZE);
}
static void copy_file(const char *from, const char *to)
{
    static uint8_t buf[G_DATA_SIZE + 0x10000];
    FILE *f = fopen(from, "rb");
    size_t n = f ? fread(buf, 1, sizeof buf, f) : 0;
    if (f)
        fclose(f);
    f = fopen(to, "wb");
    CHECK(f != NULL);
    if (f) {
        fwrite(buf, 1, n, f);
        fclose(f);
    }
}

static void m_mc_backup(void *a)
{
    (void)a;
    CHECK(sceMcInit() == 0);
    g_ent e;
    g_getinfo(0, &e);
    CHECK(g_create(0, 0, g_iconsys, g_icofile, G_ICO_SIZE) == 0);
    CHECK(g_save(0, 0, g_save_a, g_iconsys) == 0);
    CHECK(mccard_backup_count(0, g_dir(0)) == 0); /* create + first save: nothing old to keep */
    CHECK(g_save(0, 0, g_save_b, g_iconsys) == 0);
    CHECK(mccard_backup_count(0, g_dir(0)) == 1);
    CHECK(g_save(0, 0, g_save_b, g_iconsys) == 0);
    CHECK(mccard_backup_count(0, g_dir(0)) == 2);
    CHECK(g_save(0, 0, g_save_b, g_iconsys) == 0); /* same contents as the newest backup: none */
    CHECK(mccard_backup_count(0, g_dir(0)) == 2);
    /* reads never back up */
    int st[1];
    CHECK(g_scan(0, st, 1) == 1 && st[0] == G_VALID && mccard_backup_count(0, g_dir(0)) == 2);
    for (int i = 0; i < 4; i++) { /* alternate A / B: every overwrite backs up; keep 3 */
        CHECK(g_save(0, 0, (i & 1) ? g_save_b : g_save_a, g_iconsys) == 0);
    }
    CHECK(mccard_backup_count(0, g_dir(0)) == 3);
    /* the newest backup is the save before the last overwrite (A) */
    CHECK(newest_backup_holds(0, 0, g_save_a));
    /* formatting erases the card but keeps a backup of the save (B now) */
    CHECK(sceMcFormat(0, 1) == 0 && mc_wait(NULL) == 0);
    CHECK(mccard_backup_count(0, g_dir(0)) == 3);
    CHECK(newest_backup_holds(0, 0, g_save_b));
    int st2[1];
    CHECK(g_scan(0, st2, 1) == 0 && st2[0] == G_EMPTY);
    CHECK(sceMcEnd() == 1);
}
static void t_mc_backup(void)
{
    boot(1, 5000);
    g_fixtures();
    char dir[1024];
    tmpdir("backup", dir, sizeof dir, 1);
    static char root[1024];
    snprintf(root, sizeof root, "%s", dir);
    mccard_config c;
    mccard_default_config(&c);
    c.root = root;
    c.slot_policy[1] = MC_SLOT_EMPTY;
    c.clock = rg_mc_virtual_clock;
    c.backup_keep = 3;
    CHECK(mccard_init(&c) == 0);
    rg_mc_reset();
    mcserv_config sc;
    mcserv_default_config(&sc);
    sc.format_cycles = 147456000ull / 100;
    mcserv_configure(&sc);
    run_main(m_mc_backup);
    mcserv_configure(NULL);
    mccard_shutdown();
}

/* --- 7. host layout: legacy slot0 moves to card1, stale temp files go -------------------- */
static void t_mc_layout(void)
{
    g_fixtures();
    char dir[1024], p[1200];
    tmpdir("layout", dir, sizeof dir, 1);
#ifdef _WIN32
    _mkdir(dir);
#else
    mkdir(dir, 0777);
#endif
    snprintf(p, sizeof p, "%s/slot0", dir);
#ifdef _WIN32
    _mkdir(p);
#else
    mkdir(p, 0777);
#endif
    snprintf(p, sizeof p, "%s/slot0/BASCUS-97490LV5RG_00", dir);
#ifdef _WIN32
    _mkdir(p);
#else
    mkdir(p, 0777);
#endif
    snprintf(p, sizeof p, "%s/slot0/BASCUS-97490LV5RG_00/icon.sys", dir);
    FILE *f = fopen(p, "wb");
    if (f) {
        fwrite(g_iconsys, 1, sizeof g_iconsys, f);
        fclose(f);
    }
    snprintf(p, sizeof p, "%s/slot0/BASCUS-97490LV5RG_00/icon.sys%%~tmp", dir); /* a crashed write */
    f = fopen(p, "wb");
    if (f) {
        fputs("partial", f);
        fclose(f);
    }
    mc_boot("layout", 0, MC_SLOT_IF_EXISTS, MC_SLOT_EMPTY, 0);
    CHECK(mccard_present(0));
    mc_dirent t[8];
    CHECK(mccard_getdir(0, "/BASCUS-97490LV5RG_00/*", 0, 8, t) == 3); /* . .. icon.sys */
    struct stat st;
    snprintf(p, sizeof p, "%s/card1/BASCUS-97490LV5RG_00/icon.sys", dir);
    CHECK(stat(p, &st) == 0);
    snprintf(p, sizeof p, "%s/card1/BASCUS-97490LV5RG_00/icon.sys%%~tmp", dir);
    CHECK(stat(p, &st) != 0);
    snprintf(p, sizeof p, "%s/slot0", dir);
    CHECK(stat(p, &st) != 0);
    snprintf(p, sizeof p, "%s/card1.card", dir);
    CHECK(stat(p, &st) == 0);
    mccard_shutdown();
}

/* --- 8. a crash mid-write (no flush, no close, no shutdown): the host keeps the old file ---- */
static void t_mc_crash_write(void)
{
    g_fixtures();
    mc_boot("crash", 0, MC_SLOT_AUTO, MC_SLOT_EMPTY, 1);
    CHECK(mccard_open(0, g_dir(0), MC_O_MKDIR) == 0);
    int fd = mccard_open(0, g_data(0), MC_O_CREAT | MC_O_WRONLY);
    CHECK(fd >= 0 && mccard_write(fd, g_save_a, G_DATA_SIZE) == G_DATA_SIZE && mccard_close(fd) == 0);
    fd = mccard_open(0, g_data(0), MC_O_CREAT | MC_O_WRONLY);
    CHECK(fd >= 0 && mccard_write(fd, g_save_b, G_DATA_SIZE / 2) == G_DATA_SIZE / 2);
    /* a crash: the process ends here with the second write uncommitted */
    fflush(stderr);
    printf("%-24s %s\n", "mc_crash_write", g_fail ? "FAIL" : "PASS");
    fflush(stdout);
    _exit(g_fail ? 1 : 0);
}
static void t_mc_crash_read(void)
{
    g_fixtures();
    mc_boot("crash", 0, MC_SLOT_IF_EXISTS, MC_SLOT_EMPTY, 0);
    int fd = mccard_open(0, g_data(0), MC_O_RDONLY);
    static uint8_t b[G_DATA_SIZE];
    CHECK(fd >= 0 && mccard_read(fd, b, G_DATA_SIZE) == G_DATA_SIZE);
    CHECK(!memcmp(b, g_control ? g_save_b : g_save_a, G_DATA_SIZE));
    mccard_close(fd);
    mccard_shutdown();
}

/* --- 8b. a card written by tools/saves/ps2card.py (padmc.ps2card leaves it) --------------- */
static void m_mc_pyimport(void *a)
{
    (void)a;
    CHECK(sceMcInit() == 0);
    g_ent e;
    CHECK(g_getinfo(0, &e) == -1);
    int st[4];
    CHECK(g_scan(0, st, 4) == 2);
    /* the synthetic saves carry real MD5 digests, not this file's checksum: readable data
     * (bad data here), never broken or missing */
    CHECK(st[0] == G_VALID || st[0] == G_BADDATA);
    CHECK(st[3] == G_VALID || st[3] == G_BADDATA);
    CHECK(st[1] == G_EMPTY && st[2] == G_EMPTY);
    static sceMcTblGetDir t[8];
    char pat[64];
    snprintf(pat, sizeof pat, "%s/*", g_dir(3));
    CHECK(sceMcGetDir(0, 1, pat, 0, 8, t) == 0 && mc_wait(NULL) == 5);
    CHECK(!strcmp((char *)t[2].EntryName, "icon.sys") && t[2].FileSizeByte == G_ICON_SYS);
    CHECK(!strcmp((char *)t[3].EntryName, "RG.ICO") && t[3].FileSizeByte == 23000);
    CHECK(!strcmp((char *)t[4].EntryName, "BASCUS-97490LV5RG_03") && t[4].FileSizeByte == G_DATA_SIZE);
    CHECK(sceMcGetDir(0, 1, "/BASCUS-97490LV5RG_03", 0, 1, t) == 0 && mc_wait(NULL) == 1);
    CHECK(t[0]._Create.Year == 2006 && t[0]._Create.Month == 5 && t[0]._Create.Day == 4 && t[0]._Create.Sec == 1);
    CHECK(t[0]._Modify.Month == 10 && t[0].AttrFile == 0x8427);
    CHECK(sceMcEnd() == 1);
}
static void t_mc_pyimport(void)
{
    boot(1, 5000);
    mc_boot("pyimport", 0, MC_SLOT_IF_EXISTS, MC_SLOT_EMPTY, 0);
    CHECK(mccard_present(0));
    run_main(m_mc_pyimport);
    mccard_shutdown();
}

/* --- 9. the game's own save state machines on this card model ----------------------------- *
 * McGetInfoStep / McSaveCreateStep / McSaveStep / McSaveDirScan + McSaveSlotScanStep /
 * McLoadStep / McFormatStep and the result mapping McSetErrorResult, compiled from game/
 * (skipped when not ingested). Serialisation and the header check are stubs (the synthetic
 * save above); everything that talks to the card is the game's code. */
#ifdef RG_PADMC_GAME_MC
typedef int32_t s32g;
/* the save manager object (D_004831D0), offsets from the game's accessors */
static uint8_t g_mgr[0x600] __attribute__((aligned(16)));
static uint8_t g_dirtab[50 * 64] __attribute__((aligned(16)));
static uint8_t g_dir6[6 * 64] __attribute__((aligned(16)));
static uint8_t g_dir9[9 * 64] __attribute__((aligned(16)));
static uint8_t g_dbuf[0x20000] __attribute__((aligned(16)));
static uint8_t g_gd[0x100] __attribute__((aligned(16)));    /* GetGameData_1fede0() */
static uint8_t g_gd24[0x1190] __attribute__((aligned(16))); /* *(GameData + 0x24) */
static int32_t g_zero;
static const uint8_t *g_cur_save;
static int g_loaded_len;
#define MGR(off, T) (*(T *)(g_mgr + (off)))
static void put32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }

/* data the compiled units reference (values from game/src/main_data) */
uint32_t D_004658F0[2] = {0x800, 0};
uint32_t D_004658F8[2] = {0x1BC00, 0};
char D_00453F10[129] = "/BASCUS-97490LV5RG_??";
char D_004638C8[8] = "/";
char D_004638D0[8] = "..";
char D_004638D8[16] = "icon.err";
char D_004638E8[24] = "icon.sys";
char D_00463900[32] = "BASCUS-97490LV5RG_%02d";
char D_00463920[32] = "/BASCUS-97490LV5RG_%02d/*";
char D_00463A00[24] = "/BASCUS-97490LV5RG_%02d";
char D_00463A18[16] = "/icon.sys";
char D_00463A28[24] = "/icon.err";
int32_t D_00483198, D_004831A4, D_0048316C, D_00483170, D_00483174, D_00483178[2];
int16_t D_004831A8, D_00483180;
uint8_t D_00483184;
static void g_on_loaded(void *m, int32_t buf, int32_t len)
{
    (void)m;
    (void)buf;
    g_loaded_len = len;
}
void (*D_0047FAA4)(void *, int32_t, int32_t) = g_on_loaded;

/* the game functions under test */
extern s32g McGetInfoStep_375640(void *);
extern s32g McFormatStep_3736b0(void *);
extern s32g McSaveCreateStep_375090(void *);
extern s32g McSaveStep_374110(void *);
extern s32g McLoadStep_373890(void *);
extern s32g McSaveDirScan_3748c0(void *);
extern s32g McSetErrorResult_375890(void *, s32g);
extern s32g McCardCheckFreeSpace_376220(void *, s32g);
extern s32g McCardIsReady_376280(void *, void *);
extern s32g SaveCalcSizeKB_3735e0(void *);
extern s32g SaveSlotEntryIsValid_376050(void *);
extern s32g SaveSlotEntryIsEmpty_376170(void *);
extern s32g SaveSlotEntryIsBroken_3760f0(void *);
extern int16_t McPollCardChange_372db0(void);

/* stubs for what lies outside the card path */
void *GetGameData_1fede0(void) { return g_gd; }
s32g McSaveSerialize_375c60(void *m)
{
    (void)m;
    memcpy(g_dbuf, g_cur_save, G_DATA_SIZE);
    MGR(0x510, int32_t) = G_DATA_SIZE;
    return 1;
}
s32g SaveDataBuildWriteBuffer_375b80(void *m) { return McSaveSerialize_375c60(m); }
s32g SlotRecordFindLatestMaybe_3e4c90(void *g, s32g k)
{
    (void)g;
    (void)k;
    return 0; /* McSaveStep stores this + 1 at data + 8 (g_make_save writes 1 there) */
}
void *SlotRecordStore_3e52f0(void *sys, int16_t idx, s32g buf, s32g len)
{
    (void)idx;
    int v = g_check_hdr((const uint8_t *)(uintptr_t)(uint32_t)buf, len);
    put32((uint8_t *)sys + 0x5C, (uint32_t)v); /* SaveDataSetError_3e6340's code */
    return v == 0 ? (void *)g_gd : NULL;
}
s32g McSaveFlagMergeEnabledMaybe_373150(void) { return 0; }
void McSaveHeaderMergeFlagsMaybe_373060(void *r) { (void)r; }
void McSaveHeaderCheckClearedMaybe_372fd0(void *r, s32g p) { (void)r, (void)p; }
void McSaveClearedFlagReset_372fa0(s32g p) { (void)p; }
void SaveSetLastSlot_376210(s32g p, s32g s) { (void)p, (void)s; }
#include <stdarg.h>
void Sprintf_1343b8(char *dst, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf(dst, fmt, ap);
    va_end(ap);
}

static void mgr_reset(int port, int slot)
{
    memset(g_mgr, 0, sizeof g_mgr);
    memset(g_gd, 0, sizeof g_gd);
    put32(g_gd + 0x24, (uint32_t)(uintptr_t)g_gd24);
    put32(g_gd24 + 0x1188, (uint32_t)(uintptr_t)&g_zero);
    strcpy((char *)g_mgr, "RG.ICO"); /* SaveIconFilesSetAll_375b10 */
    put32(g_mgr + 0x60, (uint32_t)(uintptr_t)g_icofile);
    put32(g_mgr + 0x6C, G_ICO_SIZE);
    memcpy(g_mgr + 0xE0, g_iconsys, G_ICON_SYS); /* SaveIconSysBuild_375d10 */
    MGR(0x4EC, int16_t) = (int16_t)port;
    MGR(0x4EE, int16_t) = (int16_t)slot;
    put32(g_mgr + 0x500, (uint32_t)(uintptr_t)g_dirtab);
    put32(g_mgr + 0x504, (uint32_t)(uintptr_t)g_dir6);
    put32(g_mgr + 0x508, (uint32_t)(uintptr_t)g_dir9);
    put32(g_mgr + 0x50C, (uint32_t)(uintptr_t)g_dbuf);
}
/* SaveModeDispatch_375df0, one call per frame: 1 = done; other nonzero -> McSetErrorResult
 * and the step runs again. Returns the status word (+0x4F0) the UI reads. */
static int g_mode(s32g (*step)(void *), int mode)
{
    MGR(0x4DC, int32_t) = mode;
    MGR(0x4E0, int32_t) = 0;
    for (int it = 0; it < 400000; it++) {
        s32g t = step(g_mgr);
        if (t == 1)
            return MGR(0x4F0, int16_t);
        if (t != 0)
            McSetErrorResult_375890(g_mgr, t);
    }
    fprintf(stderr, "  mode %d did not finish\n", mode);
    g_fail++;
    return -1;
}
static uint8_t *g_ent_of(int port) { return g_mgr + 0x4A4 + port * 0x1C; }
static uint8_t *g_slot_of(int s) { return g_mgr + 0x78 + s * 2; }

static void m_mc_game(void *a)
{
    (void)a;
    CHECK(sceMcInit() == 0);
    const int need = 111 + 23 + 5;
    /* --- boot check on an empty formatted card: mode 0 then mode 3 (title state 14) */
    mgr_reset(0, 0);
    CHECK(SaveCalcSizeKB_3735e0(g_mgr) == need);
    CHECK(g_mode(McGetInfoStep_375640, 0) == 0);
    int32_t *e = (int32_t *)g_ent_of(0);
    CHECK(e[0] == 1 && e[1] == 2 && e[2] == 1 && e[4] == 8000 && e[5] == -1 && e[6] == 1); /* fresh: f18 = 1 */
    CHECK(McCardIsReady_376280(e, (void *)1) == 0);              /* the -1: not ready for a save yet */
    CHECK(g_mode(McGetInfoStep_375640, 0) == 0 && e[6] == 0 && McCardIsReady_376280(e, (void *)1) == 1);
    CHECK(McCardCheckFreeSpace_376220(e, need) == 0);
    CHECK(g_mode(McSaveDirScan_3748c0, 3) == 0 && SaveSlotEntryIsEmpty_376170(g_slot_of(0)));
    /* --- slot 2: no card */
    MGR(0x4EC, int16_t) = 1;
    CHECK(g_mode(McGetInfoStep_375640, 0) == 0);
    CHECK(((int32_t *)g_ent_of(1))[0] == 0 && McCardCheckFreeSpace_376220(g_ent_of(1), need) == 1);
    CHECK(g_mode(McSaveDirScan_3748c0, 3) == 8); /* GetDir -12 -> 8 */
    MGR(0x4EC, int16_t) = 0;
    /* --- a new save in slot 0: create (mode 2) then save (mode 4) */
    g_cur_save = g_save_a;
    CHECK(g_mode(McSaveCreateStep_375090, 2) == 0);
    CHECK(g_mode(McSaveStep_374110, 4) == 0);
    CHECK(host_file_equals(0, g_data(0), g_save_a, G_DATA_SIZE));
    CHECK(host_file_equals(0, g_icon(0, 0), g_iconsys, G_ICON_SYS));
    CHECK(host_file_equals(0, g_ico(0), g_icofile, G_ICO_SIZE));
    CHECK(g_mode(McSaveDirScan_3748c0, 3) == 0 && SaveSlotEntryIsValid_376050(g_slot_of(0)));
    CHECK(SaveSlotEntryIsEmpty_376170(g_slot_of(1)));
    /* --- load it back (mode 5) */
    memset(g_dbuf, 0, sizeof g_dbuf);
    put32(g_mgr + 0x50C, (uint32_t)(uintptr_t)g_dbuf);
    CHECK(g_mode(McLoadStep_373890, 5) == 0 && g_loaded_len == G_DATA_SIZE);
    CHECK(!memcmp(g_dbuf, g_save_a, G_DATA_SIZE));
    /* --- overwrite with B (mode 4 only); a backup of A appears */
    g_cur_save = g_save_b;
    CHECK(g_mode(McSaveStep_374110, 4) == 0);
    CHECK(host_file_equals(0, g_data(0), g_save_b, G_DATA_SIZE));
    CHECK(mccard_backup_count(0, g_dir(0)) == 1 && newest_backup_holds(0, 0, g_save_a));
    /* --- card pulled in the middle of the overwrite: status 6, slot broken afterwards */
    g_cur_save = g_save_a;
    mccard_inject_fault(0, 30, MC_RES_NOCARD);
    CHECK(g_mode(McSaveStep_374110, 4) == 6);
    CHECK(host_file_equals(0, g_data(0), g_control ? g_save_a : g_save_b, G_DATA_SIZE)); /* B intact */
    CHECK(mccard_insert(0, MC_SLOT_IF_EXISTS) == 0);
    CHECK(g_mode(McGetInfoStep_375640, 0) == 0 && g_mode(McGetInfoStep_375640, 0) == 0);
    CHECK(g_mode(McSaveDirScan_3748c0, 3) == 0 && SaveSlotEntryIsBroken_3760f0(g_slot_of(0)));
    /* the game cannot overwrite a broken slot (TransSaveSlotListConfirm refuses it); after a
     * restore from the backup it is valid again (done in t_mc_game) */
    /* --- bad data: a save whose checksum fails scans as "bad data" (overwritable) */
    {
        static uint8_t bad[G_DATA_SIZE];
        memcpy(bad, g_save_a, sizeof bad);
        bad[0x70] ^= 1;
        g_cur_save = bad;
        MGR(0x4EE, int16_t) = 1;
        CHECK(g_mode(McSaveCreateStep_375090, 2) == 0 && g_mode(McSaveStep_374110, 4) == 0);
        CHECK(g_mode(McSaveDirScan_3748c0, 3) == 0);
        CHECK(g_slot_of(1)[0] == 1 && g_slot_of(1)[1] == 2); /* SaveSlotEntrySetBadData */
        MGR(0x4EE, int16_t) = 0;
    }
    /* --- full card: the scan marks free slots "no space"; the save stops with status 4 */
    CHECK(g_mode(McGetInfoStep_375640, 0) == 0);
    int free_now = ((int32_t *)g_ent_of(0))[4];
    CHECK(free_now == 8000 - (2 * need - 1)); /* two saves (139 with the root's growth, 138) */
    CHECK(sceMcEnd() == 1);
}
static void m_mc_game_full(void *a)
{
    (void)a;
    const int need = 111 + 23 + 5;
    CHECK(sceMcInit() == 0);
    mgr_reset(0, 0);
    CHECK(g_mode(McGetInfoStep_375640, 0) == 0 && g_mode(McGetInfoStep_375640, 0) == 0);
    int32_t *e = (int32_t *)g_ent_of(0);
    CHECK(e[4] == need - 1 && McCardCheckFreeSpace_376220(e, need) == 2);
    CHECK(g_mode(McSaveDirScan_3748c0, 3) == 0);
    CHECK(g_slot_of(0)[0] == 0 && g_slot_of(0)[1] == 3); /* SaveSlotEntrySetNoSpace */
    g_cur_save = g_save_a;
    CHECK(g_mode(McSaveCreateStep_375090, 2) == 0);
    CHECK(g_mode(McSaveStep_374110, 4) == 4); /* -3 -> "not enough free space" */
    /* unformatted card: status 7, then the game's format (mode 6) */
    CHECK(sceMcUnformat(0, 1) == 0 && mc_wait(NULL) == 0);
    CHECK(g_mode(McGetInfoStep_375640, 0) == 0 && e[2] == 0);
    CHECK(g_mode(McSaveDirScan_3748c0, 3) == 7);
    /* neither step clears the status word: 7 stays until the next GetInfo; the UI only
     * stops on 5 / 6 / 8 (normal_TransSaveNewFileTickCb_519020 case 0x67) */
    CHECK(g_mode(McFormatStep_3736b0, 6) == 7 && e[0] == 1 && e[2] == 1 && e[4] == need - 1);
    CHECK(g_mode(McSaveDirScan_3748c0, 3) == 7 && g_slot_of(0)[0] == 0 && g_slot_of(0)[1] == 3);
    CHECK(g_mode(McGetInfoStep_375640, 0) == 0);
    /* card change detection (title's McPollCardChange_372db0): pull -> 1, insert -> 2.
     * The first polls report the card found at boot (2); let them pass. */
    int got1 = 0, got2 = 0;
    for (int i = 0; i < 100; i++)
        McPollCardChange_372db0();
    mccard_eject(0);
    for (int i = 0; i < 400 && !got1; i++)
        if (McPollCardChange_372db0() == 1)
            got1 = 1;
    CHECK(mccard_insert(0, MC_SLOT_IF_EXISTS) == 0);
    for (int i = 0; i < 400 && !got2; i++)
        if (McPollCardChange_372db0() == 2)
            got2 = 1;
    CHECK(got1 && got2);
    sceMcSync(0, NULL, NULL);
}
static void t_mc_game(void)
{
    boot(1, 5000);
    g_fixtures();
    mc_boot("game", 0, MC_SLOT_AUTO, MC_SLOT_EMPTY, 1);
    run_main(m_mc_game);
    mccard_inject_fault(0, 0, 0);
    mccard_shutdown();
    /* restore the broken slot from its backup, as a player would, and the game sees save B */
    mc_boot("game", 0, MC_SLOT_IF_EXISTS, MC_SLOT_EMPTY, 0);
    char snap[1100], from[1300], hp[1024];
    CHECK(newest_snapshot(0, 0, snap, sizeof snap));
    static const char *names[] = {"icon.sys", "RG.ICO", "BASCUS-97490LV5RG_00"};
    for (int i = 0; i < 3; i++) {
        char cp[128];
        snprintf(from, sizeof from, "%s/%s", snap, names[i]);
        snprintf(cp, sizeof cp, "%s/%s", g_dir(0), names[i]);
        mccard_host_path(0, cp, hp, sizeof hp);
        copy_file(from, hp);
    }
    mccard_host_path(0, g_icon(0, 1), hp, sizeof hp);
    remove(hp);
    mccard_shutdown();
    mc_boot("game", 0, MC_SLOT_IF_EXISTS, MC_SLOT_EMPTY, 0);
    mc_dirent t[2];
    CHECK(mccard_getdir(0, g_icon(0, 0), 0, 2, t) == 1 && t[0].size == G_ICON_SYS);
    CHECK(mccard_getdir(0, g_icon(0, 1), 0, 2, t) == 0);
    CHECK(host_file_equals(0, g_data(0), g_save_b, G_DATA_SIZE));
    mccard_shutdown();
    /* a card with exactly one save's space minus 1 KB */
    boot(1, 5000);
    mc_boot("game_full", (uint32_t)(111 + 23 + 5 - 1), MC_SLOT_AUTO, MC_SLOT_EMPTY, 1);
    mcserv_config sc;
    mcserv_default_config(&sc);
    sc.format_cycles = 147456000ull / 100;
    mcserv_configure(&sc);
    run_main(m_mc_game_full);
    mcserv_configure(NULL);
    mccard_shutdown();
}
#endif

/* ---- runner ------------------------------------------------------------------------------- */
static const struct {
    const char *name;
    void (*fn)(void);
} tests[] = {
    {"pad_stable", t_pad_stable},
    {"pad_mapping", t_pad_mapping},
    {"pad_replay", t_pad_replay},
    {"pad_rumble", t_pad_rumble},
    {"pad_analog_lock", t_pad_analog_lock},
    {"npad_equiv", t_npad_equiv},
#ifdef RG_PADMC_GAME_PAD
    {"pad_game", t_pad_game},
#endif
    {"mc_files", t_mc_files},
    {"mc_errors", t_mc_errors},
    {"mc_async", t_mc_async},
    {"mc_persist", t_mc_persist},
    {"mc_persist_write", t_mc_persist_write},
    {"mc_persist_read", t_mc_persist_read},
    {"mc_card_states", t_mc_card_states},
    {"mc_save_cycle", t_mc_save_cycle},
    {"mc_full", t_mc_full},
    {"mc_exact_fit", t_mc_exact_fit},
    {"mc_corrupt", t_mc_corrupt},
    {"mc_write_fail", t_mc_write_fail},
    {"mc_backup", t_mc_backup},
    {"mc_layout", t_mc_layout},
    {"mc_crash_write", t_mc_crash_write},
    {"mc_crash_read", t_mc_crash_read},
    {"mc_pyimport", t_mc_pyimport},
#ifdef RG_PADMC_GAME_MC
    {"mc_game", t_mc_game},
#endif
};

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    {
        /* this suite's default is the oracle; RG_IOP=native runs it on the native services */
        const char *e = getenv("RG_IOP");
        g_native = e && !strcmp(e, "native");
        rg_iop_set_mode(g_native ? RG_IOP_MODE_NATIVE : RG_IOP_MODE_HLE);
    }
    g_tmp = getenv("RG_PADMC_TMP");
    if (!g_tmp)
        g_tmp = ".";
    int ran = 0;
    for (size_t i = 0; i < sizeof tests / sizeof tests[0]; i++) {
        char ctl[64];
        snprintf(ctl, sizeof ctl, "%s_control", tests[i].name);
        int want = argc < 2 || strcmp(argv[1], tests[i].name) == 0;
        int want_ctl = argc >= 2 && strcmp(argv[1], ctl) == 0;
        if (argc < 2 && (!strcmp(tests[i].name, "mc_persist_write") || !strcmp(tests[i].name, "mc_persist_read") ||
                         !strncmp(tests[i].name, "mc_crash_", 9) || !strcmp(tests[i].name, "mc_pyimport")))
            want = 0; /* the two-process pairs run only by name */
        if (!want && !want_ctl)
            continue;
        g_control = want_ctl;
        int before = g_fail;
        g_violations = 0;
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
