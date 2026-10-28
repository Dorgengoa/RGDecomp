/* rg-override: replaces game/src/main/menu/RevelationBoardDrawSprite_34c170.c sha256 c6e43ba719ecb91c42bd036e8b3714b29a6bba20fa0302d8c4761078f6c6bfe0
 * why: register pass-through the stages missed: retail forwards $a0 (board) and $f12-$f19 + the stack float unchanged to 34ce10; the decomp spelled them as uninitialised locals (null board -> crash, BRINGUP item 6) */
/* rgp:protos */
#define RGP_SELF_RevelationBoardDrawSprite_34c170 1
#define RGP_SELF_RevelationBoardPktSetColorLerp_34ce10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* rg-override: real signature (asm 0034C170): a0 board, a1 packet, a2 sprite, a3 x, t0 y,
 * t1 w, t2 h; f12 t, f13-f16 colour from, f17-f19 + stack word colour to -- all forwarded
 * to RevelationBoardPktSetColorLerp_34ce10 as-is (caller RevelationBoardDraw_349e70 already
 * passes 7 ints + 9 floats). */
extern void RevelationBoardPktSetColorLerp_34ce10(void *, s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern s16 D_004539F0[];
extern s16 D_004539F2[];
extern s16 D_004539F4[];
extern s16 D_004539F6[];

void RevelationBoardDrawSprite_34c170(void *board, s32 arg1, s32 idx, s32 x, s32 y, s32 w, s32 h,
                                      f32 t, f32 a0, f32 a1, f32 a2, f32 a3,
                                      f32 b0, f32 b1, f32 b2, f32 b3)
{
    s32 x0;
    s32 y0;
    s32 dw;
    s32 dh;

    x0 = D_004539F0[idx * 4];
    y0 = D_004539F2[idx * 4];
    dw = D_004539F4[idx * 4];
    dh = D_004539F6[idx * 4];
    if (w < 0) {
        w = dw;
    }
    if (h < 0) {
        h = dh;
    }
    RevelationBoardPktSetColorLerp_34ce10(board, arg1, t, a0, a1, a2, a3, b0, b1, b2, b3);
    GsPktSetUV_13ed60(arg1, x0, y0);
    GsPktSetXYZPixel_13f110(arg1, x, y, 0);
    GsPktSetUV_13ed60(arg1, x0 + dw, y0 + dh);
    GsPktSetXYZPixel_13f110(arg1, x + w, y + h, 0);
}
