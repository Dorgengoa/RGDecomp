/* rgp:protos */
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: length-wrong (110w vs retail 111w), close; fixed a VT3C4*** deref-depth bug. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT3C4 {
    u8 pad3C4[0x3C4];
    u8 *(*unk3C4)(void *);
    u8 pad460[0x460 - 0x3C8];
    s32 (*unk460)(void *);
} VT3C4;

typedef struct Obj14 {
    u8 pad14[0x14];
    s32 unk14;
} Obj14;

void Sprintf_1343b8(void *, void *, ...);
void LoaderQueueAppendSeparator_1cd670(s32);
s32 LoaderRequestFile_1cd870(s32, void *, s32);
void CharaPcBuildPath_1f4ef0(void *, s32);
s32 GetLoaderMgr_1f59d0(void);
s32 GetNpcDataHeap_1fdd70(void);
Obj14 * GetGameData_1fede0(void);
s32 ScriptGetInt_2490f0(s32);
s32 GetEffectMgr_2d9040(void);
void EffectRequestByName_2e29d0(void *, s32, s32, void *, s32);
VT3C4 **CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
s32 CharaPcResNameBuildMaybe_40dc60(s32);
extern u8 D_0045EA00[];
extern u8 D_0045EA20[];
extern u8 D_0045EA30[];
extern u8 D_0045EA48[];
extern s32 D_0047E8B0;
extern s32 D_0047E8B4;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * f() { return VCM0(u8 *, 0x3C4); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x460); }
};
s32 EvCmdPcModelLoad_241a30(s64 *arg0, s32 arg1) {
    u8 sp180[0x100] __attribute__((aligned(16)));
    u8 sp80[0x100] __attribute__((aligned(16)));
    u8 sp70[16] __attribute__((aligned(16)));
    s32 var_19;
    s32 temp_16_2;
    s32 temp_18;
    VT3C4 **temp_2;
    s32 temp_16;
    u8 *temp_2_2;

    var_19 = ScriptGetInt_2490f0((s32)arg0++);
    temp_18 = GetLoaderMgr_1f59d0();
    temp_2 = CharaMgrPoolFindByDataId_3a8a70(GetGameData_1fede0()->unk14, 0x2AF9, 1, 1, 0, 0, 0);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_2_2 = ((VC_0 *)(temp_2))->f();
    if (temp_2_2 == NULL) {
        return 0;
    }
    temp_16 = *(s32 *)(temp_2_2 + 0x10);
    if (temp_16 == 0) {
        return 0;
    }
    if (var_19 < 0) {
        var_19 = ((VC_1 *)(temp_2))->f() & 0xFF;
    }
    if (var_19 != 0) {
        CharaPcBuildPath_1f4ef0(sp180, temp_16);
        Sprintf_1343b8(sp80, D_0045EA00);
    } else {
        Sprintf_1343b8(sp180, D_0045EA20, CharaPcResNameBuildMaybe_40dc60(temp_16));
        Sprintf_1343b8(sp80, D_0045EA30);
    }
    D_0047E8B0 = LoaderRequestFile_1cd870(temp_18, sp180, 0);
    D_0047E8B4 = LoaderRequestFile_1cd870(temp_18, sp80, 0);
    LoaderQueueAppendSeparator_1cd670(temp_18);
    if (arg1 >= 2 && ScriptGetInt_2490f0((s32)arg0) != 0 && var_19 != 0) {
        temp_16_2 = GetEffectMgr_2d9040();
        EffectRequestByName_2e29d0(sp70, temp_16_2, GetNpcDataHeap_1fdd70(), D_0045EA48, 0xC);
    }
    return 1;
}

}
