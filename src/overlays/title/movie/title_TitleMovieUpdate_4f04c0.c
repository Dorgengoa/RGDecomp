#include "types.h"

/* title.bin overlay, 0x004F04C0 -- the per-frame step of the attract loop.
 * Two paths reach the same four-call "advance" block and retail emits it
 * TWICE, so it is a helper mwcc inlined at both sites, not a shared label.
 *
 * `bgezl` means the NEGATIVE case is the fall-through, so the `< 0` arm is
 * written first.
 */

extern s32 D_00480430;
extern s32 D_00484288;
extern void *D_00484290;
extern void *D_0048429C;

extern void func_15DE80(void);
extern void func_15DE40(void);
extern s32 func_1D5680(void *a);
extern s32 func_1D52D0(void *a);
extern void func_1D56C0(void *a);
extern void func_1D5810(void *a);
extern void func_1D5870(void *a);
extern void func_1D4B20(void);
extern void func_14D830(void *a);
extern void func_1D52E0(void *a, f32 x);

static inline s32 title_FUN_004f04c0_advance(void)
{
    func_1D56C0(D_00484290);
    func_1D5870(D_00484290);
    func_1D4B20();
    func_14D830(D_0048429C);
    return 1;
}

s32 title_TitleMovieUpdate_4f04c0(void)
{
    D_00484288 = D_00484288 + 1;
    func_15DE80();
    func_15DE40();
    if (D_00480430 < 0) {
        if (func_1D5680(D_00484290) != 0) {
            return title_FUN_004f04c0_advance();
        }
    } else {
        if (func_1D5680(D_00484290) == 0) {
            if (func_1D52D0(D_00484290) < D_00480430) {
                goto idle;
            }
        }
        return title_FUN_004f04c0_advance();
    }
idle:
    func_1D5810(D_00484290);
    func_1D5870(D_00484290);
    func_1D4B20();
    if (D_00484288 == 1) {
        func_1D52E0(D_00484290, 1.0f);
    }
    return 0;
}
