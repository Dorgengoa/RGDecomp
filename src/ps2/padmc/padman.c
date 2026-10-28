/* SPDX-License-Identifier: CC0-1.0 */
/* padman HLE: DualShock 2 model, DMA buffer writer and the 0x80000100/101 SIF
 * servers. See padman.h and docs/PADMC.md. Written from the game's own libpad
 * call sites and the retail libpad readers (game/src/main/sdk/scePad*.c asm);
 * no GPL code. */
#include "padman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sif.h"
#include "rg_iop.h" /* census counters (docs/NATIVE-IOP.md) */

enum { PH_CLOSED = 0, PH_FIND, PH_CTP1, PH_DISCONN, PH_STABLE };

typedef struct pad_port {
    int open;
    uint8_t *buf;     /* EE DMA buffer (host pointer), 256 bytes */
    uint32_t frame;   /* frames written since open */
    int phase, count;
    int mode;         /* 0 digital, 1 analog */
    int press;        /* pressure mode (analog only) */
    int locked;
    uint8_t align[6];
    uint8_t direct[6];
    int cmd, cmd_left;
    uint32_t cmd_arg, cmd_arg2;
    uint8_t cmd_align[6];
    uint8_t req;
    uint8_t rum_small, rum_large;
    uint32_t commands;
    rg_pad_report last;
} pad_port;

/* The input source, latched reports and rumble hook are the shared pad I/O
 * (src/native/input/rg_pad_io.c): the native pad service asks the same source. */
static struct {
    padman_config cfg;
    pad_port port[RG_PAD_PORTS];
    uint32_t rumble_calls;
    uint64_t last_vb;
    int have_vb;
    int inited;
    uint32_t reply[32];
} P;

void padman_default_config(padman_config *c)
{
    memset(c, 0, sizeof *c);
    c->find_frames = 2;
    c->ctp1_frames = 2;
    c->cmd_frames = 3;
    c->start_analog = 0;
    c->default_connected[0] = 1;
    c->default_connected[1] = 0;
}

static void ensure_init(void)
{
    if (!P.inited)
        padman_reset(NULL);
}

void padman_reset(const padman_config *c)
{
    memset(&P, 0, sizeof P);
    if (c)
        P.cfg = *c;
    else
        padman_default_config(&P.cfg);
    if (P.cfg.find_frames < 1)
        P.cfg.find_frames = 1;
    if (P.cfg.ctp1_frames < 1)
        P.cfg.ctp1_frames = 1;
    if (P.cfg.cmd_frames < 1)
        P.cfg.cmd_frames = 1;
    rg_pad_io_reset_latched(P.cfg.default_connected);
    P.inited = 1;
}

const padman_config *padman_get_config(void)
{
    ensure_init();
    return &P.cfg;
}

uint32_t padman_rumble_calls(void) { return P.rumble_calls; }
uint64_t padman_last_vblank(void) { return P.last_vb; }

/* ---- the controller ------------------------------------------------------------ */
static void get_report(int port, uint64_t vb, rg_pad_report *r) { rg_pad_io_report(port, vb, r); }

static void set_rumble(int port, uint8_t small, uint8_t large)
{
    pad_port *p = &P.port[port];
    if (p->rum_small == small && p->rum_large == large)
        return;
    p->rum_small = small;
    p->rum_large = large;
    P.rumble_calls++;
    rg_pad_io_rumble(port, small, large);
}

static void apply_rumble(int port)
{
    pad_port *p = &P.port[port];
    uint8_t small = 0, large = 0;
    if (p->phase == PH_STABLE) {
        for (int i = 0; i < 6; i++) {
            if (p->align[i] == 0)
                small = p->direct[i] ? 1 : 0;
            else if (p->align[i] == 1)
                large = p->direct[i];
        }
    }
    set_rumble(port, small, large);
}

/* A DS2 that loses power (unplugged) comes back digital, unlocked, motors unmapped.
 * With keep_analog_lock a port the game had locked stays analog + locked. */
static int lock_kept(const pad_port *p)
{
    return P.cfg.keep_analog_lock && p->mode && p->locked;
}

static void power_reset(pad_port *p)
{
    if (!lock_kept(p)) {
        p->mode = P.cfg.start_analog ? 1 : 0;
        p->locked = 0;
    }
    p->press = 0;
    memset(p->align, 0xFF, sizeof p->align);
    memset(p->direct, 0, sizeof p->direct);
}

static uint8_t mode_id(const pad_port *p)
{
    if (!p->mode)
        return 0x41;
    return p->press ? 0x79 : 0x73;
}

