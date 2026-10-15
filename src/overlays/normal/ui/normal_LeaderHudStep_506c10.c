#include "types.h"
/* normal 0x00506C10 -- the horizontal slide step for the shop cursor.
 * `fB8` is the per-frame delta; the clamp window is fB4 +/- |delta|, and
 * landing inside it snaps fB0 to fB4 and kills the delta.  Both func_290690
 * posts push the same x with y = 1.0f, z = -1.0f. */

typedef struct Obj {
    u8  pad000[0x5C];
    s8  f05C;
    u8  pad05D[0xB0 - 0x5D];
    f32 f0B0;
    f32 f0B4;
    f32 f0B8;
} Obj;

extern void *func_289B40(void);
extern void *func_289B60(Obj *p);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern void  func_2913A0(void *w);
extern void  func_28ED70(void *w);

s32 normal_LeaderHudStep_506c10(Obj *p)
{
    void *a;
    void *b;
    f32   d;

    if (p->f05C == 0) {
        return 0;
    }
    a = func_289B40();
    b = func_289B60(p);
    if (b == 0) {
        return 0;
    }
    if (a == 0) {
        return 0;
    }
    if (p->f0B8 != 0.0f) {
        p->f0B0 = p->f0B0 + p->f0B8;
        d = (p->f0B8 < 0.0f) ? -p->f0B8 : p->f0B8;
        if (!(p->f0B0 < p->f0B4 - d)) {
            if (p->f0B0 <= p->f0B4 + d) {
                p->f0B0 = p->f0B4;
                p->f0B8 = 0.0f;
            }
        }
        func_290690(b, 1, p->f0B0, 1.0f, -1.0f);
        func_290690(b, 0xE, p->f0B0, 1.0f, -1.0f);
    }
    func_2913A0(b);
    func_28ED70(a);
    return 1;
}
