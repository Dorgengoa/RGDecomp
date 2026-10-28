/* rg-override: replaces game/src/main/movie/ViBufDelete_1d3e20.c sha256 dc53a6da3063044d89e24983a2542f2b6cd81b03182294d2e2761432a750e196
 * why: unreachable natively (docs/NATIVE-CPU.md section 8, docs/MOVIE.md "no longer reached"):
 *      the game's own IPU / DMA ch3-4 / D_ENABLE register code.  The movie layer that called
 *      it is replaced by the port's movie service; tools/native/reach_census.py finds no
 *      reference from linked code.  The body is gone (no hwbus access left); a call is a bug
 *      and stops with a message. */
/* rgp:protos */
#define RGP_SELF_ViBufDelete_1d3e20 1
#include "port/game_protos.h"
#line 1

void rg_movie_g_unreachable(const char *fn); /* src/movie/mv_game.c: message + abort */

int ViBufDelete_1d3e20(void *a0)
{
    (void)a0;
    rg_movie_g_unreachable("ViBufDelete_1d3e20");
    return 0;
}
