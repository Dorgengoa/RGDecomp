/* SPDX-License-Identifier: CC0-1.0 */
/* padman HLE: the IOP pad driver (PADMAN.IRX 4.33) as a host model (docs/PADMC.md).
 *
 * One DualShock 2 per port (no multitap: slot 0 only). The model owns, per port,
 * the controller state machine (FINDPAD -> FINDCTP1 -> STABLE, DISCONN when no
 * controller), the main mode (digital 0x41 / analog 0x73 / pressure 0x79),
 * actuator alignment, and the 256-byte pad DMA buffer that libpad gave it in
 * scePadPortOpen. It writes that buffer exactly as padman's per-frame SIF DMA
 * would: two 0x80-byte halves, the newer one marked by a larger frame counter
 * at +0x58 (layout below).
 *
 * Time is the VBlank count. padman_update(vblank) advances every open port to
 * that VBlank (one state-machine step per VBlank) and writes the buffers. The
 * EE libpad (src/sce/padmc) calls it on entry to every libpad function, so the
 * buffer is current whenever the game looks; a runtime may also call it from
 * its VBlank hook. Kernel-agnostic: nothing here reads a clock.
 *
 * Input: a host "input source" (rg_pad_input_fn) is asked for the report of
 * (port, vblank). With no source, the last report pushed with rg_pad_push_report
 * is used. A report is a pure function of its inputs, so a scripted source
 * (rg_pad_script_*) replays deterministically.
 */
#ifndef RG_PS2_PADMAN_H
#define RG_PS2_PADMAN_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* Buttons, rg_pad_report, the input source, rumble hook and scripted replay are the
 * shared pad I/O (src/native/input/rg_pad_io.h): the native pad service (the default,
 * RG_IOP=native) and this HLE (the oracle) read the same source. */
#include "rg_pad_io.h"

/* ---- model ---------------------------------------------------------------------- */
typedef struct padman_config {
    int find_frames;   /* VBlanks in FINDPAD after open / reconnect (default 2) */
    int ctp1_frames;   /* VBlanks in FINDCTP1 identifying the controller (default 2) */
    int cmd_frames;    /* VBlanks a mode/actuator/button-info command stays BUSY (default 3) */
    int start_analog;  /* 0 (default): a DS2 powers up digital (0x41), as hardware */
    int keep_analog_lock; /* 1: once the game has locked analog mode (SetMainMode(1, 3)), the
                             port stays analog + locked (0x73): an unplug / replug does not
                             power-cycle it to digital and a SetMainMode to digital is ignored,
                             so the game's "analog required" pause cannot come from a host
                             device change.  0 (default here): hardware behaviour.  The
                             runtime turns it on (rg_runtime_config.pad_power_cycle = 0). */
    int default_connected[RG_PAD_PORTS]; /* latched report before any push: {1, 0} */
} padman_config;
void padman_default_config(padman_config *c);
/* Reset the model (ports closed, latched reports default, hooks kept). NULL = defaults. */
void padman_reset(const padman_config *c);
const padman_config *padman_get_config(void);

/* Register the SIF servers 0x80000100 / 0x80000101 (replacing the placeholders in
 * src/ps2/iop). Returns 0 on success. padman_installed() is 1 while ours are the
 * registered ones (rg_sif_boot re-registers the placeholders). */
int padman_install(void);
int padman_installed(void);

/* Advance every open port to `vblank` and write the DMA buffers. Idempotent for
 * the same vblank. A gap of many VBlanks is stepped one by one up to 600 steps,
 * then jumps (the machine has converged by then). */
void padman_update(uint64_t vblank);
uint64_t padman_last_vblank(void);

/* SetActDirect: libpad hands over the 6 direct bytes (retail: SIF DMA to the
 * 0x80000101 buffer). Returns 1 if accepted (port open, controller stable). */
int padman_act_direct(int port, int slot, const uint8_t direct[6]);

/* ---- RPC protocol (port's own layout; numbering follows retail libpad) ---------- *
 * sid 0x80000100, fno 1, 128-byte request == reply buffer of u32 words:
 *   w[0] cmd, w[1] port, w[2] slot, w[3] arg (mode / info), w[4] arg2 (lock / EE
 *   buffer address), bytes 0x0C..0x11 = actuator align for SETACTALIGN.
 * Reply: w[3] = result of OPEN/INIT/GETMODVERSION/PORTMAX/SLOTMAX,
 *        w[5] = result of SETMAINMODE/SETACTALIGN/SETBUTTONINFO/CLOSE/END/SETVREF. */
