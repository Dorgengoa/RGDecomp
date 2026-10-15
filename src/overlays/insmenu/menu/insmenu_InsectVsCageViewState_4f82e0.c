#include "types.h"

/* insmenu 0x004F82E0 (632 bytes, 160 instructions, 23 calls) -- the page
 * left/right handler: an optional reset pass, then func_28E100 for the button,
 * then two short-circuit `||` chains that decide whether the page moved.
 *
 * PARKED AT 4 WORDS, RIGHT LENGTH.  All four are the same instruction: retail
 * materialises the changed flag with `daddiu $16, $0, 0x1` and we emit `addiu`
 * -- the unsigned-narrow-type class from 004EA000, met here without a callee to
 * widen.  Measured, all six spellings of the flag's type: u32 and u64 and s64
 * give the right length and these 4 words; u16 and u8 give the `daddiu` but add
 * an `andi $2, $16, 0xFFFF` before the `!= 0` test that retail does not have
 * (1 word LONG); s8 and s16 are 2 words long.  So the type that materialises
 * the constant the way retail does is exactly the one that then needs masking
 * at the test, and the type that needs no mask materialises it the other way.
 * The 004EA000 fix -- widen the CALLEE's parameter -- does not reach this
 * instance because the only consumer is a branch.
 *
 * `daddiu $16, $0, 0x1` makes the changed flag a u16 (the 004EA000 rule); the
 * page snapshot in the same register is a separate s16 local, and the two have
 * disjoint live ranges -- the flag is dead from the `lh $16` that loads the
 * snapshot until it is set to 1 on every path out.
 *
 * `changed = 0` is written ONCE after the dispatch: retail duplicates it into
 * the 0x88BF arm's `b` delay slot, which is the ordinary join-store shape.
 */

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];
extern s16 D_00480464;      /* gp - 0x4D0C */
extern u8  D_00484348;      /* gp - 0xE28 */
extern u8  D_004842E8;      /* gp - 0xE88, passed by address */
extern f32 D_0047D460;
extern f32 D_0047D3C8;

extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern void func_28EA90(const void *a, s32 b, s32 c);
extern s32 func_28E100(const void *a, const void *b, const void *c, s32 d);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern s32 func_2F6660(void);
extern s32 func_1839F0(const void *a, s32 b);
extern s32 func_2882C0(void);
extern void insmenu_InsectVsCageViewStepCage_4f8db0(s32 a);
extern void func_376B20(s32 a);
extern s32 insmenu_InsectVsGetLoadedTeam_4f9440(s16 *a);
extern void func_379BE0(s32 a, s32 b, s32 c, s32 d);

s32 insmenu_InsectVsCageViewState_4f82e0(s32 arg0, s32 init)
{
    s16 sp2E;
    u16 changed;
    s16 old;
    s32 hit;
    s32 t;

    if (init != 0) {
        func_291110(D_004FA180, 0x9CA7, 1, 1);
        func_2907A0(D_004FA180, 0x9CA7, 0.0f);
        func_290690(D_004FA180, 0x9CA7, 1.0f, D_0047D460, -1.0f);
        func_28EA90(D_004FA1A0, 0x7534, 0);
    }
    hit = func_28E100(D_004FA1A0, D_004B2570, D_004B27E0, 0);
    if (hit == 1) {
        func_290690(D_004FA180, 0x9CA7, 0.0f, D_0047D3C8, -1.0f);
        if (D_00484348 != 0) {
            func_28EDE0(&D_004842E8, 0x88BF, 0);
        } else {
            func_28EDE0(&D_004842E8, 0x88BE, 0);
        }
    } else if (hit == 2) {
        func_290690(D_004FA180, 0x9CA7, 0.0f, D_0047D3C8, -1.0f);
        func_28EDE0(&D_004842E8, 0x88BF, 0);
    }
    changed = 0;
    if (func_2F6660() == 0) {
        if (func_1839F0(D_004B2570, 8) != 0 ||
            (func_2882C0() != 0 && func_1839F0(D_004B27E0, 8) != 0)) {
            old = D_00480464;
            D_00480464 = old + 1;
            insmenu_InsectVsCageViewStepCage_4f8db0(1);
            if (old != D_00480464) {
                func_376B20(0xB);
            }
            changed = 1;
        } else if (func_1839F0(D_004B2570, 4) != 0 ||
                   (func_2882C0() != 0 && func_1839F0(D_004B27E0, 4) != 0)) {
            old = D_00480464;
            D_00480464 = old - 1;
            insmenu_InsectVsCageViewStepCage_4f8db0(-1);
            if (old != D_00480464) {
                func_376B20(0xB);
            }
            changed = 1;
        }
    }
    if (changed) {
        sp2E = 0;
        t = insmenu_InsectVsGetLoadedTeam_4f9440(&sp2E);
        if (t != 0) {
            func_379BE0(t, D_00480464, sp2E, D_00484348);
        }
    }
    return 1;
}
