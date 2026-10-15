#include "types.h"

extern s32 ItemInInvCategory0_3d4960(void *);
extern s32 ItemDefGetStackLimit_40e070(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_00465B60;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 ItemGetStackLimit_3d4480(struct Obj0 *p0)
{
    s32 t0;
    s32 rv3;
    s32 r0;
    s32 rv2;
    s32 r1;
    s32 t1;

    t0 = p0->m10;
    rv3 = rv2;
    if (t0 == 0) {
        rv3 = 0;
    } else {
        r0 = ItemInInvCategory0_3d4960(p0);
        rv2 = t1;
        if (r0 != 0) {
            r1 = ItemDefGetStackLimit_40e070(t0);
            rv2 = r1;
        } else {
            t1 = D_00465B60;
            rv2 = t1;
        }
        rv3 = rv2;
    }
    return rv3;
}
