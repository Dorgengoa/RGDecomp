#include "types.h"
/* normal 0x00506FC0 -- a gp byte cleared, then a three-argument TAIL CALL with
 * that store in the `j`'s delay slot: the recorded "a store written before a
 * call fills that call's delay slot".  D_00525A10 is OVERLAY data, 0x6C8A0
 * past _gp, so its extern must be `const` or mwcc emits `%gp_rel` and the link
 * dies with a GP offset overflow.
 * One of the 55 unnamed functions. */
extern const u8 D_00525A10[];
extern void func_131B60(const u8 *a, s32 b, s32 c);
extern u8 D_00484570;

void normal_LeaderHudBossGaugeClear_506fc0(void)
{
    D_00484570 = 0;
    func_131B60(D_00525A10, -1, 0x20);
}
