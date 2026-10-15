#include "types.h"

/* title.bin overlay, 0x004EBD00 -- the mode dispatcher.  A four-entry table is
 * COPIED from a gp-relative global into the frame before the mode test, and the
 * non-reset path calls through it.
 *
 * Ã¢Ëœâ…Ã¢Ëœâ…Ã¢Ëœâ… FOUR `lwc1`/`swc1` PAIRS ARE NOT A BLOCK COPY -- they are FOUR SEPARATE
 * `f32` GLOBALS assigned one at a time, and the local they land in is a union
 * of `f32[4]` with the function-pointer array the jalr reads.  Written as one
 * 16-byte struct copy from a single global, mwcc proves both ends qword-aligned
 * and emits ONE `lq`/`sq` -- and because 16 bytes is over the small-data
 * threshold it addresses the source with `lui`/%lo instead of $28, so the copy
 * is 5 words short AND has the wrong relocation.  Four 4-byte externs each keep
 * their own `%gp_rel`, which is what the reference has.
 */

typedef void (*Fn_title_FUN_004ebd00)(void *a);

typedef union Tab_title_FUN_004ebd00 {
    f32 w[4];
    Fn_title_FUN_004ebd00 f[4];
} Tab_title_FUN_004ebd00;

extern f32 D_004803F0;
extern f32 D_004803F4;
extern f32 D_004803F8;
extern f32 D_004803FC;
extern void *D_00484158;
extern void *D_00484170;
extern s32 D_00484164;
extern s16 D_0048417C;
extern s16 D_004841A4;
extern u8 D_004841A8;

extern void func_372D60(void);
extern void func_372F80(void);
extern void title_TitleMovieStop_4f0480(void);
extern void title_TitleMovieRelease_4f0440(void);
extern void func_2907A0(void *a, s32 b, f32 x);
extern s32 func_207F20(void);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 title_TitleStateMain_4ebd00(void *a, void *b)
{
    Tab_title_FUN_004ebd00 t;

    t.w[0] = D_004803F0;
    t.w[1] = D_004803F4;
    t.w[2] = D_004803F8;
    t.w[3] = D_004803FC;
    if (D_004841A4 == 2) {
        func_372D60();
        func_372F80();
        D_004841A8 = 0;
        title_TitleMovieStop_4f0480();
        title_TitleMovieRelease_4f0440();
        D_00484164 = 0;
        D_0048417C = 0;
        D_004841A4 = 0;
        func_2907A0(D_00484170, 2, 0.0f);
        func_2907A0(D_00484170, 1, 0.0f);
        if (func_207F20() != 0) {
            func_28EDE0(D_00484158, 4, 1);
        } else {
            func_28EDE0(D_00484158, 0xE, 1);
        }
    } else {
        t.f[D_0048417C](b);
    }
    return 1;
}
