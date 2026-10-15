#include "types.h"

extern const f32 D_0045B078[2];
extern const f32 D_0045B080[2];
extern const f32 D_0045B088[2];

extern void ScriptSlotStoreFloatRef_3347d0(f32 x);

s32 ScriptCmdGetGravity_3326d0(void)
{
    ScriptSlotStoreFloatRef_3347d0(2.0f * (D_0045B088[0] * (D_0045B080[0] / (D_0045B078[0] * D_0045B078[0]))));
    return 1;
}
