/* rgp:protos */
#define RGP_SELF_title_TitleOptionsTick_4efdd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EFDD0 -- open a dialog, then dispatch on two
 * different results.  The first test is on a SIGN-EXTENDED halfword
 * (`dsll32`/`dsra32`), so it reads a s16-returning accessor; the other two are
 * on the 32-bit result kept in $17.
 *
 * The `bnel` delay slot carries the NEXT guard's constant, not a return value,
 * so this is an ordinary else-if chain.  Two arms share a body and retail
 * emits it twice.
 */

typedef struct Obj_title_FUN_004efdd0 {
    u8 pad000[0x10];
    s16 field010;      /* +0x10 */
    s16 field012;      /* +0x12 */
} Obj_title_FUN_004efdd0;

extern void *D_00484250;
extern void *D_00484258;
extern u8 D_004B2570;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleOptionsTick_4efdd0(s32 a, s32 b)
{
    s32 r;
    Obj_title_FUN_004efdd0 *o;

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(D_00484258, 0x7536, 0);
        UiEntryListFindByTag_28ea40(D_00484258, 0x7536);
    }
    r = MenuGridCursorInput_28e170(D_00484258, (void *)&D_004B2570, 4, 0);
    o = ((Obj_title_FUN_004efdd0 *)UiEntryListGetCurrentData_28ec60(D_00484258));
    if (title_TitleGetCardChangeState_4ed370() == 2) {
        StateMachineSetState_28ede0(D_00484250, 0xD, 0);
    } else if (r == 2) {
        StateMachineSetState_28ede0(D_00484250, 0xD, 0);
    } else if (r == 1) {
        title_TitleOptionsToggle_4ef3f0(o->field010, o->field012);
    }
    return 1;
}
