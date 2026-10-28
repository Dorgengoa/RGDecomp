/* rgp:protos */
#line 1
#include "types.h"

class V1feac0 {
public:
    VC_VPTR_MEMBER;
    
    
    s32 v3(void * a0, s32 a1) { return VCM(s32, (void *, void *, s32), 0x14, a0, a1); }
    void v4(void * a0, s32 a1) { VCM(void, (void *, void *, s32), 0x18, a0, a1); }
};

typedef struct {
    u8 pad0[0xC];
    V1feac0 *unkC;
} Obj001fedf0;

extern "C" {
void MemStackReset_14d830(void *);
Obj001fedf0 *GetGameData_1fede0(void);
s32 GetWorldDataMgr_1fedf0(void);
s32 UnpackWordTriple_370d70(void *, s32, s32 *, s32 *, s32 *);
void OptionsSetPlayTime_3d61f0(V1feac0 *, double);
void GameDataSetWorld_3eddf0(void *, s32);
void GameDataCreate_3ee1f0(void *, void *);
void WorldDataMgrSetGameData_3f29d0(s32, void *);
void WorldDataMgrInit_3f3060(s32, void *);
extern u8 D_004B8A20[];
}

extern "C" void WorldDataRebuild_1feac0(s32 arg0)
{
    s32 spBC;
    s32 spB8;
    s32 spB4;
    u8 sp60[0x54] __attribute__((aligned(16)));
    s32 temp_19;
    Obj001fedf0 *temp_2;
    s32 var_17;
    V1feac0 *temp_16;
    s32 off;
    temp_19 = GetWorldDataMgr_1fedf0();
    temp_2 = GetGameData_1fede0();
    temp_16 = temp_2->unkC;
    var_17 = 0;
    if (arg0 != 0) {
        var_17 = temp_16->v3(sp60, 0x50);
    }
    MemStackReset_14d830(D_004B8A20);
    WorldDataMgrInit_3f3060(temp_19, D_004B8A20);
    GameDataCreate_3ee1f0(temp_2, D_004B8A20);
    GameDataSetWorld_3eddf0(temp_2, temp_19);
    WorldDataMgrSetGameData_3f29d0(temp_19, temp_2);
    if (arg0 != 0) {
        spBC = 0;
        spB8 = 0;
        spB4 = 0;
        off = UnpackWordTriple_370d70(sp60, var_17, &spBC, &spB8, &spB4);
        temp_16->v4(sp60 + off, spB4);
        OptionsSetPlayTime_3d61f0(temp_16, __builtin_bit_cast(double, (long long)(int)(0)));
    }
}
