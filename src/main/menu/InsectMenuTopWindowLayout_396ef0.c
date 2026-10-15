#include "types.h"

/* lane N4 family: InsectMenuTopWindowLayout_396ef0 / InsectMenuChoiceWindowLayout_396fc0 (200 B each).
   Substitutions: 0x5E/0x8C, 0x52/0x80, 0x101/0xF8. */

typedef struct {
    u8 pad00[0x12];
    s16 f12;
} Obj;

extern u8 D_004E95C0[];

extern void *UiGetWidgetSprite_28fe10(void *, s32, s32);
extern void UiLayoutWindowFrame_28b8e0(void *, s32, s32, s32);
extern void UiSetSpriteW_28fbf0(void *, s32, s32, s32);
extern void UiSetSpriteUvW_28f850(void *, s32, s32, s32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);

s32 InsectMenuTopWindowLayout_396ef0(Obj *o)
{
    UiLayoutWindowFrame_28b8e0(UiGetWidgetSprite_28fe10(D_004E95C0, 0x7533, 0), 0x5E, 0x3C, 2);
    UiSetSpriteW_28fbf0(D_004E95C0, 0x7533, 0, o->f12 + 4);
    UiSetSpriteUvW_28f850(D_004E95C0, 0x7533, 0, o->f12 + 4);
    UiSetSpriteW_28fbf0(D_004E95C0, 0x7532, 0x52, 0);
    UiSetWidgetPos_290f60(D_004E95C0, 0x7532, 0x101, o->f12 * 27 + 0xA5);
    return 1;
}
