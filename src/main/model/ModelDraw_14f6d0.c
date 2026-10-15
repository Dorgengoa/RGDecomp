#include "types.h"

extern s32 ModelUpdateFrameWorlds_1502b0(void);
extern void ModelMeshUpdateBoundsMaybe_150170(s32, s32);
extern s32 ModelPrepareDrawMaybe_14f760(s32, s32, s32);
extern s32 ModelEmitDrawPacketsMaybe_14ec20(s32, s32, s32);

s32 ModelDraw_14f6d0(s32 arg0, s32 arg1, s32 arg2)
{
    if (arg2 == 0) {
        return 0;
    }
    if (ModelUpdateFrameWorlds_1502b0() == 0) {
        return 0;
    }
    ModelMeshUpdateBoundsMaybe_150170(arg0, arg2);
    if (ModelPrepareDrawMaybe_14f760(arg0, arg1, arg2) == 0) {
        return 0;
    }
    return ModelEmitDrawPacketsMaybe_14ec20(arg0, arg1, arg2);
}
