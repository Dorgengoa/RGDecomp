#include "types.h"
/* normal 0x0051E5F0 -- 0x7919-widget phase handler, same 0x34-Layout family as
 * normal_FUN_0050F960 (identical frame: -0x50, Layout at sp+0x10, memset 0x34,
 * `sh $2,0x40($29)`).
 *
 * f(void *, s32), `$4` never read, guard on `b`, returns 1.  The `b .L0051E70C`
 * at the end of the guarded block makes this an if/ELSE, not a fall-through.
 * func_28F620's result is used BOTH as an s16 pair (`lh 0x0` / `lh 0x2`, fed to
 * func_290F60) and as the Layout's f04, so it is spelled as a pointer.
 * `lui 0x3F80 / mtc1` is 1.0f inline; the middle float is the gp literal
 * D_0047D998 (gp - 0x77D8).  The else arm's `addiu $3,$0,1` + `bne $2,$3` is a
 * plain `== 1` against the signed return.
 */

typedef struct Layout {
    void *f00;
    s16  *f04;
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

extern f32   D_0047D998;          /* gp - 0x77D8 */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484718;          /* gp - 0xA58  */
extern void *D_00484720;          /* gp - 0xA50  */

extern void  func_131B60(void *p, s32 v, s32 n);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern s32   func_28E170(void *w, const u8 *p, s32 a, s32 b);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern s16  *func_28F620(void *w, u16 id, s32 n);
extern void *func_28FE10(void *w, u16 id, s32 n);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_290F60(void *w, u16 id, s32 x, s32 y);

s32 normal_TransHunterResultMsgState_51e5f0(void *a, s32 b)
{
    Layout lay;
    s16 *p;

    if (b != 0) {
        p = func_28F620(D_00484718, 0x7919, 0);
        func_290F60(D_00484718, 0x791A, p[0], p[1]);
        func_290690(D_00484718, 0x7919, 1.0f, D_0047D998, 0.0f);

        func_131B60(&lay, 0, 0x34);
        lay.f00 = func_28FE10(D_00484718, 0x7919, 0);
        lay.f04 = func_28F620(D_00484718, 0x7919, 0);
        lay.f10 = 0x3C;
        lay.f14 = 0x28;
        lay.f18 = 0x1E;
        lay.f1C = 8;
        lay.f20 = 0x49;
        lay.f24 = 0x49;
        lay.f28 = 0x19C;
        lay.f2C = 0x136;
        lay.f30 = 4;
        func_28D0C0(&lay, 0, 0, 0);
    } else {
        if (func_28E170(D_00484720, D_004B2570, 0, 0) == 1) {
            func_28EDE0(D_0048470C, 0x18, 0);
        }
    }
    return 1;
}
