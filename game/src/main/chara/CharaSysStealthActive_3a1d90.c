/* rgp:protos */
#define RGP_SELF_CharaSysStealthActive_3a1d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma opt_rebuildconditionals off
typedef struct{u8 pad[0x250];f32 v;}O;/*rgp*/
s32 CharaSysStealthActive_3a1d90(O*a){if(((unsigned char)PartyHasStealthMember_3a1d70())==0){if(!(a->v<=0.0f))return 1;return 0;}return 1;}
