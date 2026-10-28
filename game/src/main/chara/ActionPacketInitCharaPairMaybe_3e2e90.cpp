#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v21() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v205() { return VCM0(s32, 0x33C); }
};

extern "C" void ActionPacketClear_3e3e90(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    u8 m02;
    u8 m03;
    u8 pad004[0x8];
    s32 m0C;
    s16 m10;
    u8 pad012[0x2];
    s32 m14;
    s32 m18;
    s16 m1C;
    u8 pad01E[0x2];
    s32 m20;
    s32 m24;
};

extern "C" struct Obj0 *ActionPacketInitCharaPairMaybe_3e2e90(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    if (p2 == 0) {
        return (struct Obj0 *)0;
    }
    if (p3 == 0) {
        return (struct Obj0 *)0;
    }
    ActionPacketClear_3e3e90(p0);
    p0->m02 = 8;
    p0->m00 = 1;
    if (p4 != 0) {
        p0->m03 = 0x27;
        p0->m00 = 2;
    } else {
        p0->m03 = 0x28;
        p0->m00 = 2;
    }
    p0->m0C = p1;
    r1 = ((struct C0 *)p2)->v21();
    p0->m10 = r1;
    r2 = ((struct C0 *)p2)->v205();
    p0->m14 = r2;
    p0->m18 = p2;
    r3 = ((struct C0 *)p3)->v21();
    p0->m1C = r3;
    r4 = ((struct C0 *)p3)->v205();
    p0->m20 = r4;
    p0->m24 = p3;
    return p0;
}
