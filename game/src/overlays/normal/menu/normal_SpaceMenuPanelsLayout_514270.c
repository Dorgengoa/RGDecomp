/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuPanelsLayout_514270 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00514270 -- session 31 lane n31c, FRESH.
 * Lays out two 3x3 grids of cells (holds 0x21 and 0x22).  Row j==1 gets a
 * width/height pair, row j==2 derives its x from row 1's width * scale.
 * The `mtc1 $0,$f1` hoisted into the second loop's preheader is the
 * ACCUMULATOR idiom for `x + y*z` ([[ps2-float-accumulator]]), not a real
 * 0.0f in the source.  `lwc1 $f3,-0xC($14)` / `lh $13,-0x6($14)` are the
 * PREVIOUS cell's f14/f1A folded onto the (k + j*3) index. */

typedef struct Cell {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8  pad08[8];
    f32 f10;
    f32 f14;
    s16 f18;
    s16 f1A;
    u8  pad1C[4];
} Cell;

typedef struct Hold { u8 pad00[0x20]; Cell *f20; } Hold;

extern f32 D_0047D7C4;            /* gp - 0x79AC */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_SpaceMenuPanelsLayout_514270(void *a)
{
    Cell *p;
    s32   j;
    s32   k;
    s32   n;
    s32   t;

    p = ((Hold *)UiFindWidget_290460(a, 0x21))->f20;
    for (j = 0; j < 3; j++) {
        for (k = 0; k < 3; k++) {
            n = k + j * 3;
            if (j == 2) {
                t = (s32)(p[k + 3].f10 * (f32)p[k + 3].f18);
            } else {
                t = 0;
            }
            p[(s32)n].f00 = (s16)(t + (p[(s32)k].f00 + p[(s32)k].f04));
            p[(s32)n].f02 = (s16)(k * 11);
            if (j == 1) {
                p[(s32)n].f10 = 14.0f;
                p[(s32)n].f14 = 0.0f;
                p[(s32)n].f18 = 10;
                p[(s32)n].f1A = 0;
            }
        }
    }
    UiSetWidgetPos_290f60(a, 0x21, -0x12C, 0x31);
    UiMoveWidgetUniform_290f50(a, 0x21, -0x14, 0x31, D_0047D7C4, 0);
    p = ((Hold *)UiFindWidget_290460(a, 0x22))->f20;
    for (j = 0; j < 3; j++) {
        for (k = 0; k < 3; k++) {
            n = k + j * 3;
            if (j == 2) {
                t = (s32)(p[k + 3].f10 * (f32)p[k + 3].f18);
            } else {
                t = 0;
            }
            p[(s32)n].f00 = (s16)(t + (p[(s32)k].f00 + p[(s32)k].f04));
            if (k == 2) {
                t = (s32)((f32)p[k].f06
                          + p[n - 1].f14 * (f32)p[n - 1].f1A);
            } else {
                t = k * 10;
            }
            p[(s32)n].f02 = (s16)(p->f02 + t);
            if (j == 1) {
                if (k == 1) {
                    p[(u32)n].f10 = 30.0f;
                    p[(u32)n].f14 = 9.0f;
                    p[(u32)n].f18 = 10;
                    p[(u32)n].f1A = 10;
                } else {
                    p[(u32)n].f10 = 30.0f;
                    p[(u32)n].f14 = 0.0f;
                    p[(u32)n].f18 = 10;
                    p[(u32)n].f1A = 0;
                }
            } else if (k == 1) {
                p[(u32)n].f10 = 0.0f;
                p[(u32)n].f14 = 9.0f;
                p[(u32)n].f18 = 0;
                p[(u32)n].f1A = 10;
            }
        }
    }
    UiSetWidgetPos_290f60(a, 0x22, 0x214, 0x140);
    UiSetSpriteW_28fbf0(a, 0x23, 0x120, 1);
    UiSetSpriteX_28fcd0(a, 0x23, 0x138, 2);
    UiMoveWidgetUniform_290f50(a, 0x22, 0xA5, 0x140, D_0047D7C4, 0);
    return 0;
}
