#pragma optimization_level 3
#include "types.h"
extern void EffectEntriesSetTargetRefParamsMaybe_2dde30(void *,s16*);
s32 EffectSetTargetRefParamsMaybe_2e0dc0(u8*p,s16*q){s16 v=*q;if(v==2 || v==3){EffectEntriesSetTargetRefParamsMaybe_2dde30(p+0x1674,q);return 0;}return 1;}
