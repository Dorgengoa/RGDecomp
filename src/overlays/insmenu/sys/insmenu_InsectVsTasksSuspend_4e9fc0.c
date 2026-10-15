#include "types.h"
/* insmenu 0x004E9FC0 -- the mirror of insmenu_InsectVsTasksResume_4e9f00: here retail falls
 * through into `b <epilogue> / daddu $2, $0, $0` and branches INTO the body,
 * so the guard is `!= 0` and the body is what follows it.  The `sb` that sets
 * the flag sits in func_27C220's delay slot, which is a store written before
 * the call. */
extern u8 D_00484310;
extern void func_27C220(void);
extern void func_285FF0(void);

s32 insmenu_InsectVsTasksSuspend_4e9fc0(void)
{
    if (D_00484310 != 0) {
        return 0;
    }
    D_00484310 = 1;
    func_27C220();
    func_285FF0();
    return 1;
}
