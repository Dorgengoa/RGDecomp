/* rgp:protos */
#line 1
#include "types.h"
class O{public:VC_VPTR_MEMBER;s32 value() { return VCM0(s32, 0x50); }u8 pad[6];u8 b0:1;u8 b1:1;u8 rest:6;};
extern "C" {extern void *D_004838E8;s32 ItemIsSellable_3d4360(void *);void ItemConsume_3d41b0(O*, s32, s32, int);s32 ItemGetSellPrice_3d4320(O*);void PartyAddMoney_3c8e90(void*,s64);}
extern "C" s32 ItemSell_3d4010(O*p,s32 x){s32 before,after,delta,prod;if(!D_004838E8)return 0;if(!ItemIsSellable_3d4360((void *)p))return 0;before=p->value();ItemConsume_3d41b0(p, x, 0, 0);after=0;if(!p->b1)after=p->value();before-=after;if(before>0){prod=before*((short)ItemGetSellPrice_3d4320(p));PartyAddMoney_3c8e90(*(void**)((u8*)D_004838E8+0x18),(s64)prod);return 1;}return 0;}
