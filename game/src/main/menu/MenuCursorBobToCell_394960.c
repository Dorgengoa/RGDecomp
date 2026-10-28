/* rgp:protos */
#define RGP_SELF_MenuCursorBobToCell_394960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct P394960 { s16 f0; s16 f2; s16 f4; s16 f6; u8 pad8[8]; s16 f10; s16 f12; };

extern f32 D_0047D3D0 __attribute__((section(".sdata")));
extern f32 D_0047D1FC;
extern f32 D_00483490;
extern u8 D_004E9550[];
/*rgp*/
/*rgp*/

s32 MenuCursorBobToCell_394960(struct P394960 *p0, s32 unused, s32 p2, s32 p3)
{
    f32 t;
    f32 r;
    f32 prod;

    t = D_00483490 + D_0047D3D0;
    D_00483490 = t;
    if (t > 0.0f) {
        D_00483490 = t - D_0047D1FC;
    }

    r = Sinf_128fd0(D_00483490);
    prod = 6.0f * r;
    prod = prod;
    UiMoveWidgetUniform_290f50(D_004E9550, 0xB, (s32)((f32)p2 + (prod + (f32)(p0->f0 + p0->f10 * p0->f4))), p3 + (p0->f2 + p0->f12 * p0->f6), 0.5f, 0
);
    return 1;
}
