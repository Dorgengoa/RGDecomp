/* SPDX-License-Identifier: CC0-1.0 */
/* Pad input/output between the host shell and the game's pad service (docs/NATIVE-IOP.md,
 * docs/PADMC.md "Host interface").  Shared by the native pad service (rg_npad.h, the
 * default) and the padman HLE (src/ps2/padmc, the RG_IOP=hle oracle): both ask the same
 * input source for the report of (port, vblank) and send motor changes to the same hook,
 * so a run makes the same input-source calls in either mode.
 *
 * The host shell (src/host, via src/runtime) either installs a pull source keyed by
 * VBlank (deterministic replays, the input-action layer) or pushes a latched report. */
#ifndef RG_NATIVE_PAD_IO_H
#define RG_NATIVE_PAD_IO_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define RG_PAD_PORTS 2

/* ---- DS2 buttons: active-high, SCE_PAD* bit layout (the game's decoded word) ---- */
#define RG_PAD_L2       0x0001u
#define RG_PAD_R2       0x0002u
#define RG_PAD_L1       0x0004u
#define RG_PAD_R1       0x0008u
#define RG_PAD_TRIANGLE 0x0010u
#define RG_PAD_CIRCLE   0x0020u
#define RG_PAD_CROSS    0x0040u
#define RG_PAD_SQUARE   0x0080u
#define RG_PAD_SELECT   0x0100u
#define RG_PAD_L3       0x0200u
#define RG_PAD_R3       0x0400u
#define RG_PAD_START    0x0800u
#define RG_PAD_UP       0x1000u
#define RG_PAD_RIGHT    0x2000u
#define RG_PAD_DOWN     0x4000u
#define RG_PAD_LEFT     0x8000u

/* Pressure array order = DS2 frame bytes 8..19. */
enum {
    RG_PAD_P_RIGHT = 0, RG_PAD_P_LEFT, RG_PAD_P_UP, RG_PAD_P_DOWN,
    RG_PAD_P_TRIANGLE, RG_PAD_P_CIRCLE, RG_PAD_P_CROSS, RG_PAD_P_SQUARE,
    RG_PAD_P_L1, RG_PAD_P_R1, RG_PAD_P_L2, RG_PAD_P_R2, RG_PAD_P_COUNT
};

/* What the host shell provides per frame and port. */
typedef struct rg_pad_report {
    uint8_t  connected;   /* 0 = no controller in this port */
    uint8_t  has_pressure;/* 0 = derive pressure from buttons (pressed = 0xFF) */
    uint16_t buttons;     /* RG_PAD_* active-high */
    uint8_t  lx, ly, rx, ry; /* 0..255, 0x80 = centre, y down = 0xFF */
    uint8_t  pressure[RG_PAD_P_COUNT]; /* 0 = released .. 0xFF = full */
} rg_pad_report;

/* Neutral connected report (sticks centred, nothing pressed). */
void rg_pad_report_neutral(rg_pad_report *r);

/* Pull source: fill *out for (port, vblank) and return 1, or return 0 to use the
 * latched report for that port. vblank is the kernel VBLANK_START count, not the
 * game's own counter [0x004810C4]. Called on the thread that entered the pad API;
 * must be a pure function of its arguments for replays to be deterministic. */
typedef int (*rg_pad_input_fn)(void *user, int port, uint64_t vblank, rg_pad_report *out);
void rg_pad_set_input_source(rg_pad_input_fn fn, void *user);
/* Push source: latch the report used when no pull source answers. */
void rg_pad_push_report(int port, const rg_pad_report *r);

/* Vibration: called when the motor state the game requested changes (after
 * SetActAlign mapped the actuators). small: 0/1 (motor 0), large: 0..255 (motor 1). */
typedef void (*rg_pad_rumble_fn)(void *user, int port, uint8_t small, uint8_t large);
void rg_pad_set_rumble_hook(rg_pad_rumble_fn fn, void *user);

/* ---- for the pad services (native and HLE) -------------------------------------- */
/* The report of (port, vblank): the pull source's, else the latched one. */
void rg_pad_io_report(int port, uint64_t vblank, rg_pad_report *out);
/* Latched reports back to neutral, connected per `default_connected` (NULL: {1, 0}).
 * Hooks are kept. */
void rg_pad_io_reset_latched(const int default_connected[RG_PAD_PORTS]);
/* Send a motor change to the hook. */
void rg_pad_io_rumble(int port, uint8_t small, uint8_t large);

/* ---- scripted input (replay) ------------------------------------------------------ *
 * Text format of tools/trace (examples/start_cross.txt): one line per span
 *   first_vbl last_vbl BUTTON[+BUTTON...]   (inclusive, '#' comments)
 * Buttons: L2 R2 L1 R1 TRIANGLE CIRCLE CROSS SQUARE SELECT L3 R3 START UP RIGHT DOWN LEFT.
 * The script's frame number is (kernel vblank - vbl_offset), so a trace script
 * written in game VBlank units can be replayed by setting the offset between the
 * two counters. Port 0 only; sticks centred. */
typedef struct rg_pad_script rg_pad_script;
rg_pad_script *rg_pad_script_parse(const char *text, char *err, int errlen);
rg_pad_script *rg_pad_script_load(const char *path, char *err, int errlen);
void rg_pad_script_free(rg_pad_script *s);
void rg_pad_script_set_offset(rg_pad_script *s, int64_t vbl_offset);
uint16_t rg_pad_script_buttons(const rg_pad_script *s, int64_t frame);
/* An rg_pad_input_fn: user = rg_pad_script*. */
int rg_pad_script_source(void *user, int port, uint64_t vblank, rg_pad_report *out);

#ifdef __cplusplus
}
#endif
#endif
