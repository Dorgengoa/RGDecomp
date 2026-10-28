/* SPDX-License-Identifier: CC0-1.0 */
/* Native pad service. See rg_npad.h and docs/NATIVE-IOP.md.  The controller semantics
 * follow docs/PADMC.md (the padman HLE is the oracle); written for the native path
 * without its transport (no SIF, no packet format): the readers answer from `view`, the
 * port's state as of its last VBlank steps.  Two views per port alternate by frame like
 * padman's two buffer halves, and libpad's open resets only some fields of both, so a
 * port reopened in the same session reads exactly what it read on the PS2 (stale mode
 * and actuator answers until the first step; the game itself opens each port once). */
#include "rg_npad.h"

#include <string.h>

enum { PH_CLOSED = 0, PH_FIND, PH_CTP1, PH_DISCONN, PH_STABLE };
enum { ST_DISCONN = 0, ST_FINDPAD = 1, ST_FINDCTP1 = 2, ST_EXECCMD = 5, ST_STABLE = 6 };
enum { RQ_COMPLETE = 0, RQ_FAILED = 1, RQ_BUSY = 2 };
enum { CMD_NONE = 0, CMD_MAINMODE, CMD_ACTALIGN, CMD_BUTTONINFO };

/* What the game reads (libpad's view of a port). */
typedef struct view {
    uint32_t frame;  /* the newer view has the larger frame (signed compare) */
    uint8_t state, req, ok;
    uint8_t mode_id; /* 0 unless stable */
    uint8_t mode;    /* mode table offset: 0 digital, 1 analog */
    uint8_t len;     /* bytes scePadRead copies: 32 when stable, else 0 */
    uint8_t info;    /* mode table + actuator answers present (stable) */
    uint8_t data[32];
} view;

typedef struct port {
    int open;
    uint32_t frame;
    int phase, count;
    int mode;   /* 0 digital, 1 analog */
    int press;  /* pressure mode (analog only) */
    int locked;
    uint8_t align[6];
    uint8_t direct[6];
    int cmd, cmd_left;
    int cmd_arg, cmd_arg2;
    uint8_t cmd_align[6];
    uint8_t req;
    uint8_t rum_small, rum_large;
    rg_pad_report last;
    view h[2]; /* by frame parity */
} port;

static struct {
    rg_npad_config cfg;
    port p[RG_PAD_PORTS];
    int inited;      /* rg_npad_init ran (libpad commands answer) */
    int cfg_set;
    uint64_t last_vb;
    int have_vb;
    uint32_t rumble_calls;
} G;

/* measured padman answers (docs/PADMC.md, VALIDATION.md 4) */
static const uint8_t k_act[8] = {1, 2, 0, 10, 1, 1, 1, 20}; /* act 0 / act 1: func, sub, size, current */
static const uint16_t k_mode_table[2] = {4, 7};
#define N_MODES 2
#define N_ACT 2

void rg_npad_default_config(rg_npad_config *c)
{
    memset(c, 0, sizeof *c);
    c->find_frames = 2;
    c->ctp1_frames = 2;
    c->cmd_frames = 3;
    c->default_connected[0] = 1;
}

static void ensure_cfg(void)
{
    if (!G.cfg_set)
        rg_npad_reset(NULL);
}

void rg_npad_reset(const rg_npad_config *c)
{
    memset(&G, 0, sizeof G);
    if (c)
        G.cfg = *c;
    else
        rg_npad_default_config(&G.cfg);
    if (G.cfg.find_frames < 1)
        G.cfg.find_frames = 1;
    if (G.cfg.ctp1_frames < 1)
        G.cfg.ctp1_frames = 1;
    if (G.cfg.cmd_frames < 1)
        G.cfg.cmd_frames = 1;
    rg_pad_io_reset_latched(G.cfg.default_connected);
    G.cfg_set = 1;
}

static int valid(int port, int slot) { return port >= 0 && port < RG_PAD_PORTS && slot >= 0 && slot < 4; }

int rg_npad_is_open(int port, int slot) { return valid(port, slot) && slot == 0 && G.p[port].open; }

