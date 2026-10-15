#include "types.h"
/* insmenu 0x004EE160 -- the insmenu_FUN_004EC150 shape with a different callee
 * and a non-zero second argument.  The +0x24 deref is written as a cast rather
 * than a struct member because it appears ONCE: the address-CSE defect that
 * forces a real member (see 004ED0F0) only bites on a second use. */
extern void *func_1FEDE0(void);
extern void func_431310(void *a, s32 b);
extern u8 D_00484304;
s32 insmenu_InsectVsBootFinish_4ee160(void)
{
    func_431310(*(void **)((u8 *)func_1FEDE0() + 0x24), 2);
    D_00484304 = 1;
    return 1;
}