enum {
    PADMAN_CMD_OPEN = 0x01,
    PADMAN_CMD_SETMAINMODE = 0x06,
    PADMAN_CMD_SETACTALIGN = 0x08,
    PADMAN_CMD_SETBUTTONINFO = 0x0A,
    PADMAN_CMD_SETVREF = 0x0B,
    PADMAN_CMD_GETPORTMAX = 0x0C,
    PADMAN_CMD_GETSLOTMAX = 0x0D,
    PADMAN_CMD_CLOSE = 0x0E,
    PADMAN_CMD_END = 0x0F,
    PADMAN_CMD_INIT = 0x10,
    PADMAN_CMD_GETMODVERSION = 0x12
};
#define PADMAN_MOD_VERSION 0x0421u /* padman 4.33: libpad requires (v >> 8) == 4 */
#define PADMAN_SID 0x80000100u
#define PADMAN_SID_EXT 0x80000101u

/* ---- DMA buffer layout (each 0x80-byte half; libpad reads the newer one) --------- */
#define PAD_DMA_SIZE      0x100
#define PAD_HALF          0x80
#define PAD_OFS_DATA      0x00 /* 32 bytes: [0] 0 = ok, [1] mode id, [2..3] buttons (active-low,
                                  [2] = high byte), [4..7] rx ry lx ly, [8..19] pressures */
#define PAD_OFS_ACTDIR    0x20 /* 8 bytes */
#define PAD_OFS_ACTALIGN  0x28 /* 8 bytes */
#define PAD_OFS_ACTDATA   0x30 /* 32 bytes: actuator n term t (1..4) at 0x30 + n*4 + t-1 */
#define PAD_OFS_ACTCOMB   0x40 /* observed 02 00 01 00 (actuator combination data; VALIDATION.md 4) */
#define PAD_OFS_MODETABLE 0x50 /* u16[4] */
#define PAD_OFS_FRAME     0x58 /* u32 frame counter (newer half = larger, signed compare) */
#define PAD_OFS_RETRIES   0x5C /* u32 */
#define PAD_OFS_LENGTH    0x60 /* u32 bytes scePadRead copies */
#define PAD_READ_LENGTH   0x20 /* what padman puts there when STABLE (VALIDATION.md 4) */
#define PAD_OFS_MODECONF  0x64 /* 1 = no mode info; >= 2 = DS2 (actuators) */
#define PAD_OFS_MODECURID 0x65 /* 0x41 / 0x73 / 0x79 */
#define PAD_OFS_MODEL     0x66
#define PAD_OFS_READY     0x67 /* buttonDataReady */
#define PAD_OFS_NMODES    0x68
#define PAD_OFS_MODEOFFS  0x69
#define PAD_OFS_NACT      0x6A
#define PAD_OFS_NCOMB     0x6B
#define PAD_OFS_UNK6C     0x6C /* observed 00 01 03 00 (VALIDATION.md 4) */
#define PAD_OFS_STATE     0x70
#define PAD_OFS_REQSTATE  0x71
#define PAD_OFS_OK        0x72

/* libpad states (scePadGetState) and request states (scePadGetReqState) */
enum { PAD_STATE_DISCONN = 0, PAD_STATE_FINDPAD = 1, PAD_STATE_FINDCTP1 = 2,
       PAD_STATE_EXECCMD = 5, PAD_STATE_STABLE = 6, PAD_STATE_ERROR = 7 };
enum { PAD_RSTAT_COMPLETE = 0, PAD_RSTAT_FAILED = 1, PAD_RSTAT_BUSY = 2 };

/* Newer half of a DMA buffer (as libpad's scePadGetDmaStr picks it). */
uint8_t *padman_newest_half(uint8_t *dma);

/* ---- introspection (tests, trace tools) ------------------------------------------ */
typedef struct padman_port_info {
    int open, state, req, mode_id, locked;
    uint32_t frame;
    uint8_t align[6];
    uint8_t rumble_small, rumble_large;
    uint32_t commands; /* RPC commands handled for this port */
} padman_port_info;
int padman_port_get(int port, padman_port_info *out);
uint32_t padman_rumble_calls(void);

#ifdef __cplusplus
}
#endif
#endif
