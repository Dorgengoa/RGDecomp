#include "types.h"

#pragma opt_rebuildconditionals off
typedef struct{u8 pad[0x250];f32 v;}O;extern s32 PartyHasStealthMember_3a1d70(void);
s32 CharaSysStealthActive_3a1d90(O*a){if(PartyHasStealthMember_3a1d70()==0){if(!(a->v<=0.0f))return 1;return 0;}return 1;}
