/* rg-override: replaces game/src/main/movie/ViBufStopDma_1d4180.c sha256 b1b9fe3d795a6a76d0832778cbb14267cc3b9a3681b944b1732958d226ae6e60
 * why: unreachable natively (docs/NATIVE-CPU.md section 8, docs/MOVIE.md "no longer reached"):
 *      the game's own IPU / DMA ch3-4 / D_ENABLE register code.  The movie layer that called
 *      it is replaced by the port's movie service; tools/native/reach_census.py finds no
 *      reference from linked code.  The body is gone (no hwbus access left); a call is a bug
 *      and stops with a message. */
/* rgp:protos */
#define RGP_SELF_ViBufStopDma_1d4180 1
#include "port/game_protos.h"
#line 1

void rg_movie_g_unreachable(const char *fn); /* src/movie/mv_game.c: message + abort */

int ViBufStopDma_1d4180(void *a0)
{
    (void)a0;
    rg_movie_g_unreachable("ViBufStopDma_1d4180");
    return 0;
}
