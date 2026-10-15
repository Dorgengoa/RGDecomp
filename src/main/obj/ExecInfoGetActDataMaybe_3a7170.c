#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x6];
    s32 m0C;
    s32 m10;
    u8 pad014[0x4];
    s32 m18;
};

s32 ExecInfoGetActDataMaybe_3a7170(struct Obj0 *p0)
{
    s16 t0;
    s32 rv4;
    s32 rv3;
    s32 rv2;
    s32 rv1;
    s32 rv0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t5;

    t0 = p0->m04;
    rv4 = t5;
    if (t0 != 5) {
        rv3 = t4;
        if (t0 != 4) {
            rv2 = t3;
            if (t0 != 3) {
                rv1 = t2;
                if (t0 != 2) {
                    rv0 = t1;
                    if (t0 != 1) {
                        rv0 = 0;
                    } else {
                        t1 = p0->m18;
                        rv0 = t1;
                    }
                    rv1 = rv0;
                } else {
                    t2 = p0->m0C;
                    rv1 = t2;
                }
                rv2 = rv1;
            } else {
                t3 = p0->m10;
                rv2 = t3;
            }
            rv3 = rv2;
        } else {
            t4 = p0->m10;
            rv3 = t4;
        }
        rv4 = rv3;
    } else {
        t5 = p0->m0C;
        rv4 = t5;
    }
    return rv4;
}
