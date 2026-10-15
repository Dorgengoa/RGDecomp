#include "types.h"
/* normal 0x00518590 -- tail call through a gp handle. */

extern void *D_00484728;   /* gp - 0xA48 */

extern void func_28C210(void *w, s32 id);

void normal_TransMenuIconClutBuild_518590(void)
{
    func_28C210(D_00484728, 0x32C);
}
