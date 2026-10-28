/* rg-override: replaces game/src/main/movie/ViBufAddDma_1d4240.c sha256 98ba955331e0c45b7d62ba158f64a2ca21d9366a2d82362a29633c344e9ec7d4
 * why: unreachable natively (docs/NATIVE-CPU.md section 8, docs/MOVIE.md "no longer reached"):
 *      the game's own IPU / DMA ch3-4 / D_ENABLE register code.  The movie layer that called
 *      it is replaced by the port's movie service; tools/native/reach_census.py finds no
 *      reference from linked code.  The body is gone (no hwbus access left); a call is a bug
 *      and stops with a message. */
/* rgp:protos */
#define RGP_SELF_ViBufAddDma_1d4240 1
#include "port/game_protos.h"
#line 1

void rg_movie_g_unreachable(const char *fn); /* src/movie/mv_game.c: message + abort */

int ViBufAddDma_1d4240(void *a0)
{
    (void)a0;
    rg_movie_g_unreachable("ViBufAddDma_1d4240");
    return 0;
}
