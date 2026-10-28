/* rgp:protos */
#define RGP_SELF_InsectMenuChoiceWindowLayout_396fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* lane N4 family: InsectMenuChoiceWindowLayout_396fc0 / InsectMenuChoiceWindowLayout_396fc0 (200 B each).
   Substitutions: 0x8C/0x8C, 0x52/0x80, 0xF8/0xF8. */

typedef struct {
    u8 pad00[0x12];
    s16 f12;
} Obj;

extern u8 D_004E95C0[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 InsectMenuChoiceWindowLayout_396fc0(Obj *o)
{
    UiLayoutWindowFrame_28b8e0(UiGetWidgetSprite_28fe10(D_004E95C0, 0x7533, 0), 0x8C, 0x3C, 2);
    UiSetSpriteW_28fbf0(D_004E95C0, 0x7533, 0, o->f12 + 4);
    UiSetSpriteUvW_28f850(D_004E95C0, 0x7533, 0, o->f12 + 4);
    UiSetSpriteW_28fbf0(D_004E95C0, 0x7532, 0x80, 0);
    UiSetWidgetPos_290f60(D_004E95C0, 0x7532, 0xF8, o->f12 * 27 + 0xA5);
    return 1;
}
