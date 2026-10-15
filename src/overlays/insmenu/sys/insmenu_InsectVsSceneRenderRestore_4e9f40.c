#include "types.h"
/* insmenu 0x004E9F40 -- same guard shape as insmenu_InsectVsTasksResume_4e9f00. */
extern u8 D_00484310;
extern void func_288300(void);
extern void func_287B90(s32 a);
s32 insmenu_InsectVsSceneRenderRestore_4e9f40(void)
{
    if (D_00484310 == 0) {
        return 0;
    }
    func_288300();
    func_287B90(1);
    return 1;
}
