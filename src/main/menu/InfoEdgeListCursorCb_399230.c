#include "types.h"

struct Obj {
    u8 pad00[0x2];
    s16 m02;
    u8 pad04[0x2];
    s16 m06;
    u8 pad08[0xA];
    s16 m12;
    u8 pad14[0x2];
    s16 m16;
};

extern void *D_00482360 __attribute__((section(".sdata")));
extern s16 D_00483598 __attribute__((section(".sdata")));
extern f32 D_00483594 __attribute__((section(".sdata")));
extern f32 D_0047D460 __attribute__((section(".sdata")));

extern void UiSetSpritePos_28fd10(void *a, s32 b, s32 c, s32 d, s32 e);
extern void UiMoveWidgetUniform_290f50(void *a, s32 b, s32 c, s32 d, s32 e, f32 f);
extern void InfoEdgeFillList_398d90(s32 a);

s32 InfoEdgeListCursorCb_399230(struct Obj *o)
{
    UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, o->m02 + o->m12 * o->m06, 0);
    if (D_00483598 == o->m12) {
        UiMoveWidgetUniform_290f50(D_00482360, 0x21B, 0, (s32)((f32)o->m16 * D_00483594), 0, D_0047D460);
        InfoEdgeFillList_398d90(o->m16);
    }
    D_00483598 = o->m12;
    return 1;
}