/* ---- the controller ------------------------------------------------------------ */
static void set_rumble(int i, uint8_t small, uint8_t large)
{
    port *p = &G.p[i];
    if (p->rum_small == small && p->rum_large == large)
        return;
    p->rum_small = small;
    p->rum_large = large;
    G.rumble_calls++;
    rg_pad_io_rumble(i, small, large);
}

static void apply_rumble(int i)
{
    port *p = &G.p[i];
    uint8_t small = 0, large = 0;
    if (p->phase == PH_STABLE)
        for (int k = 0; k < 6; k++) {
            if (p->align[k] == 0)
                small = p->direct[k] ? 1 : 0;
            else if (p->align[k] == 1)
                large = p->direct[k];
        }
    set_rumble(i, small, large);
}

static int lock_kept(const port *p) { return G.cfg.keep_analog_lock && p->mode && p->locked; }

static void power_reset(port *p)
{
    if (!lock_kept(p)) {
        p->mode = G.cfg.start_analog ? 1 : 0;
        p->locked = 0;
    }
    p->press = 0;
    memset(p->align, 0xFF, sizeof p->align);
    memset(p->direct, 0, sizeof p->direct);
}

static uint8_t mode_id(const port *p) { return !p->mode ? 0x41 : p->press ? 0x79 : 0x73; }

static void finish_cmd(int i)
{
    port *p = &G.p[i];
    switch (p->cmd) {
    case CMD_MAINMODE:
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
    case CMD_ACTALIGN:
        memcpy(p->align, p->cmd_align, 6);
        apply_rumble(i);
        break;
    case CMD_BUTTONINFO:
        p->press = (p->cmd_arg != 0) && p->mode;
        break;
    default:
        break;
    }
    p->cmd = CMD_NONE;
    p->req = RQ_COMPLETE;
}

static view *newest(port *p) { return (int32_t)p->h[0].frame < (int32_t)p->h[1].frame ? &p->h[1] : &p->h[0]; }

/* the view the game reads after a step */
static void publish(port *p)
{
    view *v = &p->h[p->frame & 1u];
    memset(v, 0, sizeof *v);
    v->frame = p->frame;
    memset(v->data, 0xFF, sizeof v->data);
    v->req = p->req;
    switch (p->phase) {
    case PH_FIND: v->state = ST_FINDPAD; break;
    case PH_CTP1: v->state = ST_FINDCTP1; break;
    case PH_STABLE: v->state = ST_STABLE; break;
    default: v->state = ST_DISCONN; break;
    }
    if (p->phase != PH_STABLE)
        return;
    const rg_pad_report *r = &p->last;
    uint8_t id = mode_id(p);
    uint8_t *d = v->data;
    memset(d, 0, 32);
    d[31] = 0x5A;
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
            uint8_t x;
            if (r->has_pressure)
                x = (r->buttons & bit[i]) ? (r->pressure[i] ? r->pressure[i] : 1) : 0;
            else
                x = (r->buttons & bit[i]) ? 0xFF : 0x00;
            d[8 + i] = x;
        }
    }
    v->len = 32;
    v->mode_id = id;
    v->mode = (uint8_t)(p->mode ? 1 : 0);
    v->info = 1;
    v->ok = 1;
}

