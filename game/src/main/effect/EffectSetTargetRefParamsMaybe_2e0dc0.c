/* rgp:protos */
#define RGP_SELF_EffectSetTargetRefParamsMaybe_2e0dc0 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"
/*rgp*/
s32 EffectSetTargetRefParamsMaybe_2e0dc0(u8*p,s16*q, int rgp_a2, int rgp_a3, int rgp_a4){s16 v=*q;if(v==2 || v==3){EffectEntriesSetTargetRefParamsMaybe_2dde30(p+0x1674, q, (int)rgp_a2, (int)rgp_a3, (int)rgp_a4);return 0;}return 1;}
