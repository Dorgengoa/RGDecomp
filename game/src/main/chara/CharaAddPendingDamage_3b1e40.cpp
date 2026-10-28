/* rgp:protos */
#line 1
#include "types.h"
class Obj { public:
VC_VPTR_MEMBER;













































s32 slotC0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }











s32 slotF0() { return VCM0(s32, 0xF0); }
u8 pad[0x1DC-4]; s32 count; };
extern "C" s32 CharaAddPendingDamage_3b1e40(Obj *o,s32 amount, int rgp_a2, int rgp_a3) { s32 left; s32 result; if(o->slotC0((int)(long)(amount), (int)(long)(rgp_a2), (int)(long)(rgp_a3))!=0) return 0; result=amount; left=o->slotF0()-o->count-amount; if(left<0)result=amount+left; o->count=o->count+amount; return result; }
