/* rgp:protos */
#define RGP_SELF_InfoEdgeListCursorCb_399230 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/

s32 InfoEdgeListCursorCb_399230(struct Obj *o)
{
    UiSetSpritePos_28fd10(D_00482360, 0x217, 0x17, o->m02 + o->m12 * o->m06, 0);
    if (D_00483598 == o->m12) {
        UiMoveWidgetUniform_290f50(D_00482360, 0x21B, 0, (s32)((f32)o->m16 * D_00483594), D_0047D460, 0);
        InfoEdgeFillList_398d90(o->m16);
    }
    D_00483598 = o->m12;
    return 1;
}
