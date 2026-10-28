/* rg-override: replaces game/src/main/movie/ViBufRestartDma_1d3e70.cpp sha256 8ae2bfe2895193195159a35892e3c4fe2e9bbe2116f5eff231bdf132511c2191
 * why: unreachable natively (docs/NATIVE-CPU.md section 8, docs/MOVIE.md "no longer reached"):
 *      the game's own IPU / DMA ch3-4 / D_ENABLE register code.  The movie layer that called
 *      it is replaced by the port's movie service; tools/native/reach_census.py finds no
 *      reference from linked code.  The body is gone (no hwbus access left); a call is a bug
 *      and stops with a message. */
/* rgp:protos */
#define RGP_SELF_ViBufRestartDma_1d3e70 1
#include "port/game_protos.h"
#line 1

extern "C" void rg_movie_g_unreachable(const char *fn); /* src/movie/mv_game.c: message + abort */

extern "C" int ViBufRestartDma_1d3e70(void *a0)
{
    (void)a0;
    rg_movie_g_unreachable("ViBufRestartDma_1d3e70");
    return 0;
}
