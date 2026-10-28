/* rg-override: replaces game/src/main/movie/MoviePlayerStart_1d5b50.c sha256 d52a145d82406f381600c578496d1d4bc02497d24b14b2bcd751259e230a29ea
 * why: movie layer replaced by the port's movie service (docs/MOVIE.md "Override list"):
 * no movie threads, no VBLANK/DMAC handlers; builds the GS upload packets that
 * VideoDecDecodeBs_1d29e0 built at the first picture. */
/* rgp:protos */
#define RGP_SELF_MoviePlayerStart_1d5b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004817E4;
extern u8 D_004B3210[0x400];
extern u8 D_004B3330[0x20];

void MoviePlayerStart_1d5b50(u8 *arg0, s32 arg1)
{
    s32 i;
    s32 n;
    u8 *tags;
    s32 w;
    s32 h;

    if (*(u8 *)(arg0 + 0x17900) == 0) {
        AudioDecSetInputVolume_1d2b90(0);
        MovieSetTargetTexByName_1d5650((int)arg0, arg1); /* D_004817A8: the GS upload target */
        D_004817E4 = 0;
        /* VoBuf (D_004B3330): +0 slot data base (0xE0000 per slot), +8 tag array (0x48 per
         * tag; +0x40 / +0x44 GIF upload packets), +0x14 slot count */
        w = *(s32 *)(D_004B3210 + 0);
        h = *(s32 *)(D_004B3210 + 4);
        tags = *(u8 **)(D_004B3330 + 8);
        n = *(s32 *)(D_004B3330 + 0x14);
        if (w > 0 && h > 0) {
            for (i = 0; i < n; i++) {
                GsUploadImage16Blocks_1d27a0(*(s32 *)(tags + i * 0x48 + 0x40),
                                             *(s32 *)D_004B3330 + i * 0xE0000, 0, w, h);
                GsUploadImage16Blocks_1d27a0(*(s32 *)(tags + i * 0x48 + 0x44),
                                             *(s32 *)D_004B3330 + i * 0xE0000, 0, w, h);
            }
        }
        *(u8 *)(arg0 + 0x17900) = 1;
    }
}
