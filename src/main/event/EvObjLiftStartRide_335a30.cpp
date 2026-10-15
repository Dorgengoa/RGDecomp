#include "types.h"

struct C220 {
    u8 pad000[0xDC];
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2(s32);
};

extern "C" s32 strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" u8 D_004625D0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x108];
    s16 m108;
    s16 m10A;
    s16 m10C;
    s16 m10E;
};

extern "C" s32 EvObjLiftStartRide_335a30(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    p0->m10C = p1;
    p0->m10E = p2;
    p0->m10A = 0;
    r0 = strcpy((struct Obj0 *)((u8 *)p0 + 0xF8), D_004625D0);
    p0->m108 = 4;
    r1 = ((struct C220 *)p0)->v2(0);
    return 1;
}
