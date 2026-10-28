#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    s32 v4(s32 a0, s32 a1) { return VCM(s32, (void *, s32, s32), 0x18, a0, a1); }
};

extern "C" s32 D_004658B8;

struct Obj1 {
    u8 pad000[0x98];
    s16 m98;
    u8 m9A_b0 : 1;
    u8 m9A_b1 : 7;
};

struct Obj0 {
    u8 pad000[0xC];
    struct Obj1 *m0C;
};

extern "C" s32 DataTableOwnerLoadResidentBin_3b8b70(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    if (p1 == 0) {
        return 0;
    }
    if (p0->m0C != 0) {
        p0->m0C->m98 = p2;
        p0->m0C->m9A_b0 = p3;
        ((struct C0 *)p0->m0C)->v4(p1, D_004658B8 != 0);
    }
    return 1;
}
