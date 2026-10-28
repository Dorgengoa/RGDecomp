#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    s32 v12() { return VCM0(s32, 0x38); }
    s32 v13() { return VCM0(s32, 0x3C); }
};

extern "C" s32 UnitBaseInitFromData_3b8300(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s16 m00;
};

struct Obj1 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0xA];
    s16 m10;
    u8 pad012[0x21E];
    struct Obj0 *m230;
    u8 pad234[0x4];
    s32 m238;
    u8 pad23C[0x268];
    s32 m4A4;
    s32 m4A8;
};

extern "C" s32 CharaInitFromData_3af8f0(struct Obj1 *p0, s32 p1, struct Obj0 *p2)
{
    s16 t0;
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    if (p2 == 0) {
        return 0;
    }
    t0 = p2->m00;
    p0->m04 = t0;
    p0->m230 = p2;
    p0->m10 = 1;
    r0 = UnitBaseInitFromData_3b8300(p0, p1);
    rv3 = 1;
    if ((r0 & 0xFF) == 0) {
        rv3 = 0;
    } else {
        p0->m4A4 = 0;
        p0->m4A8 = 0;
        p0->m238 = 0x54;
        r1 = ((struct C0 *)p0)->v12();
        r2 = ((struct C0 *)p0)->v13();
        rv3 = 1;
    }
    return rv3;
}
