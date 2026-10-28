/* rg-override: replaces game/src/main/movie/ViBufGetTs_1d3990.c sha256 3b45c7680894d2ce0cd49357915c4609f147cea5b3690b7743e815ee3d463aaa
 * why: unreachable natively (docs/NATIVE-CPU.md section 8, docs/MOVIE.md "no longer reached"):
 *      the game's own IPU / DMA ch3-4 / D_ENABLE register code.  The movie layer that called
 *      it is replaced by the port's movie service; tools/native/reach_census.py finds no
 *      reference from linked code.  The body is gone (no hwbus access left); a call is a bug
 *      and stops with a message. */
/* rgp:protos */
#define RGP_SELF_ViBufGetTs_1d3990 1
#include "port/game_protos.h"
#line 1

void rg_movie_g_unreachable(const char *fn); /* src/movie/mv_game.c: message + abort */

int ViBufGetTs_1d3990(void *a0, void *a1)
{
    (void)a0;
    (void)a1;
    rg_movie_g_unreachable("ViBufGetTs_1d3990");
    return 0;
}
