/* rg-override: replaces game/src/main/movie/MoviePlayerShutdown_1d56c0.c sha256 9aa6039e3289372818aa4c46d268f48890d4c89f41b8698a46ebe8f76be94bee
 * why: movie layer replaced by the port's movie service (docs/MOVIE.md "Override list"):
 * no movie threads or handlers to tear down, no libmpeg context or MVI stream to close;
 * the service is closed (this is also the skip path). */
/* rgp:protos */
#define RGP_SELF_MoviePlayerShutdown_1d56c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* src/movie/movie_game.h (CC0 port service) */
extern void rg_movie_g_close(void);

extern s32 D_004817E0;
extern u8 D_004B32D0[];

typedef struct S1D5 {
    u8 pad0[0x17900];
    u8 unk17900;
    u8 pad17901[3];
    s32 unk17904;
    s32 unk17908;
    s32 unk1790C;
    s32 unk17910;
} S1D5;

void MoviePlayerShutdown_1d56c0(S1D5 *arg0)
{
    if (arg0->unk17900 != 0) {
        D_004817E0 = 1; /* retail: set by MovieReadThread on its way out */
        arg0->unk17900 = 0;
    }
    rg_movie_g_close();
    AudioDecReset_1d3070(D_004B32D0);
    AudioDecDelete_1d31d0(D_004B32D0);
    CdDiskWatchSetEnabled_17fe80(arg0->unk17910);
}
