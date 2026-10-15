#include "types.h"
/* normal 0x0050C9A0 -- head of the 0x0050F8E0 pair.  The tested value is
 * func_28E170's result (saved in the `jal` delay slot), not func_28EC60's,
 * whose result is discarded.  ARM A of the range-test spelling: an unsigned
 * biased compare. */
extern u8    D_004B2570[];
extern void *D_004845C4;              /* gp - 0xBAC */
extern void *D_004845D0;              /* gp - 0xBA0 */

extern s32  func_28E170(void *w, const void *p, s32 a, s32 b);
extern s32  func_28EC60(void *w);
extern void func_28EDE0(void *w, s32 id, s32 a);

s32 normal_ShopMenuBuyMsgWaitState_50c9a0(void)
{
    s32 v;

    v = func_28E170(D_004845D0, D_004B2570, 0, 0);
    func_28EC60(D_004845D0);
    if ((u32)(v - 1) < 2) {
        func_28EDE0(D_004845C4, 0x7540, 0);
    }
    return 1;
}
