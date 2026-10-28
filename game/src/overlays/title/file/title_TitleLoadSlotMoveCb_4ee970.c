/* rgp:protos */
#define RGP_SELF_title_TitleLoadSlotMoveCb_4ee970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE970 -- two sibling overlay calls taking halfword
 * fields, then a call taking the object itself.
 *
 * ★ This is the caller that shows title_TitleLoadHighlightOption_4ede30 and title_TitleLoadSlotListRefreshMaybe_4edeb0
 * take an s16, not a pointer: both are reached with `lh $4, ...`.  Their
 * units were byte-identical with the wrong parameter type -- a pass-through
 * argument leaves no trace in the caller.
 */

typedef struct Obj_title_FUN_004ee970 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
    u8 pad014[0x2];
    s16 field016;      /* +0x16 */
} Obj_title_FUN_004ee970;

/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleLoadSlotMoveCb_4ee970(Obj_title_FUN_004ee970 *o)
{
    title_TitleLoadHighlightOption_4ede30(o->field012);
    title_TitleLoadSlotListRefreshMaybe_4edeb0(o->field016);
    SaveUiScrollBarThumbPlace_3777a0(o, 0x45, 1);
    return 1;
}
