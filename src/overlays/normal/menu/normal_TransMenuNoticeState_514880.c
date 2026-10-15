#include "types.h"
/* normal 0x00514880 -- 0x764E-widget phase handler, 0x34-Layout family.
 * Frame is -0x60 because one callee-saved GPR is live across a call in the
 * else arm (`sq $16` at sp+0x00, `sd $31` at sp+0x10), which pushes the Layout
 * to sp+0x20 and the `sh` to 0x50.
 *
 * f(void *, s32), `$4` never read, guard on `b`, returns 1.  The guarded block
 * ends in `b .L005149F0`, so this is if/ELSE.  In the guard the func_290690
 * floats are 0.0f then the gp literal D_0047D9F8 (gp - 0x7778) then -1.0f, the
 * SWAPPED order of the seed.  The else arm's `addiu $2,$16,-1 / sltiu $1,$2,2`
 * is an UNSIGNED range test on the func_28E170 result, so its return is spelled
 * u32.  `addiu $4,$28,-0xA70` is the ADDRESS of small-data D_00484700.
 */

typedef struct Layout {
    void *f00;
    s32   f04;
    u8    pad08[8];
    s32   f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    s32   f20;
    s32   f24;
    s32   f28;
    s32   f2C;
    s16   f30;
} Layout;

extern const u8 D_004B2570[];
extern u8    D_00527EE0[];

extern f32   D_0047D9F8;          /* gp - 0x7778 */
extern s32   D_00484700;          /* gp - 0xA70  */
extern void *D_004846E8;          /* gp - 0xA88  */

extern void  func_131B60(void *p, s32 v, s32 n);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern u32   func_28E170(void *w, const u8 *p, s32 a, s32 b);
extern void  func_28EA90(void *w, s32 id, s32 a);
extern void  func_28EC60(void *w);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern s32   func_28F620(void *w, u16 id, s32 n);
extern void *func_28FE10(void *w, u16 id, s32 n);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);

s32 normal_TransMenuNoticeState_514880(void *a, s32 b)
{
    Layout lay;
    u32 r;

    if (b != 0) {
        func_290690(D_004846E8, 0x7556, 0.0f, D_0047D9F8, -1.0f);

        func_131B60(&lay, 0, 0x34);
        lay.f00 = func_28FE10(D_004846E8, 0x764E, 0);
        lay.f04 = func_28F620(D_004846E8, 0x764E, 0);
        lay.f10 = 0x3C;
        lay.f14 = 0xC;
        lay.f18 = 0x1C;
        lay.f1C = 8;
        lay.f20 = 0x62;
        lay.f24 = 0x49;
        lay.f28 = 0x186;
        lay.f2C = 0x12C;
        lay.f30 = 4;
        func_28D0C0(&lay, 0, 0, 0);

        func_291110(D_004846E8, 0x764E, 1, 1);
        func_28EA90(D_00527EE0, 0xF, 0);
        func_28E170(D_00527EE0, D_004B2570, 0, 0);
    } else {
        r = func_28E170(D_00527EE0, D_004B2570, 0, 0);
        func_28EC60(D_00527EE0);
        if (r - 1 < 2) {
            func_291110(D_004846E8, 0x764E, 0, 1);
            func_28EDE0(&D_00484700, 3, 0);
        }
    }
    return 1;
}
