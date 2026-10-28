/* rgp:protos */
#line 1
#include "types.h"
#pragma inline_intrinsics off

/* Three C++ virtual calls, all on already-existing objects (arg0 itself,
   and the object returned by arg0's own slot 223 call): slot27 -> 0x74,
   slot154 -> 0x270, slot223 -> 0x384. Same "big base-object vtable" shape
   already admitted elsewhere in this codebase (e.g. src/s13q/CharaGaugeNextThreshold_3aade0.cpp
   with a 304-slot version of the same class) -- only declared out to the
   slot this unit actually needs. */

class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v27(s32 a0) { return VCM(s32, (void *, s32), 0x74, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int v154(s32 a0) { return VCM(int, (void *, s32), 0x270, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ent * v223(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(Ent *, (void *, int, int, int), 0x384, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 abs(s32);

extern "C" {
extern s32 D_00465CE0[];
extern s32 D_00465CE8[];
extern s32 D_00465CF0[];
}

extern "C" int CharaActionGaugeSpend_3abca0(Ent *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{ int rgp_v0;
    s32 var_5;
    Ent *temp_2;

    temp_2 = arg0->v223((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (arg1 == 0) {
        var_5 = D_00465CE8[0];
        if (temp_2 != 0) {
            var_5 = -abs(temp_2->v27(var_5));
        }
    } else if (arg1 == 1) {
        var_5 = D_00465CF0[0];
        if (temp_2 != 0) {
            var_5 = -abs(temp_2->v27(var_5));
        }
    } else {
        var_5 = D_00465CE0[0];
    }
    rgp_v0 = arg0->v154(var_5);
return rgp_v0; }
