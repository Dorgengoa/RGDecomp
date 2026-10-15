#include "types.h"
/* normal 0x0051A360 -- guarded teardown; `$4` is never read.  The `beqz $5`
 * with `sd $31` in the delay slot is the ordinary prologue-merged guard. */

extern void *D_004847D8;          /* gp - 0x998 */
extern void *D_00484714;          /* gp - 0xA5C */
extern const u8 D_004B2570;

extern void func_28EA90(void *p, s32 id, s32 a);
extern void func_37BAC0(s32 a);
extern void func_28E170(void *p, const u8 *q, s32 c, s32 d);
extern void func_3774D0(void *a);

s32 normal_TransSaveMainState_51a360(void *a, s32 b)
{
    if (b != 0) {
        func_28EA90(D_004847D8, 2, 0);
    }
    func_37BAC0(0);
    func_28E170(D_004847D8, &D_004B2570, 0, 0);
    func_3774D0(D_00484714);
    return 1;
}
