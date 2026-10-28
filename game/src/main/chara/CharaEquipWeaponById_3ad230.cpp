#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v227(s32 a0, s32 a1) { return VCM(s32, (void *, s32, s32), 0x394, a0, a1); }
};

extern "C" s32 InvFindByUniqueId_3c85d0(s32, s32, s32, s32);

extern "C" struct Obj0 * D_00483818;

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

extern "C" s32 CharaEquipWeaponById_3ad230(s32 p0, s32 p1, s32 p2)
{
    struct Obj0 *g;
    s32 r0;

    if (p2 < 0) {
        return 0;
    }
    g = D_00483818;
    if (g == 0) {
        return 0;
    }
    r0 = InvFindByUniqueId_3c85d0(g->m18, p2, -1, 0);
    return ((struct C0 *)p0)->v227(p1, r0);
}
