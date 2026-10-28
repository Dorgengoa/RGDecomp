/* rg-override: replaces game/src/main/movie/ViBufReset_1d45b0.c sha256 7487ddc4733d67c072abb07e3ea190ebec9c13f4e37b76ebceb02afcb05cc712
 * why: unreachable natively (docs/NATIVE-CPU.md section 8, docs/MOVIE.md "no longer reached"):
 *      the game's own IPU / DMA ch3-4 / D_ENABLE register code.  The movie layer that called
 *      it is replaced by the port's movie service; tools/native/reach_census.py finds no
 *      reference from linked code.  The body is gone (no hwbus access left); a call is a bug
 *      and stops with a message. */
/* rgp:protos */
#define RGP_SELF_ViBufReset_1d45b0 1
#include "port/game_protos.h"
#line 1

void rg_movie_g_unreachable(const char *fn); /* src/movie/mv_game.c: message + abort */

int ViBufReset_1d45b0(void *a0)
{
    (void)a0;
    rg_movie_g_unreachable("ViBufReset_1d45b0");
    return 0;
}
