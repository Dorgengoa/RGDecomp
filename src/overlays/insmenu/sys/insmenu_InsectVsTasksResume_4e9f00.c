#include "types.h"
/* insmenu 0x004E9F00 -- guard polarity, the `return 0` case: retail branches
 * INTO the body (`bnez $2, <body>`) and lets the exit fall through as
 * `b <epilogue> / daddu $2, $0, $0`, so the source is the INVERTED early
 * return, not `if (flag) { ...; return 1; } return 0;`. */
extern u8 D_00484310;
extern void func_27C250(void);
s32 insmenu_InsectVsTasksResume_4e9f00(void)
{
    if (D_00484310 == 0) {
        return 0;
    }
    func_27C250();
    D_00484310 = 0;
    return 1;
}
