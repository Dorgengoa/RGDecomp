#include "types.h"

extern void * SlotRecordFindById_3e4e80(s32, s32);
extern s32 SlotRecordReset_3eeca0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
};

s32 SlotRecordResetById_3e4e20(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s16 t0;
    s16 t1;
    s32 r1;

    r0 = SlotRecordFindById_3e4e80(p0, p1);
    if (r0 == 0) {
        return 0;
    }
    t0 = r0->m00;
    t1 = r0->m02;
    r1 = SlotRecordReset_3eeca0(r0);
    r0->m00 = t0;
    r0->m02 = t1;
    return 1;
}
