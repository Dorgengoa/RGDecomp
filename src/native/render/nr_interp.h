/* SPDX-License-Identifier: CC0-1.0 */
/* Interpolated presentation: the unlocked frame rate (PLAN.md "Unlocked frame rate",
 * docs/NATIVE-RENDER.md "Interpolated presentation").
 *
 * The game keeps its retail cadence (59.94 Hz VBlank phases, its own 1- / 2-VBlank logic
 * tick).  The renderer retains the last game frames natively and presents in-between images:
 *
 *   log      (worker) everything the GS input handed the worker between two game frame
 *            starts (DrawListFrameBegin): the immediate records in order (ids into nr_im's
 *            ring) and copies of the IMAGE data, plus the worker's state block at the start
 *            (nr_gs: plain data).  Three logs are kept: the newest (the frame the device shows
 *            now) and the two before it.
 *   items    (worker) the native mesh draws of a log with copies of their constant block and
 *            bone rows, and a stable identity across frames: (decoded mesh, draw context,
 *            program variant), several instances told apart by the nearest object position.
 *   pass     (worker) the log executed again from its start state with the mesh items drawn
 *            from constants interpolated between the previous frame's matched item and this
 *            frame's (object matrix and camera: rotation slerp, scale / translation lerp;
 *            projection lerp; bone matrices likewise), then the derived rows recomputed
 *            (nr_const_prog0).  Everything else in the log (2D, effects, transfers, CLUT loads,
 *            screen passes, unmatched meshes) runs as recorded: it snaps to the latest frame.
 *   restore  (worker) after a pass the device holds an in-between image; before anything else
 *            reads or extends the device state (the next GS input, a local->host read, the
 *            runtime's display read for its hash, a dump) the newest log runs once more exactly
 *            (dirty flag; nr_ip_settle), so the game, the run hash and every later frame see
 *            the original device state.
 *
 * Interpolation delays the image by one game frame: at host time tau (in VBlank phases) the
 * newest frame N (begun at phase T_N, previous T_{N-1}) is shown at alpha =
 * (tau - T_N) / (T_N - T_{N-1}) between N-1 and N, clamped to [0, 1].  $RG_INTERP_LEAD=x (0..1,
 * default 0) shows it x game frames earlier by extrapolating past N (alpha up to 1 + x; a late
 * frame takes the overshoot back): x frames less delay, a step at every change of motion
 * (docs/NATIVE-RENDER.md "Checkpoint 13").
 *
 * Characters (Z-scale composites: parts drawn into a work buffer, copied into the frame by
 * strips) get their pose interpolated: bones only, the copy moved and widened (nr_iprec.cpp
 * "composite poses", $RG_INTERP_ZSCALE in nr_interp.c).
 *
 * Off unless enabled (display.interpolation = on, or RG_INTERP=1): no log, no copies, no
 * passes; the Original preset is unchanged.  RG_NATIVE_ONLY builds with the D3D11 device only
 * (stubs elsewhere). */
#ifndef RG_NR_INTERP_H
#define RG_NR_INTERP_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- EE thread (runtime) --------------------------------------------------- */
/* on / off (the setting or $RG_INTERP; the runtime calls it when its settings change) */
void nr_ip_configure(int on);
int nr_ip_on(void);
/* the runtime's phase counter after it took a phase (rg_pace ticks) */
void nr_ip_tick(uint64_t ticks);
/* DrawListFrameBegin (nr_frame_begin): a game frame starts; queues the log boundary */
void nr_ip_frame_begin(uint32_t frame_no);
/* Queue an interpolated pass for host time tau (phases, fractional); display_regs = the PCRTC
 * registers (nr_hw_display_regs) the present will compose from.  Returns 1 when a pass was
 * queued (the caller drains the worker and presents the device's display as usual), 0 when
 * there is nothing to interpolate (present as usual). */
int nr_ip_queue_present(double tau, const uint64_t *display_regs);
/* Queue the restore pass when a pass left the device in-between (before the EE reads the
 * device: display hash, dumps, local->host reads, save states).  Cheap when clean. */
void nr_ip_settle(void);
/* exit-line statistics and the identity census (docs "Interpolated presentation") */
void nr_ip_stats(FILE *f);

