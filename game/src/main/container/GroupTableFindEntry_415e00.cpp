/* rgp:protos */
#line 1
#include "types.h"

struct E415 { s16 key; u8 pad02[0x12]; };
struct R415 { u8 pad00[0x1C]; s32 m1C; E415 *m20; };

class V415 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    R415 * s70(s16 id, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(R415 *, (void *, s16, int, int), 0x70, id, rgp_fwd2, rgp_fwd3); }
};

extern "C" E415 *GroupTableFindEntry_415e00(V415 *a0, s32 a1, s32 a2, int rgp_a3)
{
    R415 *r;
    E415 *p;
    s32 i;
    s32 n;
    s16 key;

    r = a0->s70((s16)a1, (int)(long)(a2), (int)(long)(rgp_a3));
    if (r == 0) {
        return 0;
    }
    p = r->m20;
    if (p == 0) goto none;
    n = r->m1C;
    if (n > 0) goto ok;
none:
    return 0;
ok:
    key = (s16)a2;
    for (i = 0; i < n; i++, p++) {
        if (p->key == key) {
            return p;
        }
    }
    return 0;
}
