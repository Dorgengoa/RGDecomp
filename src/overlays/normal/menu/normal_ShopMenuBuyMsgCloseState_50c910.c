#include "types.h"
/* normal 0x0050C910 -- the 0x70 widget's UNGUARDED fade-out + result post.
 * Same f(void *, s32) family as src/wf/normal/normal_FUN_0050F880.c ($4 and
 * $5 never read, returns 1), but with no `b` guard, so the scheduler is free
 * to hoist into the prologue -- `lui $2,0xBF80` issues BEFORE the `sd $31`.
 *
 * ** The middle float is a LITERAL, not `extern f32 D_0047D4BC`. **
 * 0x0047D4BC is inside mwcc's .lit4 pool (see scripts/t_lit4.py).  With the
 * extern spelling mwcc pins the `lwc1` at its use and emits
 * [mtc1 $f14, lw $4, lwc1 $f13, mtc1 $f12] -- two words wrong, and TWELVE
 * other spellings (named handle/temp both orders, const/volatile extern,
 * id signedness, four prototype GPR/FPR interleavings, hoisting the
 * func_28EA40 result) all produce the SAME object.  The literal has no alias
 * hazard, hoists freely, and gives retail's [lwc1, lw $4, mtc1 $f14, mtc1
 * $f12] exactly.
 *
 * The three-term test is a short-circuit `||` chain: `beql` and `beqz` jump
 * INTO the then arm and the LAST term's `bnel` jumps PAST it into the else.
 * D_00484630 is read INLINE twice (two `lbu -0xB40($28)`), not hoisted into a
 * local -- hoisting it costs three words.  The two `lw -0xBAC($28)` are the
 * scheduler filling the branch delay slots.
 */

typedef struct Meta { u8 pad00[0x14]; s16 f14; } Meta;

extern u8    D_00484630;          /* gp - 0xB40  */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern void *D_004845D0;          /* gp - 0xBA0  */

extern Meta *func_28EA40(void *ctx, s32 id);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);

s32 normal_ShopMenuBuyMsgCloseState_50c910(void *a, s32 b)
{
    func_290690(D_004845CC, 0x70, 0.0f, -0.1f, -1.0f);
    if (func_28EA40(D_004845D0, 0x7533)->f14 == 0 ||
        D_00484630 == 0 || D_00484630 == 0xC) {
        func_28EDE0(D_004845C4, 0x753A, 0);
    } else {
        func_28EDE0(D_004845C4, 0x7539, 0);
    }
    return 1;
}
