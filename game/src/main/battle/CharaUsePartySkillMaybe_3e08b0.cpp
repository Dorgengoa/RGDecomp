/* rgp:protos */
#line 1
#include "types.h"

class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f21() { return VCM0(s32, 0x5C); }
    
    
    
    s32 f25(s32 a0) { return VCM(s32, (void *, s32), 0x6C, a0); }
};

struct G003E08B0 {
    u8 pad0[0x14];
    s32 unk14;
    u8 pad18[0x84 - 0x18];
    s32 unk84;
};

extern "C" {
extern VC *CharaMgrPoolFindById_3a8c60(s32, s32);
extern s32 SkillGetCharaStateMaybe_3e0df0(s32);
extern s32 SkillActionCreate_3e0f40(long long, s32, s32, s32, s32);
extern s32 SkillCanUseMaybe_3e1970(s32, s32);
extern s32 SkillDefFindMaybe_40ea70(s32, s32, s32);
extern s32 D_00466910[][3];
extern G003E08B0 *D_00483990;
extern G003E08B0 *D_00483994;
}

extern "C" s32 CharaUsePartySkillMaybe_3e08b0(s32 arg0, s32 arg1)
{
    VC *o;
    s32 kind;
    s32 idx;
    s32 id;
    s32 r;

    if (D_00483990 == NULL) {
        return 0;
    }
    o = CharaMgrPoolFindById_3a8c60(D_00483990->unk14, arg0);
    if (o == NULL) {
        return 0;
    }
    kind = o->f21();
    if (o->f25(0) == 0) {
        return 0;
    }
    r = SkillGetCharaStateMaybe_3e0df0(arg0);
    if (r == 1 || r == 3) {
        return 0;
    }
    idx = kind - 0x2AF9;
    if (idx < 0 || idx >= 8) {
        return 0;
    }
    id = D_00466910[idx][arg1];
    r = SkillDefFindMaybe_40ea70(D_00483994->unk84, -1, id);
    if (r == 0) {
        return 0;
    }
    {
        bool ng = !(((unsigned char)SkillCanUseMaybe_3e1970(arg0, r)) != 0);
        if (ng) {
            return 0;
        }
    }
    return SkillActionCreate_3e0f40((long long)(-1), id, arg0, 0, 1);
}
