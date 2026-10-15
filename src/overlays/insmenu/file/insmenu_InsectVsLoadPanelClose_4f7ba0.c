#include "types.h"

/* insmenu 0x004F7BA0 -- the 004F5480 block with a leading `func_376B10(0)` and
 * a different tail.  `beqz $5` branches AWAY, so the block is the FALL-THROUGH
 * and the condition is `!= 0`; $4 is never read.
 *
 * ★ `sp1E = 0;` written BEFORE the call fills that call's delay slot, and the
 * same shape repeats for the pair of flag stores that share the constant 1
 * with the call's second argument.
 * ★ The tail guard is `c.le.s $f0, $f1` (f1 = 0.0f) with `bc1fl` branching
 * AWAY, so the body runs on `<= 0.0f` -- the guard polarity of that shape, not
 * the value-producing `> 0.0f` one.
 * ★ The inner `beql`'s delay slot carries the ELSE arm's `addiu $4, $28, K`,
 * the merge target's first instruction duplicated: a plain if/else with the
 * `!= 0` arm as the fall-through.
 */
extern const u8 D_004FA180[];
extern u8  D_00484348;      /* gp - 0xE28 */
extern u8  D_00484350;      /* gp - 0xE20 */
extern s16 D_00480464;      /* gp - 0x4D0C */
extern s16 D_004842E8;      /* gp - 0xE88 */
extern f32 D_0047D3C8;
extern f32 D_0047D460;
extern f32 D_0047D488;
extern f32 D_0047D49C;

extern void func_376B10(s32 a);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern void func_290F50(const void *a, s32 id, s32 c, s32 d, s32 e, f32 x);
extern s32  insmenu_InsectVsGetLoadedTeam_4f9440(s16 *a);
extern void func_379BE0(s32 a, s32 b, s32 c, s32 d);
extern f32  func_290770(const void *a, s32 b);
extern void func_28EDE0(void *a, s32 id, s32 c);

s32 insmenu_InsectVsLoadPanelClose_4f7ba0(s32 unused, s32 a)
{
    s16 sp1E;
    s32 h;

    if (a != 0) {
        func_376B10(0);
        func_290690(D_004FA180, 0x88BA, 0.0f, D_0047D3C8, -1.0f);
        func_290F50(D_004FA180, 0x88BA, 0xC8, 0, 0, D_0047D460);
        func_290690(D_004FA180, 0x88BC, 0.0f, D_0047D3C8, -1.0f);
        func_290F50(D_004FA180, 0x88C1, -0x12, 0xC, 0, D_0047D488);
        func_290F50(D_004FA180, 0x88C0, -0xF, 0xF, 0, D_0047D488);
        func_290690(D_004FA180, 0x88C1, 0.0f, D_0047D49C, -1.0f);
        func_290690(D_004FA180, 0x88C0, 0.0f, D_0047D49C, -1.0f);
        sp1E = 0;
        h = insmenu_InsectVsGetLoadedTeam_4f9440(&sp1E);
        if (h != 0) {
            D_00484350 = 1;
            D_00480464 = 1;
            func_379BE0(h, 1, sp1E, D_00484348);
        }
    }
    if (func_290770(D_004FA180, 0x88BA) <= 0.0f) {
        if (D_00484350 != 0) {
            func_28EDE0(&D_004842E8, 0x88BD, 0);
        } else {
            func_28EDE0(&D_004842E8, 0x88BF, 0);
        }
    }
    return 1;
}