static void finish_cmd(int port)
{
    pad_port *p = &P.port[port];
    switch (p->cmd) {
    case PADMAN_CMD_SETMAINMODE:
        if (lock_kept(p) && !p->cmd_arg)
            break; /* keep_analog_lock: stays 0x73, locked */
        p->mode = p->cmd_arg ? 1 : 0;
        if (!p->mode)
            p->press = 0;
        if (p->cmd_arg2 == 3)
            p->locked = 1;
        else if (p->cmd_arg2 == 2)
            p->locked = 0;
        break;
    case PADMAN_CMD_SETACTALIGN:
        memcpy(p->align, p->cmd_align, 6);
        apply_rumble(port);
        break;
    case PADMAN_CMD_SETBUTTONINFO:
        p->press = (p->cmd_arg != 0) && p->mode;
        break;
    default:
        break;
    }
    p->cmd = 0;
    p->req = PAD_RSTAT_COMPLETE;
}

static void step(int port, uint64_t vb)
{
    pad_port *p = &P.port[port];
    rg_pad_report r;
    get_report(port, vb, &r);
    p->frame++;
    switch (p->phase) {
    case PH_FIND:
        if (--p->count <= 0) {
            if (r.connected) {
                p->phase = PH_CTP1;
                p->count = P.cfg.ctp1_frames;
            } else {
                p->phase = PH_DISCONN;
            }
        }
        break;
    case PH_CTP1:
        if (!r.connected) {
            p->phase = PH_DISCONN;
            break;
        }
        if (--p->count <= 0) {
            p->phase = PH_STABLE;
            p->req = PAD_RSTAT_COMPLETE;
        }
        break;
    case PH_DISCONN:
        if (r.connected) {
            p->phase = PH_FIND;
            p->count = P.cfg.find_frames;
        }
        break;
    case PH_STABLE:
        if (!r.connected) {
            p->phase = PH_DISCONN;
            if (p->cmd) {
                p->cmd = 0;
                p->req = PAD_RSTAT_FAILED;
            }
            power_reset(p);
            set_rumble(port, 0, 0);
            break;
        }
        if (p->cmd && --p->cmd_left <= 0)
            finish_cmd(port);
        break;
    default:
        break;
    }
    p->last = r;
}

static void build_half(const pad_port *p, uint8_t img[PAD_HALF])
{
    memset(img, 0, PAD_HALF);
    memset(img + PAD_OFS_DATA, 0xFF, 32);
    uint32_t frame = p->frame;
    memcpy(img + PAD_OFS_FRAME, &frame, 4);
    img[PAD_OFS_REQSTATE] = p->req;
    switch (p->phase) {
    case PH_FIND: img[PAD_OFS_STATE] = PAD_STATE_FINDPAD; break;
    case PH_CTP1: img[PAD_OFS_STATE] = PAD_STATE_FINDCTP1; break;
    case PH_DISCONN: img[PAD_OFS_STATE] = PAD_STATE_DISCONN; break;
    case PH_STABLE: img[PAD_OFS_STATE] = PAD_STATE_STABLE; break;
    default: img[PAD_OFS_STATE] = PAD_STATE_DISCONN; break;
    }
    if (p->phase != PH_STABLE)
        return;
    const rg_pad_report *r = &p->last;
    uint8_t id = mode_id(p);
    uint8_t *d = img + PAD_OFS_DATA;
    /* VALIDATION.md 4 (real padman, mode 0x73): 00 73 btn btn rx ry lx ly, then
     * zeros, byte 31 = 0x5A.  The same tail is assumed for 0x41 / 0x79. */
    memset(d, 0, 32);
    d[31] = 0x5A;
    d[0] = 0x00;
    d[1] = id;
    d[2] = (uint8_t)~(r->buttons >> 8);
    d[3] = (uint8_t)~(r->buttons & 0xFF);
    if (p->mode) {
        d[4] = r->rx;
        d[5] = r->ry;
        d[6] = r->lx;
        d[7] = r->ly;
    }
    if (id == 0x79) {
        static const uint16_t bit[RG_PAD_P_COUNT] = {
            RG_PAD_RIGHT, RG_PAD_LEFT, RG_PAD_UP, RG_PAD_DOWN, RG_PAD_TRIANGLE, RG_PAD_CIRCLE,
            RG_PAD_CROSS, RG_PAD_SQUARE, RG_PAD_L1, RG_PAD_R1, RG_PAD_L2, RG_PAD_R2};
        for (int i = 0; i < RG_PAD_P_COUNT; i++) {
            uint8_t v;
            if (r->has_pressure)
                v = (r->buttons & bit[i]) ? (r->pressure[i] ? r->pressure[i] : 1) : 0;
            else
                v = (r->buttons & bit[i]) ? 0xFF : 0x00;
            d[8 + i] = v;
        }
    }
    /* VALIDATION.md 4: padman reports length 0x20 (not 2 + 2 x (id & 0xF));
     * libpad's scePadRead copies and returns it (1,145 of 1,145 reads in 0x73) */
    uint32_t len = PAD_READ_LENGTH;
    memcpy(img + PAD_OFS_LENGTH, &len, 4);
    memcpy(img + PAD_OFS_ACTALIGN, p->align, 6);
    /* actData as the real padman fills it (VALIDATION.md 4): act 0 = 01 02 00 0a,
     * act 1 = 01 01 01 14 (func, sub, size, current) */
    static const uint8_t act[8] = {1, 2, 0, 10, 1, 1, 1, 20};
    memcpy(img + PAD_OFS_ACTDATA, act, sizeof act);
    static const uint8_t comb[4] = {2, 0, 1, 0}; /* +0x40: observed, one combination */
    memcpy(img + PAD_OFS_ACTCOMB, comb, sizeof comb);
    static const uint8_t x6c[4] = {0, 1, 3, 0}; /* +0x6C: observed, meaning unknown */
    memcpy(img + PAD_OFS_UNK6C, x6c, sizeof x6c);
    uint16_t table[4] = {4, 7, 0, 0};
    memcpy(img + PAD_OFS_MODETABLE, table, sizeof table);
    img[PAD_OFS_MODECONF] = 2;
    img[PAD_OFS_MODECURID] = id;
    img[PAD_OFS_MODEL] = 3;
    img[PAD_OFS_READY] = 1;
    img[PAD_OFS_NMODES] = 2;
    img[PAD_OFS_MODEOFFS] = (uint8_t)(p->mode ? 1 : 0);
    img[PAD_OFS_NACT] = 2;
    img[PAD_OFS_NCOMB] = 1; /* VALIDATION.md 4: numActComb = 1 */
    img[PAD_OFS_OK] = 1;
}

