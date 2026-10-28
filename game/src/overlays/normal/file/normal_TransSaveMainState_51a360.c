/* rgp:protos */
#define RGP_SELF_normal_TransSaveMainState_51a360 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051A360 -- guarded teardown; `$4` is never read.  The `beqz $5`
 * with `sd $31` in the delay slot is the ordinary prologue-merged guard. */

extern void *D_004847D8;          /* gp - 0x998 */
extern void *D_00484714;          /* gp - 0xA5C */
extern u8 D_004B2570;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSaveMainState_51a360(void *a, s32 b)
{
    if (b != 0) {
        UiEntryListSelectByTag_28ea90(D_004847D8, 2, 0);
    }
    SaveStepAndGetStatus_37bac0(0);
    MenuGridCursorInput_28e170(D_004847D8, &D_004B2570, 0, 0);
    SaveProgressBarUpdate_3774d0(D_00484714);
    return 1;
}
