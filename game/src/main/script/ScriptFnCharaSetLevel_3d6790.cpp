/* rgp:protos */
#line 1
#include "types.h"

class O {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void vEC(s16 a0) { VCM(void, (void *, s16), 0xEC, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v2B8(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x2B8, a0, a1); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v450() { VCM0(void, 0x450); }
};

struct G60 { u8 pad[0x14]; s32 m14; };

extern "C" {
void VariantSetS32_36f040(s32, s32, s32);
s32 VariantGetS16_36fcc0(s32);
O *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
extern G60 *D_00483960;
extern s32 D_00483964;
}

extern "C" void ScriptFnCharaSetLevel_3d6790(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    O *o;

    if (arg0 == 0) return;
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) return;
    if (arg3 == 0 || arg2 < 2) return;
    o = CharaMgrPoolFindByDataId_3a8a70(D_00483960->m14, (s16)((short)VariantGetS16_36fcc0(arg3)), 1, 1, 0, 0, 0);
    if (o == 0) return;
    o->vEC(((short)VariantGetS16_36fcc0(arg3 + 0x38)));
    o->v450();
    o->v2B8(1, 0);
    VariantSetS32_36f040(arg0, 1, 1);
}
