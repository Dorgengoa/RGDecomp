/* rgp:protos */
#line 1
#include "types.h"

struct B3D09C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s16 n, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s16, int, int), 0x70, n, rgp_fwd2, rgp_fwd3); }
};
struct C3D09C0 : B3D09C0 {};
struct M3D09C0 { u8 pad000[0x8]; struct C3D09C0 *f08; };
struct N3D09C0 { u8 pad000[0x40]; struct M3D09C0 *f40; };
struct G3D09C0 { u8 pad000[0x8]; struct N3D09C0 *f08; };
struct A3D09C0 { u8 pad000[0x4]; s16 f04; };
struct T3D09C0 { u8 pad000[0x18]; struct A3D09C0 *f18; };

extern "C" struct G3D09C0 *D_004838E8;

extern "C" s32 CageRecGetCatchDef_3d09c0(struct T3D09C0 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    struct G3D09C0 *g;
    s32 n;

    g = D_004838E8;
    if (g == 0) return 0;
    n = p->f18->f04;
    if (n <= 0) return 0;
    return g->f08->f40->f08->v26(n, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
}
