/* rgp:protos */
#line 1
#include "types.h"

struct C76 {
    u8 pad000[0x4C];
    VC_VPTR_MEMBER;
    s32 v1(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0xC, a0, rgp_fwd2, rgp_fwd3); }
};

struct E8 { s32 a; s32 b; };

extern "C" s32 VariantGetInt_15f780(struct E8 *);

struct Obj0 {
    u8 pad000[0x50];
    s32 m50;
    s32 m54;
};

extern "C" struct Obj0 *D_004812D8;

extern "C" s32 MapCfgFuncPlaceData_18a7a0(struct E8 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    struct Obj0 *o;

    if (D_004812D8 == 0) {
        return 0;
    }
    if (((struct C76 *)D_004812D8)->v1(0x271C, (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 0) {
        return 0;
    }
    o = D_004812D8;
    o->m50 = VariantGetInt_15f780(p0++);
    o->m54 = VariantGetInt_15f780(p0);
    return 1;
}
