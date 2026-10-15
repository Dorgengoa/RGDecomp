#include "types.h"
/* normal 0x004FD2D0 -- the equip-compare panel's one-shot build: the four
 * 0x3A sub-images out of D_00481BBC, the 0x35 frame, the 0x38/0x3B labels, and
 * a reset of the 0x38 widget's field when a session is live.  The 0x35 fade
 * test at the end runs on EVERY call.
 *
 * `$4` is never read -- another member of the f(void *, s32) state-handler
 * family; the guard is on `b`.  The function returns 0 on the D_00484454 exit
 * and 1 everywhere else, which is why retail materialises the constant twice.
 * `addiu $6,$0,1 / daddu $7,$6,$0` is mwcc SHARING the constant between
 * arguments 3 and 4, not two source constants.
 * `mov.s $f13,$f12 / mov.s $f14,$f12` is the same 1.0f reaching three of
 * func_2905B0's four float arguments -- one source literal, copied.
 * `c.lt.s $f0,$f1` + `bc1tl` is the `>= 1.0f` guard INVERTED by mwcc, not a
 * `<` in the source. */

typedef struct Fld { u8 pad00[2]; s16 f02; } Fld;
typedef struct Wgt { u8 pad00[0x20]; Fld *f20; } Wgt;

extern f32   D_0047D248;          /* gp - 0x7F28 */
extern f32   D_0047D520;          /* gp - 0x7C50 */
extern void *D_00481BBC;          /* gp - 0x35B4 */
extern void *D_00484454;          /* gp - 0xD1C  */
extern void *D_00484498;          /* gp - 0xCD8  */
extern void *D_0048449C;          /* gp - 0xCD4  */
extern s32   D_004844D4;          /* gp - 0xC9C  */

extern const void *func_28AA30(void *a, s32 id);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_28F510(void *p, u16 id, const void *q, s32 d);
extern Wgt  *func_290460(void *p, u16 id);
extern void  func_2905B0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern f32   func_290770(void *p, u16 id);
extern void  func_2907A0(void *p, u16 id, f32 x);
extern void  func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void  func_290F60(void *p, u16 id, s32 x, s32 y);
extern void  func_291110(void *p, u16 id, s32 c, s32 d);

s32 normal_BtlChgMenuTacticsOpenState_4fd2d0(void *a, s32 b)
{
    Wgt *w;
    Fld *t;

    if (b != 0) {
        D_004844D4 = 0;
        func_28F510(D_0048449C, 0x3A, func_28AA30(D_00481BBC, 0x4E), 0);
        func_28F510(D_0048449C, 0x3A, func_28AA30(D_00481BBC, 0x4F), 1);
        func_28F510(D_0048449C, 0x3A, func_28AA30(D_00481BBC, 0x50), 2);
        func_28F510(D_0048449C, 0x3A, func_28AA30(D_00481BBC, 0x51), 3);
        func_291110(D_0048449C, 0x35, 1, 1);
        func_290F60(D_0048449C, 0x35, -0x1E, 0xF8);
        func_2907A0(D_0048449C, 0x35, 0.0f);
        func_290F50(D_0048449C, 0x35, 0x2A, 0xF8, 0, D_0047D248);
        func_290690(D_0048449C, 0x35, 1.0f, D_0047D520, -1.0f);
        func_291110(D_0048449C, 0x3B, 1, 1);
        func_291110(D_0048449C, 0x38, 1, 1);
        func_2907A0(D_0048449C, 0x3B, 0.0f);
        func_2907A0(D_0048449C, 0x38, 0.0f);
        func_290690(D_0048449C, 0x3B, 1.0f, D_0047D520, -1.0f);
        func_290690(D_0048449C, 0x38, 1.0f, D_0047D520, -1.0f);
        func_290F60(D_0048449C, 0x38, 7, 6);
        func_2905B0(D_0048449C, 0x38, 1.0f, 1.0f, 1.0f, -1.0f);
        func_290F60(D_0048449C, 0x3B, -0xF, 1);
        if (D_00484454 == 0) {
            return 0;
        }
        if (D_0048449C != 0) {
            func_290F60(D_0048449C, 0x38, 7, 6);
            w = func_290460(D_0048449C, 0x38);
            if (w != 0) {
                t = w->f20;
                if (t != 0) {
                    t->f02 = 0;
                }
            }
        }
    }
    if (func_290770(D_0048449C, 0x35) >= 1.0f) {
        func_28EDE0(D_00484498, 0x5609, 0);
    }
    return 1;
}
