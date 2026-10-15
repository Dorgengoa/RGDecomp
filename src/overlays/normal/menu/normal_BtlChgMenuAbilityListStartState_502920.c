#include "types.h"
/* normal 0x00502920 -- f(void *, s32) state handler: the whole body is guarded
 * on `b` and every path returns 1. */

extern void *D_00484454;          /* gp - 0xD1C */
extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_004844A0;          /* gp - 0xCD0 */

extern void normal_BtlChgPageScrollReset_5052c0(void *p);
extern void normal_BtlChgPageSetDetailShown_506110(void *p, s32 a);
extern void func_28EDE0(void *w, s32 id, s32 a);
extern void func_28EA90(void *w, s32 id, s32 a);

s32 normal_BtlChgMenuAbilityListStartState_502920(void *a, s32 b)
{
    if (b != 0) {
        normal_BtlChgPageScrollReset_5052c0(D_00484454);
        normal_BtlChgPageSetDetailShown_506110(D_00484454, 0);
        func_28EDE0(D_00484498, 0x55F3, 0);
        func_28EA90(D_004844A0, 0x55F1, 1);
    }
    return 1;
}
