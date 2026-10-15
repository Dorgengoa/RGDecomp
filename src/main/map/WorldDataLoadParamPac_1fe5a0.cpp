#include "types.h"
extern "C" {

extern void MemStackReturnToOwnerMaybe_14dad0(s32);
extern s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern void PadWaitReady_1849e0(void *);
extern u8 *SysGetModeMsg_1c39b0(void);
extern void WorldDataRebuild_1feac0(s32);
extern u8 *GetGameData_1fede0(void);
extern s32 GetWorldDataMgr_1fedf0(void);
extern s32 GetReadBuffHeap_2025e0(void);
extern s32 UnpackWordTriple_370d70(void *, s32, s32 *, s32 *, s32 *);
extern void DataTableOwnerLoadResidentBin_3b8b70(s32, s32, s16, s32);
extern void OptionsSetPlayTime_3d61f0(void **, s32);
extern void NewGamePartyInitMaybe_3e74f0(void *);
extern void GameDataLinkStateBlock_3ede00(void *);
extern void GameDataBindSubsystems_3ede30(void *, s32, s32, s32, s32);
extern s32 ResidentFileReadAlignedMaybe_3ee010(void *, s32, s32);
extern void WorldDataMgrSetGameData_3f29d0(s32, void *);
extern void WorldDataMgrLinkAll_3f29e0(s32);
extern void WorldDataMgrLoadParts_3f2be0(s32, s32, s32, s32);

extern u8 D_004B2570[0x400];

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual s32 f(void * x0, s32 x1);
};
class VC_1 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void f(u8 * x0, s32 x1);
};
void WorldDataLoadParamPac_1fe5a0(s32 arg0, s32 arg1) {
    s32 spFC;
    s32 spF8;
    s32 spF4;
    u8 spA0[0x50];
    s32 temp_3;
    s32 temp_20;
    s32 temp_23;
    u8 *temp_2_4;
    u8 *temp_2;
    s32 temp_4;
    s16 temp_k;
    s32 var_30;
    s32 temp_2_2;
    s32 temp_2_3;
    void **temp_16;

    temp_20 = GetWorldDataMgr_1fedf0();
    temp_2 = GetGameData_1fede0();
    temp_16 = *(void ***)(temp_2 + 0xC);
    var_30 = 0;
    if (arg0 != 0) {
        var_30 = ((VC_0 *)(temp_16))->f(spA0, 0x50);
    }
    WorldDataRebuild_1feac0(0);
    temp_2_2 = GetReadBuffHeap_2025e0();
    temp_2_3 = MemStackHeapAlloc_14db10(temp_2_2, 2, 0x1CCCC, 0x40);
    if (temp_2_3 != 0) {
        temp_23 = ResidentFileReadAlignedMaybe_3ee010(temp_2, temp_2_3, 0);
        if (arg1 != 0) {
            PadWaitReady_1849e0(&(*(u8 *)D_004B2570));
        }
        WorldDataMgrLoadParts_3f2be0(temp_20, temp_2_3, temp_23, arg1);
        if (arg1 != 0) {
            PadWaitReady_1849e0(&(*(u8 *)D_004B2570));
        }
        GameDataBindSubsystems_3ede30(temp_2, temp_2_3, temp_23, temp_20, arg1);
        if (arg1 != 0) {
            PadWaitReady_1849e0(&(*(u8 *)D_004B2570));
        }
        WorldDataMgrSetGameData_3f29d0(temp_20, temp_2);
        WorldDataMgrLinkAll_3f29e0(temp_20);
        if (arg1 != 0) {
            PadWaitReady_1849e0(&(*(u8 *)D_004B2570));
        }
        GameDataLinkStateBlock_3ede00(temp_2);
        if (arg1 != 0) {
            PadWaitReady_1849e0(&(*(u8 *)D_004B2570));
        }
        temp_2_4 = SysGetModeMsg_1c39b0();
        if (temp_2_4 != NULL) {
            temp_3 = *(s16 *)temp_2_4;
            if (temp_3 != 0 && temp_3 != 1) goto skip;
            NewGamePartyInitMaybe_3e74f0(temp_2);
            temp_4 = *(s32 *)(temp_2 + 0x28);
            temp_k = *(s16 *)(temp_2_4 + 0x6);
            if (temp_4 != 0) {
                DataTableOwnerLoadResidentBin_3b8b70(temp_4, temp_2_3, temp_k, 1);
            }
        skip:;
        }
        MemStackReturnToOwnerMaybe_14dad0(temp_2_2);
        MemStackHeapFree_14dcb0(temp_2_2, temp_2_3);
    }
    if (arg0 != 0) {
        spFC = 0;
        spF8 = 0;
        spF4 = 0;
        temp_4 = UnpackWordTriple_370d70(spA0, var_30, &spFC, &spF8, &spF4);
        ((VC_1 *)(temp_16))->f(spA0 + temp_4, spF4);
        OptionsSetPlayTime_3d61f0(temp_16, 0);
    }
}

}
