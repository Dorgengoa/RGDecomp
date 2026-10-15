#include "types.h"
/* normal 0x005181D0 -- the gameplay scene's menu registration: three state
 * gates on D_00484788, then the 0x526730..0x5267F0 descriptor blocks are
 * handed one at a time to the menu built on func_28B270's handle, the scene
 * widgets are brought up by normal_TransMenuLayoutBuild_516e20, and the gate is armed.
 *
 * FOUR early exits and EVERY one of them materialises its own `daddu $2,$0,$0`
 * in its own delay slot -- so all four are `return 0`, not `break`s into a
 * shared tail (main-pass31 section 1: count the exits).  The last path's
 * `addiu $2,$0,1` is SHARED between the D_00484750 store and the return.
 *
 * `daddu $16,$2,$0` sits in func_206A40's DELAY SLOT and captures
 * func_28B270's result, not func_206A40's.
 * `addiu $5,$0,2 / daddu $6,$5,$0` is mwcc sharing the constant between
 * arguments 2 and 3, not two source constants.
 * The `lw $4,-0x9E8($28)` in each `bnel`'s likely slot is the NEXT block's
 * argument load hoisted into the slot, not part of the guard. */

extern const u8 D_00526730[];
extern const u8 D_00526748[];
extern const u8 D_00526758[];
extern const u8 D_00526770[];
extern const u8 D_00526790[];
extern const u8 D_005267B0[];
extern const u8 D_005267D0[];
extern const u8 D_005267F0[];

extern void *D_004846E0;          /* gp - 0xA90 */
extern s16   D_00484750;          /* gp - 0xA20 */
extern s32   D_00484770;          /* gp - 0xA00 */
extern s32   D_00484774;          /* gp - 0x9FC */
extern void *D_00484788;          /* gp - 0x9E8 */

extern s32   func_28B220(void *a);
extern s32   func_28B210(void *a);
extern s32   func_28B2E0(void *a);
extern void *func_28B270(void *a, s32 *b);
extern void  func_28B230(void *a);
extern void *func_206A40(void);
extern void  func_42B840(void *a, s32 b, s32 c, void *d, void *e);
extern s32   func_202A50(void *a, const void *b, void *c);
extern void *func_1C2800(void *a, const void *b, s32 *c);
extern void  func_376B40(void *a, void *b, s32 c);
extern void  func_202BE0(void *a, const void *b, void *c, s32 d, s32 e);
extern void  normal_TransMenuLayoutBuild_516e20(void);

s32 normal_TransMenuResPoll_5181d0(void)
{
    void *h;
    void *ob;
    void *ctx;
    s32   sel;

    h = D_004846E0;
    if (func_28B220(D_00484788) == -1) {
        return 0;
    }
    if (func_28B210(D_00484788) == 0) {
        return 0;
    }
    if (func_28B2E0(D_00484788) == 1) {
        ob = func_28B270(D_00484788, &sel);
        ctx = func_206A40();
        func_42B840(ctx, 2, 2, h, ob);
        D_00484770 = func_202A50(ob, D_00526730, h);
        D_00484774 = func_202A50(ob, D_00526748, h);
        func_376B40(h, func_1C2800(ob, D_00526758, &sel), sel);
        func_202BE0(ob, D_00526770, h, 0x32D, 0);
        func_202BE0(ob, D_00526790, h, 0x32D, 0);
        func_202BE0(ob, D_005267B0, h, 0x32D, 0);
        func_202BE0(ob, D_005267D0, h, 0x32D, 0);
        func_202BE0(ob, D_005267F0, h, 0x32D, 0);
        normal_TransMenuLayoutBuild_516e20();
        func_28B230(D_00484788);
        D_00484750 = 1;
        return 1;
    }
    return 0;
}