/* RG_INTERP_CHECK=1 (headless measurement): queue an EXACT pass of the newest log (no
 * interpolation); the caller compares the display before and after: equal = the frame is
 * self-contained (re-executing it reproduces it). */
int nr_ip_queue_exact(void);

/* ---- worker (GS input, nr_gs.c / nr_hw.c) ---------------------------------- */
void nr_ip_w_rec(uint32_t id);                       /* before the record runs */
void nr_ip_w_image(const void *qw, uint32_t nqw);    /* before IMAGE data runs */
void nr_ip_w_reset(void);                            /* CSR.RESET: logs void */

/* ---- worker (mesh marker, nr_scene.c) --------------------------------------- */
/* 0 normal execution, 1 interpolated pass, 2 exact pass (restore / check) */
int nr_ip_pass(void);
/* a native mesh draw of the original execution (after it was drawn) */
void nr_ip_note(uint32_t id, const void *mesh, int variant, uint32_t ctx, uint64_t frame_reg, int has_box,
                const float box[4], const void *c, const void *bones, uint32_t bones_hi);
/* during a pass: what to draw for mesh record id (constants interpolated in pass 1); NULL when
 * the log holds no such item (skip it) */
typedef struct nr_ip_draw {
    const void *mesh;
    int variant;
    int has_box;
    float box[4];
    const void *c;          /* nr_qw[112] */
    const void *bones;      /* nr_qw[256] (rows past bones_hi zero) */
    uint32_t bones_hi;
    int interp;             /* 0: as recorded (exact item, or an exact pass) */
} nr_ip_draw;
const nr_ip_draw *nr_ip_draw_for(uint32_t id);

/* ---- the device (nr_iprec.cpp): the retained frame as the device's command list ---- */
struct gpu_renderer;
struct gpu_nr_draw;
#define NR_IP_SLOTS 5                                 /* logs kept (slots of the recorder) */
void gpu_ip_install(struct gpu_renderer *r);          /* wrap the backend (once) */
void gpu_ip_set_mesh(uint32_t id);                    /* the mesh record the next native draw is */
void gpu_ip_rec_slot(struct gpu_renderer *r, int slot); /* record into slot 0..2 from now (-1: stop) */
void gpu_ip_slot_free(struct gpu_renderer *r, int slot);
/* run the commands of slots[0..n) again, oldest first, from the targets' state before the first
 * (pre-images); slot interp_at's mesh draws through nr_ip_mesh_cb (-1: none) and its immediate
 * draws (2D, effects) paired with slot prev's by order and state, their vertices lerped from
 * prev's toward the recorded ones at weight alpha (prev -1: as recorded); 0 done, -1 not
 * possible */
int gpu_ip_replay(struct gpu_renderer *r, const int *slots, int n, int interp_at, int prev, float alpha);
void gpu_ip_restore(struct gpu_renderer *r);          /* the targets a replay wrote back as they were */
int gpu_ip_dirty(struct gpu_renderer *r);
/* do slots[0]'s mesh draws reach the displayed target by the end of slots[0..n)?  1 / 0, -1 unknown */
int gpu_ip_flows(struct gpu_renderer *r, const int *slots, int n);
void gpu_ip_slot_info(struct gpu_renderer *r, int slot, uint32_t out[4]);   /* cmds, pre-images, created, bad */
void gpu_ip_stats(struct gpu_renderer *r, FILE *f);
void gpu_ip_dump(struct gpu_renderer *r, int slot, FILE *f);   /* $RG_INTERP_CMDDUMP=frame: the log's commands */
/* (nr_scene.c) the replay's mesh draw: d's constant rows / bones / culling for mesh record id from
 * nr_ip_draw_for; 1 = substituted, 0 = draw as recorded */
int nr_ip_mesh_cb(uint32_t id, struct gpu_nr_draw *d);
/* Z-scale composites ($RG_INTERP_ZSCALE, nr_interp.c): the mode, and (mode 4, the replay) whether the
 * mesh draws that follow feed a strip group whose copy into the frame was widened (their pose may
 * move: interpolated), 0 = drawn as recorded */
int nr_ip_zs_mode(void);
void nr_ip_zs_allow(int ok);
/* during a pass: 1 when mesh record id of the frame being interpolated is a Z-scale composite part */
int nr_ip_zs_item(uint32_t id);

#ifdef __cplusplus
}
#endif
#endif
