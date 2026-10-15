#include "types.h"

/* jalr $25 (jalr-is-cpp-virtual lever): vtable pointer is embedded directly
   at temp_2+0x20 (this=temp_2, K=0, pad000[0x20] before the injected vptr),
   slot 8 -> N=(8-8)/4=0. */

class VE {
public:
    u8 pad000[0x20];
    virtual s32 v0();
};

extern "C" void *ObjRecTableGet_1c3fe0(void);
extern "C" s32 ParamTableGetRec_1cfbc0(s32, s32);
extern "C" void ParamRecReset_1cfdb0(s32);
extern "C" void ActionMgrRemoveWeaponAllGlobal_1fb4a0(s32);

extern "C" void GameSceneObjReleaseMaybe_1cfc50(s32 arg0, s32 arg1)
{
    s32 temp_2_2;
    VE *temp_2;

    temp_2 = (VE *)ObjRecTableGet_1c3fe0();
    if (temp_2 != NULL) {
        temp_2_2 = ParamTableGetRec_1cfbc0(arg0, arg1);
        if (temp_2_2 != 0) {
            ParamRecReset_1cfdb0(temp_2_2);
        }
        temp_2->v0();
        ActionMgrRemoveWeaponAllGlobal_1fb4a0(arg1);
    }
}
