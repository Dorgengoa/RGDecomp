#include "types.h"

typedef struct {
    f32 unk0;
    f32 unk4;
} Obj002ee250;

extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);

s32 ScreenPointInBounds_2ee250(void *arg0, Obj002ee250 *arg1)
{
    s32 temp_16;

    temp_16 = GetDrawCtx_15de80();
    if (arg1->unk0 < 0.0f || !(arg1->unk0 <= 16.0f * (f32)DrawEnvGetWidth_1451e0(temp_16))) return 0;
    if (arg1->unk4 < 0.0f || !(arg1->unk4 <= 16.0f * (f32)DrawEnvGetHeight_1451d0(temp_16))) return 0;
    return 1;
}
