/* rgp:protos */
#line 1
#include "types.h"

struct Ent {
    s16 unk0;
    s16 unk2;
    u8 pad4[4];
    s16 unk8;
};

class Tbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ent * v70(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(Ent *, (void *, s32, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};

struct Sub {
    u8 pad0[0x1C];
    Tbl *tbl;
};

struct Obj {
    u8 pad0[4];
    Sub *sub;
    u8 pad8[0x340];
    s16 n;
    u8 pad34A[2];
    s32 ids[4];
};

extern "C" s32 StateBlockMapMarkerSetRemoveMatchingMaybe_3cc050(Obj *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    s32 tmp[4] __attribute__((aligned(16)));
    Ent *ref;
    Ent *e;
    s32 n;
    s32 i;
    s32 id;

    if (arg1 < 0) {
        arg0->n = 0;
        return 1;
    }
    ref = arg0->sub->tbl->v70(arg1, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (ref == NULL) {
        return 0;
    }
    {
        n = 0;
        for (i = 0; i < arg0->n; i++) {
            id = arg0->ids[i];
            e = arg0->sub->tbl->v70(id);
            if (e == NULL) {
                continue;
            }
            if (e->unk2 != ref->unk2 || e->unk8 != ref->unk8) {
                tmp[n++] = id;
            }
        }
        arg0->n = n;
        for (i = 0; i < n; i++) {
            arg0->ids[i] = tmp[i];
        }
    }
    return 1;
}
