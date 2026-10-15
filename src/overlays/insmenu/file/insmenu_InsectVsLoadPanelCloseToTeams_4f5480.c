#include "types.h"

/* insmenu 0x004F5480 -- `beqz $5` branches AWAY, so the block is the
 * FALL-THROUGH and the condition is `!= 0`; $4 is never read.
 *
 * ★ The tail guard is `c.le.s $f0, $f1` (f1 = 0.0f) with `bc1fl` branching AWAY
 * to the epilogue, so the branch is taken when the condition is FALSE, i.e.
 * when the value is > 0 -- which means the BODY runs on `<= 0.0f`.  ⚠ Not the
 * recorded `c.le.s + bc1f = > 0.0f` shape: that one is the VALUE-producing
 * form where the flag is materialised as 0/1.  As a guard the polarity is the
 * other way round, and the branch KIND is what distinguishes them.
 *
 * ★ `D_00484354 = 0;` written BEFORE the call fills that call's delay slot.
 * The ids do not fit a signed 16-bit immediate, hence `ori`.
 */
extern const u8 D_004FA180[];
extern u8  D_00484354;      /* gp - 0xE1C */
extern s16 D_004842E8;      /* gp - 0xE88 */
extern f32 D_0047D3C8;
extern f32 D_0047D460;
extern f32 D_0047D488;
extern f32 D_0047D49C;

extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern void func_290F50(const void *a, s32 id, s32 c, s32 d, s32 e, f32 x);
extern f32  func_290770(const void *a, s32 b);
extern void func_28EDE0(void *a, s32 id, s32 c);

s32 insmenu_InsectVsLoadPanelCloseToTeams_4f5480(s32 unused, s32 a)
{
    if (a != 0) {
        func_290690(D_004FA180, 0x88BA, 0.0f, D_0047D3C8, -1.0f);
        func_290F50(D_004FA180, 0x88BA, 0xC8, 0, 0, D_0047D460);
        func_290690(D_004FA180, 0x88BC, 0.0f, D_0047D3C8, -1.0f);
        func_290F50(D_004FA180, 0x88C1, -0x12, 0xC, 0, D_0047D488);
        func_290F50(D_004FA180, 0x88C0, -0xF, 0xF, 0, D_0047D488);
        func_290690(D_004FA180, 0x88C1, 0.0f, D_0047D49C, -1.0f);
        func_290690(D_004FA180, 0x88C0, 0.0f, D_0047D49C, -1.0f);
    }
    if (func_290770(D_004FA180, 0x88BA) <= 0.0f) {
        D_00484354 = 0;
        func_28EDE0(&D_004842E8, 0x88C1, 0);
    }
    return 1;
}
