/* rgp:protos */
#line 1
#include "types.h"
class Obj { public:
VC_VPTR_MEMBER;

























s32 get(s64 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s64, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};
extern "C" {
extern u8 *D_00483894;
s32 WeaponCombineLookup_3c4280(s32, s32, s32, s32, s32, s32, s32, s32, void *, void *, void *, void *);
void WeaponCombineLookupByIds_3c45c0(s32 a,s64 b,s32 c,s64 d,s32 e,s32 f,s32 g,s32 h,s32 i,s32 j,s32 k,s32 l){
 s32 x;
 Obj *p;
 p=*(Obj **)(*(u8 **)(D_00483894+0x40)+8);
 x=p->get((s64)(s16)b, (int)(long)(c), (int)(long)(d));
 p=*(Obj **)(*(u8 **)(D_00483894+0x40)+8);
 WeaponCombineLookup_3c4280(a, x, c, p->get((s64)(s16)d), e, f, g, h, (void *)((s64)i), (void *)((s64)j), (void *)((s64)k), (void *)((s64)l));
}
}
