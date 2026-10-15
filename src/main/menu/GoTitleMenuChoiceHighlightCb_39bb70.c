#include "types.h"

extern s32 UiSetSpriteU_28f930(void *, s32, s32, s32);

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
    r0 = UiSetSpriteU_28f930(D_004E9660, 0xC, 0x4C, t0);
    t1 = p0->m10;
    ok = !t1;
    r1 = UiSetSpriteU_28f930(D_004E9660, 0xC, 0x18, ok);
    return 1;
}
