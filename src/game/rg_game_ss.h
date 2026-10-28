/* SPDX-License-Identifier: CC0-1.0
 * rg-game's save-state CLI (rg_game_ss.c, docs/TEST-FIXTURES.md). */
#ifndef RG_GAME_SS_H
#define RG_GAME_SS_H

#include <stdint.h>

/* First thing in main: with --save-state / --load-state in argv (or RG_SS=1)
 * reserve the state region before any window, GPU device or thread exists. */
void rg_game_ss_early(int argc, char **argv);
/* One argument: 1 = consumed a and its value v, 0 = not a save-state flag,
 * -1 = bad value.  --save-state FIELD:FILE, --state-note TEXT, --load-state FILE */
int rg_game_ss_arg(const char *a, const char *v);
/* Before rg_runtime_init: fiber arena, crt0 RAM provider, hooks.  0 ok. */
int rg_game_ss_before_init(void);
/* After rg_runtime_init: end of the init fingerprint, then --load-state.
 * *first_field = the loaded state's field (0 without one).  0 ok, -1 refused
 * (message printed; nothing was written back), -2 failed mid-load (exit). */
int rg_game_ss_after_init(uint64_t *first_field);
/* After field `field` completed (and its shots): --save-state points. */
void rg_game_ss_field_done(uint64_t field, const char *input_script);
int rg_game_ss_saving(void);

#endif
