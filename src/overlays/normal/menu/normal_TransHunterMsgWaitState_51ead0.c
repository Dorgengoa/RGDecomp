#include "types.h"
/* normal 0x0051EAD0 -- posts event 0x15 when the func_28E170 result is 1 or 2.
 * Retail folds the pair into `addiu $2,$2,-1 / sltiu $1,$2,2`, so the source
 * is the two-way equality test. */

extern void *D_0048470C;          /* gp - 0xA64 */
extern void *D_00484720;          /* gp - 0xA50 */
extern const u8 D_004B2570;

extern s32  func_28E170(void *p, const u8 *q, s32 c, s32 d);
extern void func_28EDE0(void *p, s32 id, s32 a);

s32 normal_TransHunterMsgWaitState_51ead0(void)
{
    s32 n;

    n = func_28E170(D_00484720, &D_004B2570, 0, 0);
    if (n == 1 || n == 2) {
        func_28EDE0(D_0048470C, 0x15, 0);
    }
    return 1;
}
