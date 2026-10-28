/* rg-override: replaces game/src/main/movie/ViBufSetD3Chcr_1d4800.c sha256 4d565321b024a9b62c31b354f75ccca8edd63c918ab8a80b5c8bcb641db6a64a
 * why: unreachable natively (docs/NATIVE-CPU.md section 8, docs/MOVIE.md "no longer reached"):
 *      the game's own IPU / DMA ch3-4 / D_ENABLE register code.  The movie layer that called
 *      it is replaced by the port's movie service; tools/native/reach_census.py finds no
 *      reference from linked code.  The body is gone (no hwbus access left); a call is a bug
 *      and stops with a message. */
/* rgp:protos */
#define RGP_SELF_ViBufSetD3Chcr_1d4800 1
#include "port/game_protos.h"
#line 1

void rg_movie_g_unreachable(const char *fn); /* src/movie/mv_game.c: message + abort */

void ViBufSetD3Chcr_1d4800(int a0)
{
    (void)a0;
    rg_movie_g_unreachable("ViBufSetD3Chcr_1d4800");
}
