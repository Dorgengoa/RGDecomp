/* rgp:protos */
#line 1
#include "types.h"

struct E422 { s16 key; u8 pad02[0x1E]; };
struct R422 { u8 pad00[0x14]; s32 m14; E422 *m18; };

class V422 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    R422 * s70(s16 id, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(R422 *, (void *, s16, int, int), 0x70, id, rgp_fwd2, rgp_fwd3); }
};

extern "C" E422 *GroupTableFindEntry_422950(V422 *a0, s32 a1, s32 a2, int rgp_a3)
{
    R422 *r;
    E422 *p;
    s32 i;
    s32 n;
    s16 key;

    r = a0->s70((s16)a1, (int)(long)(a2), (int)(long)(rgp_a3));
    if (r == 0) {
        return 0;
    }
    p = r->m18;
    if (p == 0) goto none;
    n = r->m14;
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
