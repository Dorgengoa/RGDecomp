#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v21() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s16 * v206(s32 arg1) { return VCM(s16 *, (void *, s32), 0x340, arg1); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v278() { return VCM0(s32, 0x460); }
};

extern "C" s32 CharaDataEnsureAndLoadBtChrMaybe_1f0c00(s32 arg0, s32 arg1);
extern "C" s32 GetNpcDataHeap_1fdd70(void);
struct Ctx001f09f0 { u8 pad0[0x14]; s32 unk14; };
extern "C" Ctx001f09f0 *GetGameData_1fede0(void);
extern "C" s32 GetEffectMgr_2d9040(void);
struct Sp50Struct { u8 pad0[0x10]; };
extern "C" void EffectRequestByName_2e29d0(Sp50Struct *arg0, s32 arg1, s32 arg2, const void *arg3, s32 arg4);
extern "C" C0 *CharaMgrPoolFindById_3a8c60(s32 arg0, s32 arg1);
extern "C" u8 D_0045B770;

extern "C" s32 CharaResRequestBtChrByIdMaybe_1f09f0(s32 arg0, s32 arg1) {
    Sp50Struct sp50 __attribute__((aligned(16)));
    s16 *temp_16;
    s32 temp_18;
    C0 *temp_2;

    temp_2 = CharaMgrPoolFindById_3a8c60(GetGameData_1fede0()->unk14, arg1);
    if (temp_2 == NULL) {
        return 0;
    }
    if (temp_2->v278() != 0) {
        temp_16 = temp_2->v206(0);
        temp_18 = GetEffectMgr_2d9040();
        EffectRequestByName_2e29d0(&sp50, temp_18, GetNpcDataHeap_1fdd70(), &D_0045B770, *temp_16 - 0x3DD);
    }
    if (CharaDataEnsureAndLoadBtChrMaybe_1f0c00(arg0, temp_2->v21()) == 0) {
        return 0;
    }
    return 1;
}
