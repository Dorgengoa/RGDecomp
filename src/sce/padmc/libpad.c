/* SPDX-License-Identifier: CC0-1.0 */
/* EE libpad over the padman HLE. See libpad.h and docs/PADMC.md.
 *
 * Retail libpad keeps a per-(port, slot) table (open flag + DMA buffer) and reads
 * every status from the newer half of the pad DMA buffer; commands go to padman
 * over SIF RPC 0x80000100 fno 1 as synchronous calls. This file does the same:
 * the readers below follow the retail asm byte for byte in their decisions, and
 * each entry point first brings the padman model up to the current VBlank so the
 * buffer holds what padman's per-frame DMA would have written by now.
 *
 * RG_IOP=native (the default, docs/NATIVE-IOP.md): every entry point answers from the
 * native pad service (src/native/input/rg_npad.c) instead: no padman server, no SIF
 * RPC, no DMA buffer.  The padman path below is the oracle (RG_IOP=hle). */
#include "libpad.h"

#include <stdint.h>
#include <string.h>

#include "libsif.h"
#include "padman.h"
#include "ps2k.h"
#include "rg_iop.h"
#include "rg_npad.h"

/* native path: bring the service up to the current VBlank first, as lp_sync does */
#if RG_IOP_ORACLE
#define NATIVE() (rg_iop_native() && (rg_npad_update(ps2k_vblank_count()), 1))
#else /* RG_NATIVE_ONLY (docs/NATIVE-ONLY.md): always native, no padman below */
#define NATIVE() (rg_npad_update(ps2k_vblank_count()), 1)
#endif

#if RG_IOP_ORACLE
#define PORTS 2
#define SLOTS 4 /* retail table: 0x70 bytes per port, 0x1C per slot */

static struct {
    sceSifClientData cd[2];
    struct {
        int open;
        uint8_t *buf;
    } s[PORTS][SLOTS];
    uint32_t req[32];
} L;

static void lp_sync(void) { padman_update(ps2k_vblank_count()); }

static int valid(int port, int slot) { return port >= 0 && port < PORTS && slot >= 0 && slot < SLOTS; }

static int is_open(int port, int slot) { return valid(port, slot) && L.s[port][slot].open; }

static void ensure_server(void)
{
    sceSifInitRpc(0);
    if (!padman_installed())
        padman_install();
}

/* synchronous padman command; returns the SIF call result (< 0 = failed) */
static int lp_call(uint32_t cmd, int port, int slot, uint32_t a, uint32_t b, const unsigned char *align)
{
    if (!L.cd[0].serve)
        return -1;
    lp_sync();
    memset(L.req, 0, sizeof L.req);
    L.req[0] = cmd;
    L.req[1] = (uint32_t)port;
    L.req[2] = (uint32_t)slot;
    L.req[3] = a;
    L.req[4] = b;
    if (align)
        memcpy((uint8_t *)L.req + 0x0C, align, 6);
    return sceSifCallRpc(&L.cd[0], 1, 0, L.req, 0x80, L.req, 0x80, NULL, NULL);
}
#endif

unsigned char *scePadGetDmaStr(int port, int slot, void *copy)
{
    RG_IOP_API("scePadGetDmaStr");
    if (rg_iop_native()) {
        (void)port;
        (void)slot;
        (void)copy;
        return NULL; /* no DMA buffer exists natively (the game never calls it) */
    }
#if RG_IOP_ORACLE
    if (!valid(port, slot) || !L.s[port][slot].buf)
        return NULL;
    lp_sync();
    uint8_t *h = padman_newest_half(L.s[port][slot].buf);
    if (copy)
        memcpy(copy, h, PAD_HALF);
    return h;
#endif
}

int scePadGetModVersion(void)
{
    RG_IOP_API("scePadGetModVersion");
    if (NATIVE())
        return rg_npad_inited() ? rg_npad_mod_version() : 0;
#if RG_IOP_ORACLE
    if (lp_call(PADMAN_CMD_GETMODVERSION, 0, 0, 0, 0, NULL) < 0)
        return 0;
    return (int)L.req[3];
#endif
}

