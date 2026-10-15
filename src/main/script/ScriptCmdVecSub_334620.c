#include "types.h"

extern void ScriptSlotsToVec4_334810(f32 *v, void *p);
extern void ScriptSlotStoreFloatRef_3347d0(void *p, f32 x);

s32 ScriptCmdVecSub_334620(u8 *p, s32 kind)
{
    f32 v[3];

    if (kind != 6) {
        return 0;
    }
    ScriptSlotsToVec4_334810(v, p + 0x18);
    ScriptSlotStoreFloatRef_3347d0(p, *(f32 *)(*(s32 *)(p + 0x4) + 4) - v[0]);
    ScriptSlotStoreFloatRef_3347d0(p + 8, *(f32 *)(*(s32 *)(p + 0xC) + 4) - v[1]);
    ScriptSlotStoreFloatRef_3347d0(p + 0x10, *(f32 *)(*(s32 *)(p + 0x14) + 4) - v[2]);
    return 1;
}
