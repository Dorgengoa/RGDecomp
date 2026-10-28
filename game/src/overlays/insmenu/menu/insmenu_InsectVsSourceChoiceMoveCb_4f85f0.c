/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSourceChoiceMoveCb_4f85f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F85F0 -- one call, argument 4 is o->field12 * 31 built as
 * `sll $2, $3, 5 / subu $7, $2, $3` (32x - x).  Unlike the 004EE250 family the
 * second argument is a CONSTANT here, so there is no incoming colour to mask
 * and the function takes one parameter. */
typedef struct {
    u8 pad00[0x12];
    s16 field12;
} Widget;

extern u8 insmenu_D_004FA180[];
/*rgp*/

s32 insmenu_InsectVsSourceChoiceMoveCb_4f85f0(Widget *o)
{
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x5D, 0, o->field12 * 31);
    return 1;
}
