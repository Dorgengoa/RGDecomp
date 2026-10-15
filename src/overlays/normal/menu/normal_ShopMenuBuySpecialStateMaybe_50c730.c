#include "types.h"
/* normal 0x0050C730 -- the 0x71/0x72 result-banner phase handler.  `b != 0`
 * builds the banner (the 0xAC-byte descriptor is zeroed on the frame, given
 * the record's id, and handed to func_28A9A0); `b == 0` is the per-frame tick
 * that counts D_00484654 up to 0xA0 and then, once, tears the banner down.
 *
 * `$4` is never read -- the f(void *, s32) state-handler family; the guard is
 * on `b`.  The early exit returns 0, every other path returns 1.
 * `bnel $3,$2,.L0050C900 / addiu $2,$0,1` is the SHARED-TAIL DUPLICATE of
 * .L0050C8FC's `addiu $2,$0,1`, i.e. the `t == 0xA0` arm simply falls into the
 * common `return 1` -- it is not a per-arm return.
 * `slti $1, $3, 0xA0` writes $at.  MEASURED NULL here, 3 arms: `< 0xA0`,
 * `<= 0x9F` and the nested `else { if }` all give the SAME object, so the
 * [[at-compare-class]] token rule does not discriminate on this side of the
 * relation -- what mattered was WHICH ARM IS THE BRANCH TARGET: written
 * `> 0x9F` first the counter arm becomes the target and it is one word long.
 * `addiu $6,$0,1 / daddu $7,$6,$0` is mwcc sharing the constant between
 * arguments 3 and 4. */

typedef struct Rec { s16 f00; u8 pad02[0x2A]; s16 f2C; } Rec;
typedef struct Ent { u8 pad00[0x10]; Rec *f10; } Ent;
typedef struct Desc { u8 pad00[0xC]; s32 f0C; u8 pad10[0xAC - 0x10]; } Desc;

extern u8 D_00527E30[];
extern const u8 D_004B2570[];

extern void *D_004845CC;          /* gp - 0xBA4 */
extern void *D_004845D0;          /* gp - 0xBA0 */
extern void *D_004845C4;          /* gp - 0xBAC */
extern Ent **D_00484644;          /* gp - 0xB2C */
extern void *D_004845F8;          /* gp - 0xB78 */
extern s16   D_00484654;          /* gp - 0xB1C */

extern s32   func_1F59D0(void);
extern void  func_1CD960(s32 a, s32 b, s32 c, f32 d);
extern void  func_207340(s32 a, s32 b, f32 c);
extern void  func_2072F0(s32 a, f32 b);
extern void  func_28EA90(void *a, s32 b, s32 c);
extern void  func_28EDE0(void *a, s32 b, s32 c);
extern s32   func_28FE10(void *a, u16 b, s32 c);
extern void  func_288E50(s32 a, s16 b, s32 c, s32 d);
extern void  func_28AA00(Desc *a);
extern void  func_131B60(void *a, s32 b, s32 c);
extern void *func_28AA30(void *a, s32 b);
extern void  func_28A9A0(void *a, void *b, Desc *c, s32 d);
extern void  func_28F510(void *a, u16 b, const void *c, s32 d);
extern void  func_291110(void *a, u16 b, s32 c, s32 d);
extern void  func_2907A0(void *a, u16 b, f32 c);
extern void  func_290F60(void *a, u16 b, s32 c, s32 d);
extern s32   func_28E170(void *a, const void *b, s32 c, s32 d);

s32 normal_ShopMenuBuySpecialStateMaybe_50c730(void *a, s32 b)
{
    Ent *e;
    s16  t;
    Desc d;

    if (b != 0) {
        func_1CD960(func_1F59D0(), 0, 0xF, 0.0f);
        func_207340(0x321, 0, 1.0f);
        func_28EA90(D_004845D0, 0x7536, 0);
        e = *D_00484644;
        if (e == 0) {
            return 0;
        }
        func_288E50(func_28FE10(D_004845CC, 0x73, 0), e->f10->f2C, 0x28, 0x2D);
        func_28AA00(&d);
        func_131B60(&d, 0, 0xAC);
        d.f0C = e->f10->f00;
        func_28A9A0(D_00527E30, func_28AA30(D_004845F8, 0x10), &d, 1);
        func_28F510(D_004845CC, 0x72, D_00527E30, 0);
        func_291110(D_004845CC, 0x71, 1, 1);
        func_2907A0(D_004845CC, 0x71, 1.0f);
        func_290F60(D_004845CC, 0x71, 0x91, 0xB4);
        D_00484654 = 0;
    } else {
        t = D_00484654;
        if (t < 0xA0) {
            D_00484654 = t + 1;
        } else if (t == 0xA0) {
            if ((u32)(func_28E170(D_004845D0, D_004B2570, 0, 0) - 1) < 2) {
                func_291110(D_004845CC, 0x71, 0, 1);
                func_2072F0(0xF, 0.0f);
                func_1CD960(func_1F59D0(), 0, 0xF, 1.0f);
                func_28EDE0(D_004845C4, 0x753A, 0);
            }
        }
    }
    return 1;
}
