/* rgp:protos */
#line 1
/* PARK 1/3: RIGHT LENGTH (100w), 30 bad. Fixed a VT30*** vs VT30** dereference-depth bug that blocked compilation; the `(var_18*4+sp)->unk70->unk8` m2c bug was reconstructed as a byte-offset chain, unverified against raw asm. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT30 {
    u8 pad[0x30];
    s32 (*unk30)(void *);
    s32 (*unk34)(void *);
    u8 pad340[0x340 - 0x38];
    s16 *(*unk340)(void *, s32);
} VT30;

typedef struct Obj14 {
    u8 pad[0x14];
    s32 unk14;
} Obj14;

typedef struct Entry70 {
    u8 pad70[0x70];
    s32 unk70_8_pad[2];
} Entry70;

s32 CharaDataGetSubRecMemStack_1ed430(s32, s32, s32);
s32 CharaAbilityResRequest_1f0650(s32, s32, s32, s32);
s32 GetCharaResMgr_1fdb60(void);
s32 GetCharaDataMgr_1fdb70(void);
Obj14 * GetGameData_1fede0(void);
s32 GetEffectMgr_2d9040(void);
void EffectReleaseByGroup_2e12f0(s32, s32);
void EffectRequestByName_2e29d0(void *, s32, s32, s32, s32);
s32 EquipSlotCollectEffectRefsMaybe_3a03e0(void **, void *, s32, s32);
VT30 **CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x30); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x34); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s16 * f(s32 x0) { return VCM(s16 *, (void *, s32), 0x340, x0); }
};
s32 CharaAbilityResReloadMaybe_2f3f10(s32 arg0, VT30 **arg1) {
    u8 sp70[0x100] __attribute__((aligned(16)));
    s32 temp_18;
    s16 *temp_2_2;
    s32 temp_16;
    s32 temp_17;
    u8 sp60[16] __attribute__((aligned(16)));
    s32 temp_18_2;
    s32 temp_20;
    s32 temp_2_3;
    s32 var_18;
    VT30 **temp_2;
    Obj14 *temp_17_2;

    if (arg1 == NULL) {
        return 0;
    }
    temp_18 = GetCharaResMgr_1fdb60();
    temp_17 = ((VC_0 *)(arg1))->f();
    if (CharaAbilityResRequest_1f0650(temp_18, arg0, temp_17, ((VC_1 *)(arg1))->f()) == 0) {
        return 0;
    }
    temp_17_2 = GetGameData_1fede0();
    temp_18_2 = GetCharaDataMgr_1fdb70();
    temp_20 = GetEffectMgr_2d9040();
    temp_2 = CharaMgrPoolFindByDataId_3a8a70(temp_17_2->unk14, arg0, 1, 1, 0, 0, 0);
    if (temp_2 != NULL) {
        temp_2_2 = ((VC_2 *)(temp_2))->f(0);
        if (temp_2_2 != NULL) {
            EffectReleaseByGroup_2e12f0(temp_20, *temp_2_2 - 0x3D1);
            temp_2_3 = CharaDataGetSubRecMemStack_1ed430(temp_18_2, *temp_2_2 - 0x3D1, 4);
            if (temp_2_3 != 0) {
                temp_16 = EquipSlotCollectEffectRefsMaybe_3a03e0((void **)arg1, sp70, 0x40, 0);
                var_18 = 0;
                while (var_18 < temp_16) {
                    EffectRequestByName_2e29d0(sp60, temp_20, temp_2_3, *(s32 *)(*(u8 **)(sp70 + var_18 * 4) + 8), *temp_2_2 - 0x3D1);
                    var_18 += 1;
                }
            }
        }
    }
    return 1;
}

}
