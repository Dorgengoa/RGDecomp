/* rgp:protos */
#define RGP_SELF_GoTitleMenuChoiceHighlightCb_39bb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

extern u8 D_004E9660[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
};

s32 GoTitleMenuChoiceHighlightCb_39bb70(struct Obj0 *p0)
{
    s16 t0;
    s32 r0;
    s16 t1;
    u8 ok;
    s32 r1;

    t0 = p0->m10;
    r0 = ((s32)UiSetSpriteU_28f930(D_004E9660, 0xC, 0x4C, t0));
    t1 = p0->m10;
    ok = !t1;
    r1 = ((s32)UiSetSpriteU_28f930(D_004E9660, 0xC, 0x18, ok));
    return 1;
}
