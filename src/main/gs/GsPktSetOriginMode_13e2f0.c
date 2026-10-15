#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x11C];
    s32 m11C;
    s32 m120;
    s32 m124;
    s32 m128;
    s32 m12C;
    s32 m130;
    s32 m134;
};

void GsPktSetOriginMode_13e2f0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    s32 t2;
    s32 rv0;
    s32 rv1;
    s32 t3;
    s32 t4;
    s32 rv2;
    s32 rv3;
    s32 t5;

    p0->m11C = p1;
    if (p1 == 1) {
        p0->m124 = 0;
        p0->m120 = 0;
    } else {
        if (p1 == 2) {
            t0 = p0->m128;
            p0->m120 = t0;
            t1 = p0->m12C;
            p0->m124 = t1;
        } else {
            t2 = p0->m130;
            rv0 = t2;
            rv1 = (t2 >> 1);
            if (t2 < 0) {
                rv0 = (t2 + 1);
                rv1 = ((t2 + 1) >> 1);
            }
            t3 = p0->m128;
            p0->m120 = (t3 - rv1);
            t4 = p0->m134;
            rv2 = t4;
            rv3 = (t4 >> 1);
            if (t4 < 0) {
                rv2 = (t4 + 1);
                rv3 = ((t4 + 1) >> 1);
            }
            t5 = p0->m12C;
            p0->m124 = (t5 - rv3);
        }
    }
}
