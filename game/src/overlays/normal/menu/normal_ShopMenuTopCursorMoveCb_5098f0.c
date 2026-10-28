/* rgp:protos */
#define RGP_SELF_normal_ShopMenuTopCursorMoveCb_5098f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005098F0 -- the selected/unselected pass over the two 0x9+i rows of
 * normal_D_00527C40.  The id `i + 9` is used TWICE, so it is a u16 LOCAL (its mask
 * lands in a callee-saved register); `i + 0x16` is single-use and inline.
 * The two float constants are branch-dependent, which is why the (s32) casts
 * are real cvt.w.s and not folded. */
typedef struct Box   { u8 pad00[4]; s16 f04; s16 f06; u8 pad08[4]; s16 f0C; s16 f0E; } Box;
typedef struct Gauge { u8 pad00[8]; s16 f08; } Gauge;
typedef struct Hold  { u8 pad00[0x20]; void *f20; } Hold;
typedef struct Obj   { u8 pad00[0x12]; s16 f12; } Obj;

extern u8 normal_D_00527C40[];
extern f32 D_0047D240;                /* gp - 0x7F30 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuTopCursorMoveCb_5098f0(Obj *o)
{
    Box   *bx;
    Gauge *g;
    s32    i;
    f32  a;
    f32  b;
    u16  k;

    for (i = 0; i < 2; i++) {
        k = i + 9;
        bx = (Box *)((Hold *)UiFindWidget_290460(normal_D_00527C40, k))->f20;
        if (o->f12 == i) {
            bx->f0E = 0;
            bx->f0C = 0;
            bx->f06 = 0;
            bx->f04 = 0;
            a = 43.0f;
            b = 115.0f;
            UiSetWidgetParent_2911a0(normal_D_00527C40, 8, k);
            UiSetWidgetsVisibleById_291110(normal_D_00527C40, 8, 1, 1);
        } else {
            bx->f04 = 0x70;
            bx->f06 = 0x1B;
            bx->f0E = 4;
            bx->f0C = 4;
            a = 33.0f;
            b = 147.0f;
        }
        UiMoveWidgetUniform_290f50(normal_D_00527C40, k, (s32)a, i * 38 + 0x32, D_0047D240, 0);
        UiMoveWidgetUniform_290f50(normal_D_00527C40, i + 6, (s32)(3.0f + a), i * 38 + 0x35, D_0047D240, 0);
        g = (Gauge *)((Hold *)UiFindWidget_290460(normal_D_00527C40, i + 0x16))->f20;
        g->f08 = b;
    }
    return 1;
}
