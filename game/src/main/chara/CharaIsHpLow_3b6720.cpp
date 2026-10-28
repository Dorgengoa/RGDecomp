/* rgp:protos */
#line 1
#pragma opt_propagation off
#include "types.h"
#pragma fast_fptosi on
class O{public:VC_VPTR_MEMBER;s32 vF0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xF0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }s32 v128(s32 a0) { return VCM(s32, (void *, s32), 0x128, a0); }};extern "C" s32 D_00465CC8[4];
extern "C" s32 CharaIsHpLow_3b6720(O*p, int rgp_a1, int rgp_a2, int rgp_a3){s32 n=p->vF0((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));s32 m=p->v128(1);f32 c=(f32)m/100.0f;f32 f=(f32)(s32)(c*(f32)D_00465CC8[0]);f32 e=(f32)n;s32 r=1;if(!(e<=f))r=0;return r;}
