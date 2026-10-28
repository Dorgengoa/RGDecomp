/* PARK: m2c cannot decompile -- "Unable to determine jump table for jr
   instruction." Needs a jump-table reconstruction pass this lane's budget
   does not cover. Not attempted. */
/* s49m: MATCH (multi-section, multicheck.py) */
#include "types.h"
#undef NULL
#define NULL 0
#pragma opt_propagation off

class Obj {
public:
    u8 pad[0x68];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f5C(s32 a0, s32 a1, s32 a2, s32 a3) { return VCM(s32, (void *, s32, s32, s32, s32), 0x5C, a0, a1, a2, a3); }
};

typedef struct Ent {
    u8 pad0[0x32];
    s16 unk32;
    u8 pad34[0x38];
    s8 unk6C;
} Ent;

extern "C" s32 MapAreaModelCollectOverlappingNodesMaybe_188c20(Obj *, s32, Ent **, s32);
extern "C" s32 NodeObjCollectTris_194e90(Ent *, s32, u8 *, s32, s32);

extern "C" s32 MapAreaModelCollectTrisAllMaybe_187d40(Obj *o, s32 a, s32 b, s32 c)
{
    return o->f5C(3, a, b, c);
}

extern "C" s32 func_00187D40_e1(Obj *o, s32 a, s32 b, s32 c)
{
    return o->f5C(1, a, b, c);
}

extern "C" s32 func_00187D40_e2(Obj *o, s32 a1, u8 *out, s32 key, s32 max)
{
    Ent *list[0x80];
    s32 n;
    s32 total;
    s32 i;
    s32 j;
    s32 k;
    Ent *e;

    if (max <= 0) {
        return 0;
    }
    n = MapAreaModelCollectOverlappingNodesMaybe_188c20(o, key, list, 0x80);
    total = 0;
    for (i = 0; i < n; i++) {
        e = list[i];
        bool b = e->unk6C == 0;
        if (b) {
            continue;
        }
        if (e->unk32 == 0) {
            continue;
        }
        k = NodeObjCollectTris_194e90(e, a1, out, key, max);
        for (j = 0; j < k; j++) {
            *(s16 *)(out + 0x50) = i;
            out += 0x60;
        }
        max -= k;
        total += k;
        if (max <= 0) {
            break;
        }
    }
    return total;
}
