#include "types.h"
/* normal 0x0051EB20 -- 0x7919-widget phase handler, 0x34-Layout family.
 * Frame -0x50: `sd $31,0x0` is the whole save area, Layout at sp+0x10, no
 * extra stack object.  f(void *, s32), `$4` never read, guard on `b`, but the
 * TAIL after the guard is unconditional and returns 1.
 *
 * The three leading func_290690 calls take the ARGUMENT SWAP form
 * (0.0f, K, -1.0f); D_0047D9C4 is read TWICE, at each use, not hoisted.
 * `lui 0x42B4` / `lui 0x41F0` + plain `sw` is a float CONSTANT assigned to the
 * gp float D_004848CC -- mwcc materialises it in a GPR, so the two arms are
 * two source statements and the duplicated store is the scheduler's copy.
 * The tail `c.le.s $f2,$f1` against an inline 0.0f with `bc1tl` INTO the call
 * arm is a source `> 0.0f` with the subtract on the fall-through side.
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

extern f32   D_0047D9C0;          /* gp - 0x77B0 */
extern f32   D_0047D9C4;          /* gp - 0x77AC */
extern f32   D_0047D9C8;          /* gp - 0x77A8 */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern void *D_00484718;          /* gp - 0xA58  */
extern void *D_00484720;          /* gp - 0xA50  */
extern void *D_00484770;          /* gp - 0xA00  */
extern s32   D_004848BC;          /* gp - 0x8B4  */
extern f32   D_004848CC;          /* gp - 0x8A4  */

extern void  func_131B60(void *p, s32 v, s32 n);
extern f32   func_1CEBA0(void *p);
extern void *func_1F5BE0(void);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern void  func_28EA90(void *w, s32 id, s32 a);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  func_28F510(void *w, u16 id, void *p, s32 n);
extern s32   func_28F620(void *w, u16 id, s32 n);
extern void *func_28FE10(void *w, u16 id, s32 n);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);

s32 normal_TransHunterMsgOpenState_51eb20(void *a, s32 b)
{
    Layout lay;
    f32 t;

    if (b != 0) {
        func_290690(D_00484710, 0x764B, 0.0f, D_0047D9C0, -1.0f);
        func_290690(D_00484710, 0x7637, 0.0f, D_0047D9C4, -1.0f);
        func_290690(D_00484710, 0x764D, 0.0f, D_0047D9C4, -1.0f);
        func_28EA90(D_00484720, 0xF, 0);
        func_291110(D_00484718, 0x7919, 1, 1);
        func_290690(D_00484718, 0x7919, 1.0f, D_0047D9C8, 0.0f);
        func_28F510(D_00484718, 0x7919, func_28AA30(D_00484770, D_004848BC), 0);

        func_131B60(&lay, 0, 0x34);
        lay.f00 = func_28FE10(D_00484718, 0x7919, 0);
        lay.f04 = func_28F620(D_00484718, 0x7919, 0);
        lay.f10 = 0x28;
        lay.f14 = 0xC;
        lay.f18 = 0x14;
        lay.f1C = 8;
        lay.f20 = 0x49;
        lay.f24 = 0x49;
        lay.f28 = 0x19C;
        lay.f2C = 0x136;
        lay.f30 = 4;
        func_28D0C0(&lay, 0, 0, 0);

        func_291110(D_00484718, 0x791A, 0, 1);
        if (D_004848BC == 3) {
            D_004848CC = 90.0f;
        } else {
            D_004848CC = 30.0f;
        }
    }
    t = func_1CEBA0(func_1F5BE0());
    if (D_004848CC > 0.0f) {
        D_004848CC = D_004848CC - t;
    } else {
        func_28EDE0(D_0048470C, 0x14, 0);
    }
    return 1;
}
