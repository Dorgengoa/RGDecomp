/* SPDX-License-Identifier: CC0-1.0 */
/* Online Insectron 2-Player Battle, the session layer (rg_insnet.c; docs/INSECTRON-VERSUS.md). */
#ifndef RG_INSNET_H
#define RG_INSNET_H

#include <stddef.h>
#include <stdint.h>

#include "rg_runtime.h"

struct rg_settings;

/* command line: 0 = not ours, 1 = flag used (no value), 2 = flag + value used, -1 = bad */
int rg_insnet_arg(const char *a, const char *v);
/* a host / join / hand-over was asked for */
int rg_insnet_wanted(void);
/* before rg_runtime_init: connect, exchange, build the session saves (cfg->saves_dir is
 * replaced) and install the pad hook.  0 ok; -1 with err */
int rg_insnet_start(rg_runtime_config *cfg, struct rg_settings *settings, char *err, size_t cap);
/* the runtime pad hook (rg_runtime_set_pad_hook) */
void rg_insnet_pad(void *user, int port, uint32_t vbl, uint16_t *buttons, uint8_t sticks[4], int *connected);
/* the main loop, around each rg_runtime_run_field (k = fields run before / after) */
void rg_insnet_before_field(uint64_t k);
int rg_insnet_after_field(uint64_t k);
/* at exit: last hashes, BYE, close; returns 6 on a desync, else 0 */
int rg_insnet_finish(void);
int rg_insnet_active(void);
const char *rg_insnet_end_reason(void);
/* the original command line (main), for the relaunches */
void rg_insnet_set_argv(int argc, char **argv);
/* the ids both peers must share */
uint64_t rg_insnet_build_id(void);
uint64_t rg_insnet_data_id(void);
/* the port the menus host on and call by default (--net-port N, $RG_NET_PORT, else 7490) */
int rg_insnet_menu_port(void);
/* session: INSMENU hooks (overrides) */
int rg_insnet_lost_notice(void);
int rg_insnet_session(void);
void rg_insnet_session_left(void);

/* rg_insnet_ui.c: the way in through the game's menus (overrides call these) */
void rg_insnet_ui_set_argv(int argc, char **argv);
const char *rg_insnet_ui_text(int id);
int rg_insnet_ui_ctx(void);
void rg_insnet_ui_cancel(void);
void rg_insnet_ui_top_layout(void *widgets);
int rg_insnet_ui_begin(void);
int rg_insnet_ui_active(void);
int rg_insnet_ui_tick(void);
void rg_insnet_ui_answer(int id, int yes);
int rg_insnet_ui_want(void);
const char *rg_insnet_ui_entry_initial(void);
void rg_insnet_ui_entry_done(const char *text, int ok);
void rg_insnet_ui_relaunch(void);
void rg_insnet_spawn_self(int argc, char **argv, const char *const *extra, int nextra);

#endif
