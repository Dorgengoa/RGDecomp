#include "types.h"

extern void *CharaGetHitInfo_214a00(s32);
extern void ScriptSlotStoreFloatRef_2cc8e0(s32, f32);
extern s32 D_004DB92C[];

s32 AiCmdGetLastHitPos_2c61e0(s32 arg0, s32 arg1)
{
    void *temp_2;

    if (arg1 < 3) {
        return 0;
    }
    ScriptSlotStoreFloatRef_2cc8e0(arg0, 0.0f);
    ScriptSlotStoreFloatRef_2cc8e0(arg0 + 8, 0.0f);
    ScriptSlotStoreFloatRef_2cc8e0(arg0 + 0x10, 0.0f);
    if (D_004DB92C[0] == 0) {
        return 0;
    }
    temp_2 = CharaGetHitInfo_214a00(D_004DB92C[0]);
    ScriptSlotStoreFloatRef_2cc8e0(arg0, *(f32 *)((u8 *)temp_2 + 0));
    ScriptSlotStoreFloatRef_2cc8e0(arg0 + 8, *(f32 *)((u8 *)temp_2 + 4));
    ScriptSlotStoreFloatRef_2cc8e0(arg0 + 0x10, *(f32 *)((u8 *)temp_2 + 8));
    return 1;
}