int scePadInit(int mode)
{
    RG_IOP_API("scePadInit");
    if (NATIVE()) {
        (void)mode;
        return rg_npad_init();
    }
#if RG_IOP_ORACLE
    (void)mode;
    ensure_server();
    sceSifBindRpc(&L.cd[0], PADMAN_SID, 0);
    if (!L.cd[0].serve)
        return 0; /* retail spins until bound; the HLE server is always there */
    sceSifBindRpc(&L.cd[1], PADMAN_SID_EXT, 0);
    int v = scePadGetModVersion();
    if ((v >> 8) != 4)
        return 0;
    memset(L.s, 0, sizeof L.s);
    if (lp_call(PADMAN_CMD_INIT, 0, 0, 0, 0, NULL) < 0)
        return 0;
    return (int)L.req[3];
#endif
}

int scePadEnd(void)
{
    RG_IOP_API("scePadEnd");
    if (NATIVE())
        return rg_npad_end();
#if RG_IOP_ORACLE
    if (lp_call(PADMAN_CMD_END, 0, 0, 0, 0, NULL) < 0)
        return 0;
    memset(L.s, 0, sizeof L.s);
    return (int)L.req[5];
#endif
}

int scePadEnd_12b208(void) { return scePadEnd(); }

int scePadPortOpen(int port, int slot, void *addr)
{
    RG_IOP_API("scePadPortOpen");
    if (NATIVE()) {
        /* the buffer is libpad's DMA area on the PS2: checked as retail, never written */
        if (((uintptr_t)addr & 0x3F) != 0 || !addr)
            return 0;
        return rg_npad_port_open(port, slot);
    }
#if RG_IOP_ORACLE
    if (((uintptr_t)addr & 0x3F) != 0 || !addr)
        return 0;
    if (!valid(port, slot) || L.s[port][slot].open)
        return 0;
    /* retail: both halves -> frame 0, EXECCMD/BUSY, not ready, data 0xFF, length 0 */
    uint8_t *b = (uint8_t *)addr;
    for (int h = 0; h < 2; h++) {
        uint8_t *p = b + h * PAD_HALF;
        memset(p + PAD_OFS_FRAME, 0, 4);
        p[PAD_OFS_STATE] = PAD_STATE_EXECCMD;
        p[PAD_OFS_REQSTATE] = PAD_RSTAT_BUSY;
        p[PAD_OFS_READY] = 0;
        memset(p + PAD_OFS_DATA, 0xFF, 32);
        memset(p + PAD_OFS_LENGTH, 0, 4);
    }
    if (lp_call(PADMAN_CMD_OPEN, port, slot, 0, (uint32_t)(uintptr_t)addr, NULL) < 0)
        return 0;
    int r = (int)L.req[3];
    if (r == 1) {
        L.s[port][slot].open = 1;
        L.s[port][slot].buf = b;
    }
    return r;
#endif
}

int scePadPortClose(int port, int slot)
{
    RG_IOP_API("scePadPortClose");
    if (NATIVE())
        return rg_npad_port_close(port, slot);
#if RG_IOP_ORACLE
    if (!is_open(port, slot))
        return 0;
    if (lp_call(PADMAN_CMD_CLOSE, port, slot, 0, 0, NULL) < 0)
        return 0;
    L.s[port][slot].open = 0;
    L.s[port][slot].buf = NULL;
    return (int)L.req[5];
#endif
}

static scePadHleReadHook g_read_hook;
static void *g_read_hook_user;

void scePadHleSetReadHook(scePadHleReadHook fn, void *user)
{
    g_read_hook = fn;
    g_read_hook_user = user;
}

int scePadRead(int port, int slot, unsigned char *rdata)
{
    RG_IOP_API("scePadRead");
    if (NATIVE()) {
        uint8_t d[32];
        memset(d, 0xFF, sizeof d); /* what the hook sees before the pad is stable */
        int n = rg_npad_read(port, slot, d);
        if (rdata && n)
            memcpy(rdata, d, (size_t)n);
        if (g_read_hook && rg_npad_is_open(port, slot))
            g_read_hook(g_read_hook_user, port, slot, d, n);
        return n;
    }
#if RG_IOP_ORACLE
    if (!is_open(port, slot))
        return 0;
    uint8_t *h = scePadGetDmaStr(port, slot, NULL);
    /* retail copies +0x60 bytes, which padman sets to 0x20 when STABLE (VALIDATION.md 4);
     * the clamp only guards the host against a corrupt length */
    uint32_t len;
    memcpy(&len, h + PAD_OFS_LENGTH, 4);
    if (len > 32)
        len = 32;
    if (rdata && len)
        memcpy(rdata, h + PAD_OFS_DATA, len);
    if (g_read_hook)
        g_read_hook(g_read_hook_user, port, slot, h + PAD_OFS_DATA, (int)len);
    return (int)len;
#endif
}