static void step(int i, uint64_t vb)
{
    port *p = &G.p[i];
    rg_pad_report r;
    rg_pad_io_report(i, vb, &r);
    p->frame++;
    switch (p->phase) {
    case PH_FIND:
        if (--p->count <= 0) {
            if (r.connected) {
                p->phase = PH_CTP1;
                p->count = G.cfg.ctp1_frames;
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
            p->req = RQ_COMPLETE;
        }
        break;
    case PH_DISCONN:
        if (r.connected) {
            p->phase = PH_FIND;
            p->count = G.cfg.find_frames;
        }
        break;
    case PH_STABLE:
        if (!r.connected) {
            p->phase = PH_DISCONN;
            if (p->cmd) {
                p->cmd = CMD_NONE;
                p->req = RQ_FAILED;
            }
            power_reset(p);
            set_rumble(i, 0, 0);
            break;
        }
        if (p->cmd && --p->cmd_left <= 0)
            finish_cmd(i);
        break;
    default:
        break;
    }
    p->last = r;
}

void rg_npad_update(uint64_t vblank)
{
    ensure_cfg();
    if (!G.have_vb) {
        G.have_vb = 1;
        G.last_vb = vblank;
        return;
    }
    if (vblank <= G.last_vb)
        return;
    uint64_t n = vblank - G.last_vb;
    uint64_t first = G.last_vb + 1;
    if (n > 600) { /* the machine has converged long before */
        first = vblank - 599;
        n = 600;
    }
    for (int i = 0; i < RG_PAD_PORTS; i++) {
        port *p = &G.p[i];
        if (!p->open)
            continue;
        for (uint64_t k = 0; k < n; k++) {
            step(i, first + k);
            if (k + 2 >= n) /* the last two steps fill both views, as padman's halves */
                publish(p);
        }
    }
    G.last_vb = vblank;
}

uint64_t rg_npad_last_vblank(void) { return G.last_vb; }
uint32_t rg_npad_rumble_calls(void) { return G.rumble_calls; }

/* ---- libpad API ------------------------------------------------------------------ */
int rg_npad_init(void)
{
    ensure_cfg();
    for (int i = 0; i < RG_PAD_PORTS; i++)
        G.p[i].open = 0;
    G.inited = 1;
    return 1;
}

int rg_npad_inited(void) { return G.inited; }

int rg_npad_end(void)
{
    if (!G.inited)
        return 0;
    for (int i = 0; i < RG_PAD_PORTS; i++) {
        if (G.p[i].open)
            set_rumble(i, 0, 0);
        G.p[i].open = 0;
        G.p[i].phase = PH_CLOSED;
    }
    return 1;
}

int rg_npad_port_open(int i, int slot)
{
    ensure_cfg();
    if (!valid(i, slot) || G.p[i].open || !G.inited || slot != 0)
        return 0;
    port *p = &G.p[i];
    view keep[2];
    memcpy(keep, p->h, sizeof keep);
    memset(p, 0, sizeof *p);
    p->open = 1;
    p->phase = PH_FIND;
    p->count = G.cfg.find_frames;
    p->req = RQ_COMPLETE;
    power_reset(p);
    rg_pad_report_neutral(&p->last);
    /* until the first step the game reads libpad's open-time view: frame 0, EXECCMD,
     * BUSY, data 0xFF, nothing to read; the other fields keep what the last session
     * left (zero for a port never opened) */
    for (int k = 0; k < 2; k++) {
        p->h[k] = keep[k];
        p->h[k].frame = 0;
        p->h[k].state = ST_EXECCMD;
        p->h[k].req = RQ_BUSY;
        p->h[k].len = 0;
        memset(p->h[k].data, 0xFF, sizeof p->h[k].data);
    }
    return 1;
}

int rg_npad_port_close(int i, int slot)
{
    if (!rg_npad_is_open(i, slot) || !G.inited)
        return 0;
    set_rumble(i, 0, 0);
    G.p[i].open = 0;
    G.p[i].phase = PH_CLOSED;
    return 1;
}

int rg_npad_read(int i, int slot, uint8_t data[32])
{
    if (!rg_npad_is_open(i, slot))
        return 0;
    const view *v = newest(&G.p[i]);
    if (data && v->len)
        memcpy(data, v->data, v->len);
    return v->len;
}

int rg_npad_state(int i, int slot)
{
    if (!rg_npad_is_open(i, slot))
        return 99; /* scePadStateClosed */
    const view *v = newest(&G.p[i]);
    if (v->state == ST_STABLE && v->req == RQ_BUSY)
        return ST_EXECCMD;
    return v->state;
}

int rg_npad_req_state(int i, int slot) { return rg_npad_is_open(i, slot) ? newest(&G.p[i])->req : 0; }

int rg_npad_set_req_state(int i, int slot, int state)
{
    if (!rg_npad_is_open(i, slot))
        return 0;
    newest(&G.p[i])->req = (uint8_t)state; /* until the next step publishes the port's own */
    return 1;
}

int rg_npad_info_mode(int i, int slot, int term, int offs)
{
    if (!rg_npad_is_open(i, slot))
        return 0;
    const view *v = newest(&G.p[i]);
    if (v->ok != 1 || v->req == RQ_BUSY)
        return 0;
    if (!v->info) /* modeConfig 0: no mode table (cannot happen with ok = 1 from padman) */
        return term == 1 ? v->mode_id >> 4 : 0;
    switch (term) {
    case 1: /* InfoModeCurID */
        return v->mode_id >> 4;
    case 2: /* InfoModeCurExID */
        return k_mode_table[v->mode];
    case 3: /* InfoModeCurExOffs */
        return v->mode;
    case 4: /* InfoModeIdTable */
        if (offs == -1)
            return N_MODES;
        if (offs >= 0 && offs < N_MODES)
            return k_mode_table[offs];
        return 0;
    default:
        return 0;
    }
}

int rg_npad_info_act(int i, int slot, int actno, int term)
{
    if (!rg_npad_is_open(i, slot))
        return 0;
    const view *v = newest(&G.p[i]);
    if (v->ok != 1 || !v->info)
        return 0;
    if (actno >= N_ACT)
        return 0;
    if (actno == -1)
        return N_ACT;
    if (actno < 0 || term < 1 || term > 4)
        return 0;
    return k_act[actno * 4 + term - 1];
}

int rg_npad_info_press_mode(int i, int slot)
{
    if (!rg_npad_is_open(i, slot))
        return 0;
    const view *v = newest(&G.p[i]);
    return v->ok == 1 && v->info;
}

/* a mode / actuator / button-info command: accepted only when stable and idle; the
 * game then reads EXECCMD / BUSY for cmd_frames VBlanks */
static int start_cmd(int i, int slot, int cmd, int a, int b, const uint8_t *align)
{
    if (!G.inited || !valid(i, slot) || slot != 0)
        return 0;
    port *p = &G.p[i];
    if (!p->open || p->phase != PH_STABLE || p->cmd)
        return 0;
    p->cmd = cmd;
    p->cmd_left = G.cfg.cmd_frames;
    p->cmd_arg = a;
    p->cmd_arg2 = b;
    if (align)
        memcpy(p->cmd_align, align, 6);
    p->req = RQ_BUSY;
    newest(p)->req = RQ_BUSY;
    return 1;
}

int rg_npad_set_main_mode(int i, int slot, int offs, int lock)
{
    if ((unsigned)offs > 1u)
        return 0;
    return start_cmd(i, slot, CMD_MAINMODE, offs, lock, NULL);
}

int rg_npad_set_act_align(int i, int slot, const uint8_t align[6])
{
    return start_cmd(i, slot, CMD_ACTALIGN, 0, 0, align);
}

int rg_npad_set_button_info(int i, int slot, int info)
{
    if (!valid(i, slot) || !G.p[i].mode)
        return 0;
    return start_cmd(i, slot, CMD_BUTTONINFO, info, 0, NULL);
}

int rg_npad_set_act_direct(int i, int slot, const uint8_t direct[6])
{
    if (!rg_npad_is_open(i, slot) || newest(&G.p[i])->ok != 1)
        return 0;
    port *p = &G.p[i];
    if (p->phase != PH_STABLE)
        return 0;
    memcpy(p->direct, direct, 6);
    apply_rumble(i);
    return 1;
}

int rg_npad_port_max(void) { return G.inited ? RG_PAD_PORTS : 0; }
int rg_npad_slot_max(int i) { return G.inited && i >= 0 && i < RG_PAD_PORTS ? 1 : 0; }
int rg_npad_mod_version(void) { return 0x0421; }

int rg_npad_port_get(int i, rg_npad_info *o)
{
    ensure_cfg();
    if (i < 0 || i >= RG_PAD_PORTS || !o)
        return -1;
    const port *p = &G.p[i];
    memset(o, 0, sizeof *o);
    o->open = p->open;
    switch (p->phase) {
    case PH_FIND: o->state = ST_FINDPAD; break;
    case PH_CTP1: o->state = ST_FINDCTP1; break;
    case PH_STABLE: o->state = ST_STABLE; break;
    default: o->state = ST_DISCONN; break;
    }
    o->req = p->req;
    o->mode_id = p->phase == PH_STABLE ? mode_id(p) : 0;
    o->locked = p->locked;
    o->frame = p->frame;
    memcpy(o->align, p->align, 6);
    o->rumble_small = p->rum_small;
    o->rumble_large = p->rum_large;
    return 0;
}
