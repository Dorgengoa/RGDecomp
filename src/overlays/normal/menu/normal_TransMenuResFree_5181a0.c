#include "types.h"
/* normal 0x005181A0 -- one call, `return 1`. */

extern void *D_00484788;          /* gp - 0x9E8 */

extern void func_28B0F0(void *w, s32 a);

s32 normal_TransMenuResFree_5181a0(void)
{
    func_28B0F0(D_00484788, 1);
    return 1;
}
