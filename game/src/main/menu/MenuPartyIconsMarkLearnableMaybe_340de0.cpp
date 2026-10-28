/* rgp:protos */
#line 1
#include "types.h"

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f5c() { return VCM0(s32, 0x5C); }
};

struct R {
    u8 pad0[0x18];
    s32 unk18;
};

extern "C" {
void UiSetSpriteFlags_290bd0(s32, s32, long long, s32, s32, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
VObj *PartyGetSlotChara_3c2fb0(s32, s32);
bool SkillFlowHasLearnableMaybe_3e9580(R *, s32, int, int);
R *GetGameData_1fede0(void);
}

extern "C" s32 MenuPartyIconsMarkLearnableMaybe_340de0(u8 *arg0, s32 arg1)
{
    R *r;
    s32 h;
    s32 n;
    s32 i;
    VObj *o;

    r = GetGameData_1fede0();
    if (r == 0) {
        return 0;
    }
    h = r->unk18;
    n = PartyCountMembers_3c2010(h, 1, 1);
    n = n + PartyCountReserve_3c1c20(h, 1, 1);
    for (i = 0; i < n; i++) {
        o = PartyGetSlotChara_3c2fb0(r->unk18, i);
        if (o == 0) {
            continue;
        }
        if (SkillFlowHasLearnableMaybe_3e9580(r, o->f5c(), 0, 0) == 0) {
            UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x5C), arg1, (long long)(8), 1, i, 0);
        } else {
            UiSetSpriteFlags_290bd0(*(s32 *)(arg0 + 0x5C), arg1, (long long)(8), -1, i, 0);
        }
    }
    return 1;
}
