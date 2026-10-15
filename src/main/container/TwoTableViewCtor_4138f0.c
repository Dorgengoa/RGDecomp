#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_0047A210[];
extern u8 D_0047A5B0[];

struct Obj0;

struct Obj0 {
    void *m00;
    s16 m04;
    u8 pad006[0x2];
    s32 m08;
    s32 m0C;
};

struct Obj0 *TwoTableViewCtor_4138f0(struct Obj0 *p0)
{
    p0->m00 = D_00472250;
    p0->m00 = D_0047A210;
    p0->m00 = D_0047A5B0;
    p0->m04 = -1;
    p0->m08 = 0;
    p0->m0C = 0;
    return p0;
}
