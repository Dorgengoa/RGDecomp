#include "types.h"

/* title.bin overlay, 0x004EE2C0 -- the title menu's per-frame step.  A five-arm
 * dispatch on the phase counter D_0048420C plus a pad-state gate in front of it.
 *
 * THE TWO DISPATCHES ARE DIFFERENT CONSTRUCTS AND THE DELAY SLOTS SAY WHICH.
 * The phase dispatch compares 4,3,2,1,0 -- DESCENDING -- and every converted
 * `beql` carries a CASE BODY'S first instruction (`addiu $4,$0,5`,
 * `addiu $4,$28,-0xF60`, `addiu $4,$0,0x15`, `lw $3,-0xF74`), so it is a
 * `switch` written in ASCENDING case order, which is the recorded reversal.
 * The two guard chains inside state 3, by contrast, carry the NEXT GUARD'S
 * CONSTANT (`addiu $3,$0,5`) or nothing, and are `||` chains in source order.
 *
 * `addiu $2,$16,-0x2 / sltiu $1,$2,0x2` is mwcc range-optimising `k == 2 ||
 * k == 3`; it is compiler output, not a source-level range test.  It does NOT
 * fold the adjacent `k == 5 || k == 6` in the same chain.
 *
 * The phase counter is READ TWICE, once for the gate and once for the switch:
 * the `beql`'s delay slot at 0x004EE2D4 re-issues `lw $3, -0xF64($28)` even on
 * the path with no intervening call, so the gate holds it in a local and the
 * switch reads the global again.
 *
 * `andi $2, $2, 0xFF` after func_37B9B0 makes its return a `u8` -- the mask is
 * the discriminator, not the semantics.
 */

typedef struct Buf_title_FUN_004ee2c0 {
    u8 pad00[0x70];
} Buf_title_FUN_004ee2c0;

extern void *D_004841E0;
extern void *D_004841E8;
extern s16 D_004841F0;
extern s32 D_004841FC;
extern s32 D_00484200;
extern s32 D_0048420C;
extern s32 D_00484210;
extern const u8 D_004B2570;

extern s32 func_37B970(void);
extern u8 func_37B9B0(s32 a);
extern void func_37B9E0(s32 a);
extern s32 func_37BAA0(void);
extern void func_37B460(s32 a);
extern void func_376B20(s32 a);
extern void func_377180(s32 *a);
extern s32 func_1839F0(const u8 *a, s32 b);
extern void func_28EA90(void *a, s32 b, s32 c);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void func_373840(Buf_title_FUN_004ee2c0 *a, s32 b);
extern void func_1319A8(s32 a, Buf_title_FUN_004ee2c0 *b, s32 c);
extern void title_TitleLoadShowMsg_4eeb60(s32 a);
extern void title_TitleLoadShowError_4eeb70(s32 a);
extern void title_TitleLoadYesNoCursorBob_4edc00(s32 a, s32 b, s32 c);
extern void title_TitleLoadProgressWindowShow_4ede10(s32 a, s32 b);
extern s32 title_TitleGetSaveCtx_4ef380(void);
extern s32 title_TitleGetLoadSysMsgBuf_4ef390(void);

s32 title_TitleLoadConfirmCb_4ee2c0(void)
{
    Buf_title_FUN_004ee2c0 sp20;
    s32 t;
    s32 k;

    t = D_0048420C;
    if ((t != 4) && (t != 3)) {
        k = func_37B970();
        if ((func_37B9B0(1) == 0) || (k == 6) || (k == 5) || (k == 8)) {
            title_TitleLoadShowError_4eeb70(8);
            return 1;
        }
    }
    switch (D_0048420C) {
    case 0:
        title_TitleLoadShowMsg_4eeb60(0x15);
        D_00484210 = 0;
        title_TitleLoadYesNoCursorBob_4edc00(0, 1, 1);
        func_37B460(0x43);
        D_0048420C = D_0048420C + 1;
        break;
    case 1:
        func_377180(&D_00484210);
        title_TitleLoadYesNoCursorBob_4edc00(D_00484210, 0, 1);
        if ((func_1839F0(&D_004B2570, D_00484200) != 0)
            || ((func_1839F0(&D_004B2570, D_004841FC) != 0)
                && (D_00484210 == 1))) {
            title_TitleLoadYesNoCursorBob_4edc00(D_00484210, 0, 0);
            func_376B20(6);
            title_TitleLoadShowMsg_4eeb60(-1);
            func_28EA90(D_004841E8, 0x7534, 0);
        } else if (func_1839F0(&D_004B2570, D_004841FC) != 0) {
            title_TitleLoadYesNoCursorBob_4edc00(D_00484210, 0, 0);
            func_376B20(5);
            D_0048420C = D_0048420C + 1;
        }
        break;
    case 2:
        func_37B9E0(5);
        title_TitleLoadProgressWindowShow_4ede10(2, 1);
        title_TitleLoadShowMsg_4eeb60(7);
        D_0048420C = D_0048420C + 1;
        break;
    case 3:
        if (func_37BAA0() != 0) {
            title_TitleLoadProgressWindowShow_4ede10(2, 0);
            k = func_37B970();
            if ((k == 0) && (func_37B9B0(0) == 1)) {
                func_376B20(0x23);
                title_TitleLoadShowMsg_4eeb60(0x16);
                func_373840(&sp20, title_TitleGetSaveCtx_4ef380());
                func_1319A8(title_TitleGetLoadSysMsgBuf_4ef390(), &sp20, 0x70);
                D_0048420C = D_0048420C + 1;
            } else if ((k == 5) || (k == 6) || (k == 8) || (k == 2)
                       || (k == 3)) {
                title_TitleLoadShowError_4eeb70(0xE);
            } else if (k == 1) {
                title_TitleLoadShowError_4eeb70(1);
            } else {
                title_TitleLoadShowError_4eeb70(5);
            }
        }
        break;
    case 4:
        if (func_1839F0(&D_004B2570, D_004841FC | D_00484200) != 0) {
            title_TitleLoadShowMsg_4eeb60(-1);
            D_004841F0 = 1;
            func_28EDE0(D_004841E0, 9, 0);
        }
        break;
    }
    return 1;
}
