#include "types.h"
/* insmenu 0x4EDBF0 -- fetch a handle, pass its +0x24 member on, latch
 * the gp byte flag.  `addiu $2, $0, 0x1` feeds BOTH the `sb`
 * and the return register, so the stored value and the returned
 * value are the same constant. */
extern void *func_1FEDE0(void);
extern void func_430BF0(void *a, s32 b);
extern u8 D_00484304;
s32 insmenu_InsectVsStateAdvance_4edbf0(void)
{
    func_430BF0(*(void **)((u8 *)func_1FEDE0() + 0x24), 0);
    D_00484304 = 0x1;
    return 0x1;
}