int scePadGetState(int port, int slot)
{
    RG_IOP_API("scePadGetState");
    if (NATIVE())
        return rg_npad_state(port, slot);
#if RG_IOP_ORACLE
    if (!is_open(port, slot))
        return scePadStateClosed;
    const uint8_t *h = scePadGetDmaStr(port, slot, NULL);
    if (h[PAD_OFS_STATE] == PAD_STATE_STABLE && h[PAD_OFS_REQSTATE] == PAD_RSTAT_BUSY)
        return PAD_STATE_EXECCMD;
    return h[PAD_OFS_STATE];
#endif
}

int scePadGetReqState(int port, int slot)
{
    RG_IOP_API("scePadGetReqState");
    if (NATIVE())
        return rg_npad_req_state(port, slot);
#if RG_IOP_ORACLE
    if (!is_open(port, slot))
        return 0;
    return scePadGetDmaStr(port, slot, NULL)[PAD_OFS_REQSTATE];
#endif
}

int scePadSetReqState(int port, int slot, int state)
{
    RG_IOP_API("scePadSetReqState");
    if (NATIVE())
        return rg_npad_set_req_state(port, slot, state);
#if RG_IOP_ORACLE
    if (!is_open(port, slot))
        return 0;
    scePadGetDmaStr(port, slot, NULL)[PAD_OFS_REQSTATE] = (uint8_t)state;
    return 1;
#endif
}

#if RG_IOP_ORACLE
static int mode_table(const uint8_t *h, int i)
{
    uint16_t v;
    if (PAD_OFS_MODETABLE + 2 * i + 2 > PAD_HALF)
        return 0;
    memcpy(&v, h + PAD_OFS_MODETABLE + 2 * i, 2);
    return v;
}
#endif

int scePadInfoMode(int port, int slot, int term, int offs)
{
    RG_IOP_API("scePadInfoMode");
    if (NATIVE())
        return rg_npad_info_mode(port, slot, term, offs);
#if RG_IOP_ORACLE
    if (!is_open(port, slot))
        return 0;
    const uint8_t *h = scePadGetDmaStr(port, slot, NULL);
    if (h[PAD_OFS_OK] != 1 || h[PAD_OFS_REQSTATE] == PAD_RSTAT_BUSY)
        return 0;
    /* byte sources as retail 0x12BCA0 (VALIDATION.md 4): CURID = +0x65 >> 4 (0 for
     * 0xF3); CUREXID = u16 at +0x50 + 2 x (+0x69); CUREXOFFS = +0x69; TABLE -1 =
     * +0x68, i < +0x68 -> u16 at +0x50 + 2i; the last three are 0 when modeConfig
     * (+0x64) = 1.  Retail does not bound the index to the half (it reads its stack
     * copy); here an index past the 0x80-byte half reads 0. */
    switch (term) {
    case InfoModeCurID:
        return h[PAD_OFS_MODECURID] == 0xF3 ? 0 : h[PAD_OFS_MODECURID] >> 4;
    case InfoModeCurExID:
        if (h[PAD_OFS_MODECONF] == 1)
            return 0;
        return mode_table(h, h[PAD_OFS_MODEOFFS]);
    case InfoModeCurExOffs:
        return h[PAD_OFS_MODECONF] == 1 ? 0 : h[PAD_OFS_MODEOFFS];
    case InfoModeIdTable:
        if (h[PAD_OFS_MODECONF] == 1)
            return 0;
        if (offs == -1)
            return h[PAD_OFS_NMODES];
        if (offs >= 0 && offs < h[PAD_OFS_NMODES])
            return mode_table(h, offs);
        return 0;
    default:
        return 0;
    }
#endif
}

int scePadInfoAct(int port, int slot, int actno, int term)
{
    RG_IOP_API("scePadInfoAct");
    if (NATIVE())
        return rg_npad_info_act(port, slot, actno, term);
#if RG_IOP_ORACLE
    if (!is_open(port, slot))
        return 0;
    const uint8_t *h = scePadGetDmaStr(port, slot, NULL);
    if (h[PAD_OFS_OK] != 1 || h[PAD_OFS_MODECONF] < 2)
        return 0;
    if (actno >= h[PAD_OFS_NACT])
        return 0;
    if (actno == -1)
        return h[PAD_OFS_NACT];
    if (actno < 0 || actno > 7 || term < 1 || term > 4)
        return 0;
    return h[PAD_OFS_ACTDATA + actno * 4 + (term - 1)];
#endif
}

