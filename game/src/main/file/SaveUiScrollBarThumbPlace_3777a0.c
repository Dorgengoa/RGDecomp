/* rgp:protos */
#define RGP_SELF_SaveUiScrollBarThumbPlace_3777a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct P {
    u8 pad000[0x16];
    s16 m16;
};

/*rgp*/
/*rgp*/

extern s32 D_004831D4;
extern f32 D_004831DC;

void SaveUiScrollBarThumbPlace_3777a0(struct P *p0, s32 p1, s32 mode)
{
    f32 v;

    if (D_004831D4 == 0) {
        return;
    }
    v = 0.0f + 76.0f + D_004831DC * (f32)p0->m16;
    if (mode != 0) {
        UiMoveWidgetUniform_290f50(D_004831D4, p1, 0x1E9, (s32)v, 0.25f, 0);
    } else {
        UiSetWidgetPos_290f60(D_004831D4, p1, 0x1E9, (s32)v);
    }
}
