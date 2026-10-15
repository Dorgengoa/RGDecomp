#include "types.h"
/* normal 0x0050F8E0 -- tail of the 0x0050C9A0 pair (different event id and an
 * extra func_28D820).  The range test is the biased unsigned compare, the same
 * spelling 0x0050C9A0 closed on; a compiled `switch` costs FOUR extra words. */
extern u8    D_004B2570[];
extern const u8 D_00527E70[];
extern void *D_004845C4;              /* gp - 0xBAC */
extern void *D_004845D0;              /* gp - 0xBA0 */

extern s32  func_28E170(void *w, const void *p, s32 a, s32 b);
extern s32  func_28EC60(void *w);
extern void func_28EDE0(void *w, s32 id, s32 a);
extern void func_28D820(const void *p, s32 id);

s32 normal_ShopMenuSellMsgWaitState_50f8e0(void)
{
    s32 v;

    v = func_28E170(D_004845D0, D_004B2570, 0, 0);
    func_28EC60(D_004845D0);
    if ((u32)(v - 1) < 2) {
        func_28EDE0(D_004845C4, 0x754D, 0);
    }
    func_28D820(D_00527E70, 0x3F);
    return 1;
}
