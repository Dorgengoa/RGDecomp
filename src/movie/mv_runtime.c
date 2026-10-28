/* SPDX-License-Identifier: CC0-1.0 */
/* Movie service <-> platform runtime binding (docs/MOVIE.md "Runtime binding",
 * docs/RUNTIME.md "Hooks for other services").
 *
 * With MovieOpen/MoviePlayerStart/... overridden, the game no longer programs the IPU
 * or DMA channels 3/4: decoding happens in src/movie.  The ViBuf* functions that held the
 * game's IPU / DMA ch3-4 / D_ENABLE register code are stub overrides that stop with a
 * message (unreachable: tools/native/reach_census.py, docs/NATIVE-CPU.md section 8), so
 * the IPU hwbus hooks and the fromIPU/toIPU DMAC bindings this file used to install are
 * gone.  What is left: the data root from the runtime config. */
#include "movie_game.h"
#include "rg_runtime.h"

void rg_movie_runtime_service(void *user)
{
    (void)user;
    const rg_runtime_config *c = rg_runtime_get_config();
    if (c && c->data_dir && *c->data_dir) rg_movie_g_set_data_root(c->data_dir);
}

void rg_movie_runtime_attach(void) { rg_runtime_set_service_hook(rg_movie_runtime_service, NULL); }
