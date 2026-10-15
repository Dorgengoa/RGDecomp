#include "types.h"

/* insmenu 0x004F6410 (80 bytes, 20 instructions, 5 calls) -- leave the detail
 * pane: drop the page, clear every selector, reset the flag.  The `sb $0` is
 * written BEFORE the call it shares a delay slot with.
 */

extern u8 D_00484390;       /* gp - 0xDE0 */

extern void func_37B460(s32 a);
extern void func_37B800(s32 a);
extern void insmenu_InsectVsSaveListRefresh_4ebc30(s32 a, s32 b);
extern void func_37B9E0(s32 a);
extern void insmenu_InsectVsSaveShowMsg_4f6e00(s32 a, s32 b, s32 c);

s32 insmenu_InsectVsLoadCardScanEnterCb_4f6410(void)
{
    func_37B460(0x890D);
    func_37B800(-1);
    insmenu_InsectVsSaveListRefresh_4ebc30(0, 0);
    D_00484390 = 0;
    func_37B9E0(0);
    insmenu_InsectVsSaveShowMsg_4f6e00(3, 0, -1);
    return 1;
}
