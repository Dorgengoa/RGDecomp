/* rgp:protos */
#define RGP_SELF_normal_InsectEntryNoFundsMsgState_523330 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00523330 -- optional 0x7532 push, then the 0x4B2570 text-device
 * open/close pair; the `sltiu $1,$2,2` tail is the two-value range test on
 * the open's result. */

extern u8 normal_D_005281C0[];
extern u8 D_004B2570[];

extern s32 D_004849A8;            /* gp - 0x7C8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_InsectEntryNoFundsMsgState_523330(void *a, s32 b)
{
    s32 r;

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(normal_D_005281C0, 0x7532, 1);
    }
    r = MenuGridCursorInput_28e170(normal_D_005281C0, D_004B2570, 0, 0);
    UiEntryListGetCurrentData_28ec60(normal_D_005281C0);
    if (r == 1 || r == 2) {
        StateMachineSetState_28ede0(&D_004849A8, 0x7536, 1);
    }
    return 1;
}
