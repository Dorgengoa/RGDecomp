/* rgp:protos */
#line 1
#include "types.h"

struct O3d89f0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    void f3c() { VCM0(void, 0x3C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 fc0() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    void ff4(s32 a0) { VCM(void, (void *, s32), 0xF4, a0); }
};

extern "C" {
void VariantSetS32_36f040(s32, s32, s32);
s32 VariantGetS16_36fcc0(s32);
O3d89f0 *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
s32 PartySetLeader_3c1600(s32, s32, s32);
extern void *D_00483960;
extern s32 D_00483964;
}

extern "C" void ScriptFnPartySetLeader_3d89f0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    O3d89f0 *o;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    o = CharaMgrPoolFindByDataId_3a8a70(*(s32 *)((u8 *)D_00483960 + 0x14), (s16)((short)VariantGetS16_36fcc0(arg3)), 1, 1, 0, 0, 0);
    if (o == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, PartySetLeader_3c1600(*(s32 *)((u8 *)D_00483960 + 0x18), *(s32 *)((u8 *)o + 0xC), 0) != 0, 1);
    if (o->fc0() != 0) {
        o->ff4(1);
        o->f3c();
    }
}
