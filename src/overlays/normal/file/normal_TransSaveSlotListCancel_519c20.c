#include "types.h"
/* normal 0x00519C20 -- three-call entry, returns 1.  `$4` is never read. */

extern void *D_004847D8;          /* gp - 0x998 */

extern void func_376B20(s32 a);
extern void normal_TransSavePanelFade_518700(s32 a);
extern void func_28EA90(void *p, s32 id, s32 a);

s32 normal_TransSaveSlotListCancel_519c20(void)
{
    func_376B20(6);
    normal_TransSavePanelFade_518700(2);
    func_28EA90(D_004847D8, 2, 0);
    return 1;
}