#if RG_IOP_ORACLE
static int lp_mode_cmd(uint32_t cmd, int port, int slot, uint32_t a, uint32_t b, const unsigned char *align)
{
    if (lp_call(cmd, port, slot, a, b, align) < 0)
        return 0;
    int r = (int)L.req[5];
    if (r == 1)
        scePadSetReqState(port, slot, PAD_RSTAT_BUSY);
    return r;
}
#endif

int scePadSetMainMode(int port, int slot, int offs, int lock)
{
    RG_IOP_API("scePadSetMainMode");
    if (NATIVE())
        return rg_npad_set_main_mode(port, slot, offs, lock);
#if RG_IOP_ORACLE
    return lp_mode_cmd(PADMAN_CMD_SETMAINMODE, port, slot, (uint32_t)offs, (uint32_t)lock, NULL);
#endif
}

int scePadSetActAlign(int port, int slot, const unsigned char *data)
{
    RG_IOP_API("scePadSetActAlign");
    if (NATIVE()) {
        uint8_t a[6];
        memcpy(a, data, 6);
        return rg_npad_set_act_align(port, slot, a);
    }
#if RG_IOP_ORACLE
    unsigned char a[6];
    memcpy(a, data, 6);
    return lp_mode_cmd(PADMAN_CMD_SETACTALIGN, port, slot, 0, 0, a);
#endif
}

int scePadSetButtonInfo(int port, int slot, int info)
{
    RG_IOP_API("scePadSetButtonInfo");
    if (NATIVE())
        return rg_npad_set_button_info(port, slot, info);
#if RG_IOP_ORACLE
    return lp_mode_cmd(PADMAN_CMD_SETBUTTONINFO, port, slot, (uint32_t)info, 0, NULL);
#endif
}

static int lp_open(int port, int slot) { return RG_IOP_PICK(rg_npad_is_open(port, slot), is_open(port, slot)); }


int scePadEnterPressMode(int port, int slot)
{
    return lp_open(port, slot) ? scePadSetButtonInfo(port, slot, 0xFFF) : 0;
}

int scePadExitPressMode(int port, int slot)
{
    return lp_open(port, slot) ? scePadSetButtonInfo(port, slot, 0) : 0;
}

int scePadInfoPressMode(int port, int slot)
{
    RG_IOP_API("scePadInfoPressMode");
    if (NATIVE())
        return rg_npad_info_press_mode(port, slot);
#if RG_IOP_ORACLE
    if (!is_open(port, slot))
        return 0;
    const uint8_t *h = scePadGetDmaStr(port, slot, NULL);
    return h[PAD_OFS_OK] == 1 && h[PAD_OFS_MODECONF] >= 2;
#endif
}

int scePadSetActDirect(int port, int slot, const unsigned char *data)
{
    RG_IOP_API("scePadSetActDirect");
    if (NATIVE()) {
        uint8_t d[6];
        memcpy(d, data, 6);
        return rg_npad_set_act_direct(port, slot, d);
    }
#if RG_IOP_ORACLE
    if (!is_open(port, slot))
        return 0;
    const uint8_t *h = scePadGetDmaStr(port, slot, NULL);
    if (h[PAD_OFS_OK] != 1)
        return 0;
    uint8_t d[6];
    memcpy(d, data, 6);
    return padman_act_direct(port, slot, d) == 1;
#endif
}

int scePadGetPortMax(void)
{
    RG_IOP_API("scePadGetPortMax");
    if (NATIVE())
        return rg_npad_port_max();
#if RG_IOP_ORACLE
    if (lp_call(PADMAN_CMD_GETPORTMAX, 0, 0, 0, 0, NULL) < 0)
        return 0;
    return (int)L.req[3];
#endif
}

int scePadGetSlotMax(int port)
{
    RG_IOP_API("scePadGetSlotMax");
    if (NATIVE())
        return rg_npad_slot_max(port);
#if RG_IOP_ORACLE
    if (lp_call(PADMAN_CMD_GETSLOTMAX, port, 0, 0, 0, NULL) < 0)
        return 0;
    return (int)L.req[3];
#endif
}
