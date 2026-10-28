/* rg-override: replaces game/src/main/movie/ViBufSetD4Chcr_1d47a0.c sha256 c2550317c981d119a2fa9a2fb5db0a66a9f5c28dd34fff23ae4517f3e5dc04c2
 * why: unreachable natively (docs/NATIVE-CPU.md section 8, docs/MOVIE.md "no longer reached"):
 *      the game's own IPU / DMA ch3-4 / D_ENABLE register code.  The movie layer that called
 *      it is replaced by the port's movie service; tools/native/reach_census.py finds no
 *      reference from linked code.  The body is gone (no hwbus access left); a call is a bug
 *      and stops with a message. */
/* rgp:protos */
#define RGP_SELF_ViBufSetD4Chcr_1d47a0 1
#include "port/game_protos.h"
#line 1

void rg_movie_g_unreachable(const char *fn); /* src/movie/mv_game.c: message + abort */

void ViBufSetD4Chcr_1d47a0(int a0)
{
    (void)a0;
    rg_movie_g_unreachable("ViBufSetD4Chcr_1d47a0");
}