static void write_half(pad_port *p)
{
    if (!p->buf)
        return;
    uint8_t img[PAD_HALF];
    build_half(p, img);
    sif0_write(p->buf + (p->frame & 1u) * PAD_HALF, img, PAD_HALF);
}

uint8_t *padman_newest_half(uint8_t *dma)
{
    int32_t f0, f1;
    memcpy(&f0, dma + PAD_OFS_FRAME, 4);
    memcpy(&f1, dma + PAD_HALF + PAD_OFS_FRAME, 4);
    return dma + (f0 < f1 ? PAD_HALF : 0);
}

void padman_update(uint64_t vblank)
{
    RG_IOP_HLE("padman_update");
    ensure_init();
    if (!P.have_vb) {
        P.have_vb = 1;
        P.last_vb = vblank;
        return;
    }
    if (vblank <= P.last_vb)
        return;
    uint64_t n = vblank - P.last_vb;
    uint64_t first = P.last_vb + 1;
    if (n > 600) {
        first = vblank - 599;
        n = 600;
    }
    for (int port = 0; port < RG_PAD_PORTS; port++) {
        pad_port *p = &P.port[port];
        if (!p->open)
            continue;
        for (uint64_t i = 0; i < n; i++) {
            step(port, first + i);
            if (i + 2 >= n)
                write_half(p);
        }
    }
    P.last_vb = vblank;
}

int padman_act_direct(int port, int slot, const uint8_t direct[6])
{
    RG_IOP_HLE("padman_act_direct");
    ensure_init();
    if (port < 0 || port >= RG_PAD_PORTS || slot != 0)
        return 0;
    pad_port *p = &P.port[port];
    if (!p->open || p->phase != PH_STABLE)
        return 0;
    memcpy(p->direct, direct, 6);
    apply_rumble(port);
    return 1;
}

int padman_port_get(int port, padman_port_info *o)
{
    ensure_init();
    if (port < 0 || port >= RG_PAD_PORTS || !o)
        return -1;
    const pad_port *p = &P.port[port];
    memset(o, 0, sizeof *o);
    o->open = p->open;
    switch (p->phase) {
    case PH_FIND: o->state = PAD_STATE_FINDPAD; break;
    case PH_CTP1: o->state = PAD_STATE_FINDCTP1; break;
    case PH_STABLE: o->state = PAD_STATE_STABLE; break;
    default: o->state = PAD_STATE_DISCONN; break;
    }
    o->req = p->req;
    o->mode_id = p->phase == PH_STABLE ? mode_id(p) : 0;
    o->locked = p->locked;
    o->frame = p->frame;
    memcpy(o->align, p->align, 6);
    o->rumble_small = p->rum_small;
    o->rumble_large = p->rum_large;
    o->commands = p->commands;
    return 0;
}

