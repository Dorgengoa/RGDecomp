/* rgp:protos */
#define RGP_SELF_normal_TransHunterMsgWaitState_51ead0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051EAD0 -- posts event 0x15 when the func_28E170 result is 1 or 2.
 * Retail folds the pair into `addiu $2,$2,-1 / sltiu $1,$2,2`, so the source
 * is the two-way equality test. */

extern void *D_0048470C;          /* gp - 0xA64 */
extern void *D_00484720;          /* gp - 0xA50 */
extern u8 D_004B2570;

/*rgp*/
/*rgp*/

s32 normal_TransHunterMsgWaitState_51ead0(void)
{
    s32 n;

    n = MenuGridCursorInput_28e170(D_00484720, &D_004B2570, 0, 0);
    if (n == 1 || n == 2) {
        StateMachineSetState_28ede0(D_0048470C, 0x15, 0);
    }
    return 1;
}
