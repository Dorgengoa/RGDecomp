/* SPDX-License-Identifier: CC0-1.0 */
#ifndef RG_GPU_TESTS_H
#define RG_GPU_TESTS_H

#include "gpu.h"
#include "gs.h"

/* gpu_tee.c */
void tee_set_renderer(gpu_renderer *r);
extern const char *g_tee_name;

/* gpu_scenes.c: returns 1 if `name` is a scene (and ran it) */
int run_scene(const char *name, gpu_renderer *r);
extern int g_scene_tol;
extern int g_scene_tol_force;

/* gpu_replay.c: GS recordings of the real game (RG_GS_REC) */
int run_replay(const char *path, gpu_renderer *r);
int run_replay_dir(const char *dir, gpu_renderer *r);

/* gpu_gfx_tests.c: graphics settings (docs/GPU.md "Graphics settings");
 * run_gfx_test returns 1 = ran and passed, -1 = ran and failed, 0 = unknown */
int run_gfx_test(const char *name, gpu_renderer *r);
int run_gfx_replay_dir(const char *dir, gpu_renderer *r);
int run_gfx_bench(const char *dir, gpu_renderer *r);
int run_gfx_perf(const char *dir, const char *match, gpu_renderer *r);
int run_lag_test(const char *path, gpu_renderer *ref, gpu_renderer *lag);

/* golden tests (tests/gs) */
int test_clut(const char *name);
int test_pixel(const char *name);
int test_prim(const char *name);
int test_display(const char *name);

#endif
