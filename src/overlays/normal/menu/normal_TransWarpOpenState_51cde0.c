#include "types.h"
/* normal 0x0051CDE0 -- the name-entry banner's one-shot build: the 0x754B/C
 * and 0x75D0..0x75D3 widgets, then the 0x75DC caption centred on its own
 * measured width.  The 0x7534 fade test at the end runs on EVERY call.
 *
 * `$4` is never read -- another member of the f(void *, s32) state-handler
 * family; the guard is on `b`, and the two early exits return 0.
 * `bgez $2, .L / sra $3,$2,1` with the `addiu $2,$2,1` bias on the negative
 * path is a SIGNED DIVIDE BY TWO -- a source-level `/ 2`, not a shift.
 * `mtc1 $0,$f12` + three `mov.s` is one 0.0f reaching all four of
 * func_2905B0's float arguments.
 * `daddu $16,$2,$0` sits in func_3C97E0's DELAY SLOT and captures the
 * PREVIOUS call's result, which reads as the wrong call's return. */

typedef struct W   { u8 pad00[0x30]; s16 f30; } W;
typedef struct Ctx { u8 pad00[0x18]; W *f18; } Ctx;
typedef struct Obj { u8 pad00[4]; const void *f04; u8 pad08[0x40 - 8];
                     s32 f40; } Obj;

extern f32   D_0047D9EC;          /* gp - 0x7784 */
extern f32   D_0047D9F8;          /* gp - 0x7778 */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern s32   D_0048484C;          /* gp - 0x924  */
extern s32   D_00484878;          /* gp - 0x8F8  */

extern Ctx  *func_1FEDE0(void);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern s32   func_28F400(void *p, u16 id, s32 c);
extern void  func_28F510(void *p, u16 id, const void *q, s32 d);
extern void  func_28F590(void *p, u16 id, s32 c, s32 d);
extern void  func_28F670(void *p, u16 id, s32 c, s32 d, s32 e, s32 f, s32 g);
extern void  func_290010(void *p, u16 id, s32 c, s32 d);
extern void  func_2905B0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern f32   func_290770(void *p, u16 id);
extern void  func_2907A0(void *p, u16 id, f32 x);
extern void  func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void  func_290F60(void *p, u16 id, s32 x, s32 y);
extern void  func_291110(void *p, u16 id, s32 c, s32 d);
extern Obj  *func_3C97E0(W *w);

s32 normal_TransWarpOpenState_51cde0(void *a, s32 b)
{
    Ctx *c;
    Obj *o;

    if (b != 0) {
        func_291110(D_00484710, 0x754C, 0, 1);
        func_291110(D_00484710, 0x754B, 0, 1);
        func_290F50(D_00484710, 0x7534, -0x30, -0xF, 0, D_0047D9EC);
        func_290690(D_00484710, 0x7534, 0.0f, D_0047D9F8, -1.0f);
        func_290010(D_00484710, 0x75D0, 1, -1);
        func_2907A0(D_00484710, 0x75D0, 0.0f);
        func_291110(D_00484710, 0x75D2, 1, 1);
        func_2907A0(D_00484710, 0x75D2, 0.0f);
        func_291110(D_00484710, 0x75D3, 1, 1);
        func_2907A0(D_00484710, 0x75D3, 0.0f);
        func_28F670(D_00484710, 0x753C, 0, 0, 0, 0, 0);
        func_291110(D_00484710, 0x75DC, 1, 1);
        func_291110(D_00484710, 0x75DB, 1, 1);
        func_2907A0(D_00484710, 0x75DC, 0.0f);
        func_2905B0(D_00484710, 0x75DB, 0.0f, 0.0f, 0.0f, 0.0f);
        func_290F60(D_00484710, 0x75DC, 0, 0x10);
        func_290F60(D_00484710, 0x75DB, 3, 0x13);
        c = func_1FEDE0();
        o = func_3C97E0(c->f18);
        if (o == 0) {
            return 0;
        }
        if ((o->f40 & 1) == 0) {
            return 0;
        }
        func_28F510(D_00484710, 0x75DC, o->f04, 0);
        func_28F590(D_00484710, 0x75DC,
                    0x100 - func_28F400(D_00484710, 0x75DC, 0) / 2, 0);
        D_00484878 = c->f18->f30;
        D_0048484C = 0;
    }
    if (func_290770(D_00484710, 0x7534) <= 0.0f) {
        func_28EDE0(D_0048470C, 0xC, 0);
    }
    return 1;
}
