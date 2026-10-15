#include "types.h"
/* insmenu 0x004E9F80 -- same guard shape again; here the argument setup for
 * the first call fills the guard's delay slot, which is why the branch is the
 * likely form. */
extern u8 D_00484310;
extern void func_287B90(s32 a);
extern void func_288340(void);
s32 insmenu_InsectVsSceneRenderHide_4e9f80(void)
{
    if (D_00484310 == 0) {
        return 0;
    }
    func_287B90(0);
    func_288340();
    return 1;
}
