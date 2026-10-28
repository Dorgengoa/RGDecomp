/* SPDX-License-Identifier: CC0-1.0 */
/* Native pad service (docs/NATIVE-IOP.md): the DualShock 2 the game sees through its
 * libpad calls, answered directly from host input.  No padman server, no SIF RPC, no
 * pad DMA buffer: libpad (src/sce/padmc/libpad.c, RG_IOP=native) calls these
 * functions, and each reader answers from the port's state as of the last VBlank step.
 *
 * Game-visible semantics are the padman HLE's (docs/PADMC.md, which the oracle keeps):
 * per-VBlank connection states FINDPAD -> FINDCTP1 -> STABLE (DISCONN without a
 * controller), digital power-up, SetMainMode / SetActAlign / SetButtonInfo BUSY for
 * cmd_frames VBlanks, keep_analog_lock, the 32-byte read (00 id btn btn rx ry lx ly,
 * pressures in 0x79, byte 31 = 0x5A), the measured mode table / actuator answers.
 * tests/padmc `npad_equiv` runs both services side by side and compares every answer.
 *
 * Time is the VBlank count: rg_npad_update(vblank) steps every open port once per
 * VBlank, asking the shared input source (rg_pad_io.h) for (port, vblank); libpad calls
 * it on entry to every function, the runtime from its VBlank observer.  Kernel-agnostic. */
#ifndef RG_NATIVE_NPAD_H
#define RG_NATIVE_NPAD_H
#include <stdint.h>

#include "rg_pad_io.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rg_npad_config {
    int find_frames;      /* VBlanks in FINDPAD after open / reconnect (default 2) */
    int ctp1_frames;      /* VBlanks in FINDCTP1 (default 2) */
    int cmd_frames;       /* VBlanks a mode/actuator/button-info command stays BUSY (default 3) */
    int start_analog;     /* 0 (default): a DS2 powers up digital (0x41) */
    int keep_analog_lock; /* 1: once locked analog, stays 0x73 across unplug / digital requests */
    int default_connected[RG_PAD_PORTS]; /* latched report before any push: {1, 0} */
} rg_npad_config;

void rg_npad_default_config(rg_npad_config *c);
/* Ports closed, config set (NULL = defaults); the latched reports are reset too. */
void rg_npad_reset(const rg_npad_config *c);
void rg_npad_update(uint64_t vblank);

/* libpad API, retail return conventions (libpad.h).  `port` 0..1, `slot` 0..3 (only
 * slot 0 has a controller). */
int rg_npad_init(void);              /* 1 */
int rg_npad_end(void);               /* 1, every port closed, motors off */
int rg_npad_inited(void);
int rg_npad_port_open(int port, int slot);  /* 1 opened, 0 bad port/slot or already open */
int rg_npad_port_close(int port, int slot); /* 1, 0 if not open */
int rg_npad_is_open(int port, int slot);
int rg_npad_read(int port, int slot, uint8_t data[32]); /* bytes (32 when stable, else 0) */
int rg_npad_state(int port, int slot);      /* scePadGetState (99 closed) */
int rg_npad_req_state(int port, int slot);
int rg_npad_set_req_state(int port, int slot, int state);
int rg_npad_info_mode(int port, int slot, int term, int offs);
int rg_npad_info_act(int port, int slot, int actno, int term);
int rg_npad_info_press_mode(int port, int slot);
int rg_npad_set_main_mode(int port, int slot, int offs, int lock);
int rg_npad_set_act_align(int port, int slot, const uint8_t align[6]);
int rg_npad_set_button_info(int port, int slot, int info);
int rg_npad_set_act_direct(int port, int slot, const uint8_t direct[6]);
int rg_npad_port_max(void);          /* 2 */
int rg_npad_slot_max(int port);      /* 1 for ports 0..1 */
int rg_npad_mod_version(void);       /* 0x0421 (padman 4.33, as libpad checks) */

/* introspection (tests, tools) */
typedef struct rg_npad_info {
    int open, state, req, mode_id, locked;
    uint32_t frame;
    uint8_t align[6];
    uint8_t rumble_small, rumble_large;
} rg_npad_info;
int rg_npad_port_get(int port, rg_npad_info *out);
uint32_t rg_npad_rumble_calls(void);
uint64_t rg_npad_last_vblank(void);

#ifdef __cplusplus
}
#endif
#endif
