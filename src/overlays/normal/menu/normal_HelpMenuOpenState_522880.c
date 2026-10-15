#include "types.h"
/* normal 0x00522880 -- the 0x28/0x29/0x2A/0x2B/0x2C widget group's one-shot
 * setup, then a per-frame poll on 0x2A's fade value.
 * ⚠ `$4` is never read: the first parameter leaves no trace.  This is one of
 * the state-handler family (see normal_TransSaveQuitState_51a020) and they are all f(void*, s32).
 * `sw $0, -0x76C($28)` rides in normal_HelpMenuScrollBarLayout_522b90's delay slot, so the
 * zeroing store is written BEFORE the call in source. */

extern const u8 D_00528180;

extern f32 D_0047D7CC;            /* gp - 0x79A4 */
extern f32 D_00484A04;            /* gp - 0x76C  */
extern s32 D_004849F0;            /* gp - 0x780  */
extern s32 D_004849B4;            /* gp - 0x7BC  */
extern s32 D_004849A8;            /* gp - 0x7C8  */

extern s32  func_28AA30(s32 a, s32 b);
extern void func_28EDE0(void *p, s32 id, s32 c);
extern void func_28F300(const u8 *p, s32 id, s32 c, s32 d);
extern void func_28F510(const u8 *p, s32 id, s32 c, s32 d);
extern void func_28F850(const u8 *p, s32 id, s32 c, s32 d);
extern void func_28F970(const u8 *p, s32 id, s32 c, s32 d, s32 e);
extern void func_28FBF0(const u8 *p, s32 id, s32 c, s32 d);
extern void func_290690(const u8 *p, s32 id, f32 x, f32 y, f32 z);
extern f32  func_290770(const u8 *p, s32 id);
extern void func_2907A0(const u8 *p, s32 id, f32 x);
extern void func_290F60(const u8 *p, s32 id, s32 c, s32 d);
extern void func_291110(const u8 *p, s32 id, s32 c, s32 d);
extern f32  normal_HelpMenuScrollBarLayout_522b90(s32 a, s32 b, s32 c, s32 d);
extern void normal_HelpMenuListFill_522e30(s32 a);

s32 normal_HelpMenuOpenState_522880(void *a, s32 b)
{
    s32 i;

    if (b != 0) {
        func_291110(&D_00528180, 0x2A, 1, 1);
        func_290F60(&D_00528180, 0x2A, 0x50, 0x70);
        func_2907A0(&D_00528180, 0x2A, D_0047D7CC);
        func_290690(&D_00528180, 0x2A, 1.0f, D_0047D7CC, -1.0f);
        func_290F60(&D_00528180, 0x29, 0x52, 0x70);
        func_291110(&D_00528180, 0x29, 1, 1);
        func_2907A0(&D_00528180, 0x29, D_0047D7CC);
        func_290690(&D_00528180, 0x29, 1.0f, D_0047D7CC, -1.0f);
        func_290F60(&D_00528180, 0x2C, -0x1A, 6);
        i = 0;
        do {
            func_28FBF0(&D_00528180, 0x2A, 0x14F, i);
            func_28F850(&D_00528180, 0x2A, 4, i);
            i += 1;
        } while (i < 8);
        D_00484A04 = 0.0f;
        D_00484A04 = normal_HelpMenuScrollBarLayout_522b90(0x2B, 0xD8, 8, D_004849F0);
        func_28F970(&D_00528180, 0x2B, 0x80, 0x4C, 0);
        func_28F970(&D_00528180, 0x2B, 0x80, 0x52, 1);
        func_28F970(&D_00528180, 0x2B, 0x80, 0x5A, 2);
        func_290F60(&D_00528180, 0x2B, 0x154, 3);
        normal_HelpMenuListFill_522e30(0);
        func_291110(&D_00528180, 0x28, 1, 1);
        func_28F510(&D_00528180, 0x28, func_28AA30(D_004849B4, 8), 0);
        func_28F300(&D_00528180, 0x28, 0x100, 0);
        func_290F60(&D_00528180, 0x28, 0, 0x14);
        func_2907A0(&D_00528180, 0x28, D_0047D7CC);
        func_290690(&D_00528180, 0x28, 1.0f, D_0047D7CC, -1.0f);
        func_28FBF0(&D_00528180, 0x2A, 0, 0);
        func_28F850(&D_00528180, 0x2A, 0, 0);
        func_290F60(&D_00528180, 0x29, 0x52, 0x70);
    }
    if (!(func_290770(&D_00528180, 0x2A) < 1.0f)) {
        func_28EDE0(&D_004849A8, 0x7538, 1);
    }
    return 1;
}