/* ---- SIF servers ------------------------------------------------------------------- */
static uint32_t rd32(const uint8_t *b, int i)
{
    uint32_t v;
    memcpy(&v, b + i * 4, 4);
    return v;
}

static int start_cmd(pad_port *p, int cmd, uint32_t a, uint32_t b, const uint8_t *align)
{
    if (!p->open || p->phase != PH_STABLE || p->cmd)
        return 0;
    p->cmd = cmd;
    p->cmd_left = P.cfg.cmd_frames;
    p->cmd_arg = a;
    p->cmd_arg2 = b;
    if (align)
        memcpy(p->cmd_align, align, 6);
    p->req = PAD_RSTAT_BUSY;
    return 1;
}

static void *srv_padman(sif_rpc_ctx *c, void *user)
{
    (void)user;
    ensure_init();
    uint8_t req[128];
    memset(req, 0, sizeof req);
    memcpy(req, c->data, c->size < sizeof req ? c->size : sizeof req);
    memcpy(P.reply, req, sizeof req);
    uint32_t cmd = rd32(req, 0), port = rd32(req, 1), slot = rd32(req, 2);
    uint32_t a = rd32(req, 3), b = rd32(req, 4);
    pad_port *p = port < RG_PAD_PORTS ? &P.port[port] : NULL;
    if (p)
        p->commands++;
    uint32_t w3 = 0, w5 = 0;
    switch (cmd) {
    case PADMAN_CMD_INIT:
        w3 = 1;
        break;
    case PADMAN_CMD_GETMODVERSION:
        w3 = PADMAN_MOD_VERSION;
        break;
    case PADMAN_CMD_GETPORTMAX:
        w3 = RG_PAD_PORTS;
        break;
    case PADMAN_CMD_GETSLOTMAX:
        w3 = p ? 1 : 0;
        break;
    case PADMAN_CMD_OPEN:
        if (p && slot == 0 && b != 0) {
            uint32_t keep = p->commands;
            memset(p, 0, sizeof *p);
            p->commands = keep;
            p->open = 1;
            p->buf = (uint8_t *)(uintptr_t)b;
            p->phase = PH_FIND;
            p->count = P.cfg.find_frames;
            p->req = PAD_RSTAT_COMPLETE;
            power_reset(p);
            rg_pad_report_neutral(&p->last);
            w3 = 1;
        }
        break;
    case PADMAN_CMD_CLOSE:
        if (p && slot == 0 && p->open) {
            set_rumble((int)port, 0, 0);
            p->open = 0;
            p->buf = NULL;
            p->phase = PH_CLOSED;
            w5 = 1;
        }
        break;
    case PADMAN_CMD_END:
        for (int i = 0; i < RG_PAD_PORTS; i++) {
            if (P.port[i].open)
                set_rumble(i, 0, 0);
            P.port[i].open = 0;
            P.port[i].buf = NULL;
            P.port[i].phase = PH_CLOSED;
        }
        w5 = 1;
        break;
    case PADMAN_CMD_SETMAINMODE:
        if (p && slot == 0 && a <= 1)
            w5 = (uint32_t)start_cmd(p, (int)cmd, a, b, NULL);
        break;
    case PADMAN_CMD_SETACTALIGN:
        if (p && slot == 0)
            w5 = (uint32_t)start_cmd(p, (int)cmd, 0, 0, req + 0x0C);
        break;
    case PADMAN_CMD_SETBUTTONINFO:
        if (p && slot == 0 && p->mode)
            w5 = (uint32_t)start_cmd(p, (int)cmd, a, 0, NULL);
        break;
    case PADMAN_CMD_SETVREF:
        w5 = (p && p->open) ? 1u : 0u;
        break;
    default:
        c->unknown = 1;
        break;
    }
    P.reply[3] = w3;
    P.reply[5] = w5;
    return P.reply;
}

/* 0x80000101: retail libpad sends SetActDirect data here by SIF DMA. The port's
 * libpad calls padman_act_direct directly; this server answers anything else. */
static void *srv_padman_ext(sif_rpc_ctx *c, void *user)
{
    (void)user;
    c->unknown = 1;
    memset(P.reply, 0, sizeof P.reply);
    return P.reply;
}

int padman_install(void)
{
    RG_IOP_HLE("padman_install");
    ensure_init();
    int r = sif_server_register(PADMAN_SID, "padman", 0x80, srv_padman, NULL);
    r |= sif_server_register(PADMAN_SID_EXT, "padman-ext", 0x80, srv_padman_ext, NULL);
    return r;
}

int padman_installed(void)
{
    const sif_server_info *a = sif_server_find(PADMAN_SID);
    const sif_server_info *b = sif_server_find(PADMAN_SID_EXT);
    return a && b && a->fn == srv_padman && b->fn == srv_padman_ext;
}
