#include "types.h"

/* title.bin overlay, 0x004EAD40 -- one of the two attract-demo drivers.
 * title_FUN_004EAB10 is THE SAME FUNCTION in 139 of its 140 words, differing
 * only in the idle timeout (0x112E here, 0x3C6E there), so the two sources are
 * kept deliberately identical apart from that constant.
 *
 * The five pad polls all branch to the same block, so they are one `||` chain;
 * the fifth is `poll && D_0048416C`, which is why only it falls through the
 * extra halfword test. *
 * PARKED at 14 words, the same two clusters as title_FUN_004EBAF0 and in the
 * same places -- see that file for everything measured.  Written now so that
 * cracking the class lands all three at once.
 */

extern s16 D_0048416C;
extern s32 D_00484164;
extern s16 D_00484194;
extern s16 D_00484198;
extern void *D_00484154;
extern void *D_00484158;
extern void *D_00484160;
extern void *D_00484170;
extern s16 D_0048417C;
extern s16 D_00484188;
extern s16 D_0048418C;
extern f32 D_004803B0;
extern f32 D_004803B4;
extern void *D_004803D0;
extern f32 D_0047D56C;
extern const u8 D_004B2570;
extern void *const D_004F1400;

extern f32 func_290770(void *a, s32 b);
extern void func_291110(void *a, s32 b, s32 c, s32 d);
extern s32 func_1839F0(void *a, s32 b);
extern void *func_1F5BE0(void);
extern void func_1CF730(void *a, s32 b, f32 x, f32 y, f32 z);
extern s32 title_TitleMovieUpdate_4f04c0(void);
extern void title_TitleMovieRelease_4f0440(void);
extern void title_TitleMovieStop_4f0480(void);
extern void title_TitleMenuWidgetsSetup_4ece80(void *a, void *b);
extern void title_TitleMoviePlay_4f0600(void *a, void *b, s32 c, void *d);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 title_TitleAttractMovieTick_4ead40(s32 a)
{
    s32 m;
    s16 n;

    if (a != 0) {
        if (func_290770(D_00484170, 1) > 0.0f) {
            func_291110(D_00484170, 1, 0, 1);
        }
        D_0048416C = 0;
        D_00484164 = 0;
    }
    if (func_1839F0((void *)&D_004B2570, 0x10) != 0 ||
        func_1839F0((void *)&D_004B2570, 0x40) != 0 ||
        func_1839F0((void *)&D_004B2570, 0x80) != 0 ||
        func_1839F0((void *)&D_004B2570, 0x20) != 0 ||
        (func_1839F0((void *)&D_004B2570, 0x800) != 0 && D_0048416C != 0)) {
        if (D_00484198 == 0) {
            func_1CF730(func_1F5BE0(), 0xA, 0.0f, 0.0f, 0.0f);
            D_00484198 = 1;
        }
    }
    if (D_00484164 >= 0x112E) {
        D_0048416C = 0;
    } else if (D_00484164 > 0xA && D_0048416C == 0) {
        D_0048416C = 1;
    }
    if (D_00484198 < 0xC) {
        if (title_TitleMovieUpdate_4f04c0() != 0) {
            title_TitleMovieRelease_4f0440();
            D_004803B0 = 1.0f;
            D_004803B4 = D_0047D56C;
            D_00484194 = 0;
            D_00484198 = 0;
            D_00484164 = 0;
            title_TitleMenuWidgetsSetup_4ece80(D_00484160, D_00484170);
            D_00484188 = 0;
            D_0048418C = 0;
            D_0048417C = 0;
            title_TitleMoviePlay_4f0600(D_004F1400, D_00484154, 1, D_004803D0);
        } else {
            D_00484164 = D_00484164 + 1;
        }
    }
    if (D_00484198 != 0) {
        m = D_00484198 + 1;
        n = m;
        D_00484198 = m;
        if (n > 0xE) {
            D_0048417C = 0;
            func_28EDE0(D_00484158, 4, 1);
            D_00484198 = 0;
        } else if (n == 0xC) {
            title_TitleMovieStop_4f0480();
            title_TitleMovieRelease_4f0440();
            D_00484164 = 0;
        }
    }
    return 1;
}
