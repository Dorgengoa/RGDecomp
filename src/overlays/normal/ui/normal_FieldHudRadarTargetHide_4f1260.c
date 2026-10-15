#include "types.h"
/* normal 0x004F1260 -- re-arms the party-formation panel's 0x3E cursor: drops
 * the current hold, resets its scale to 1.0f, restarts the blink and clears
 * the 0x4F0/0x4F4 selection pair.  Sibling of normal_FUN_004F12D0, same
 * `p->f378` guard written positively so the body falls through.
 *
 * func_290460's result is DISCARDED -- $4 is still the incoming pointer at the
 * call, and the `daddu $4,$16,$0` before each later call is the reload of the
 * saved handle.  `b` is never read.
 */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x4F0 - 0x37A];
    s32 f4F0;
    s32 f4F4;
} Obj;

extern f32 D_0047D1D8;            /* gp - 0x7F98 */

extern void *func_290460(void *p, u16 id);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void  func_2907A0(void *p, u16 id, f32 x);

void normal_FieldHudRadarTargetHide_4f1260(Obj *p, s32 b)
{
    if (p->f378 != 0) {
        func_290460(p, 0x3E);
        func_2907A0(p, 0x3E, 1.0f);
        func_290690(p, 0x3E, 0.0f, D_0047D1D8, -1.0f);
        p->f4F0 = -1;
        p->f4F4 = 0;
    }
}
