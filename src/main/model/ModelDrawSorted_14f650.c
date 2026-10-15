#include "types.h"

extern s32 ModelUpdateFrameWorlds_1502b0(void *a, void *b, void *c);
extern void ModelMeshUpdateBoundsMaybe_150170(void *a, void *c);
extern s32 ModelPrepareDrawMaybe_14f760(void *a, void *b, void *c);
extern s32 ModelQueueSortedPackets_14f0d0(void *a, void *b, void *c);

s32 ModelDrawSorted_14f650(void *a, void *b, void *c)
{
    if (ModelUpdateFrameWorlds_1502b0(a, b, c) == 0) {
        return 0;
    }
    ModelMeshUpdateBoundsMaybe_150170(a, c);
    if (ModelPrepareDrawMaybe_14f760(a, b, c) == 0) {
        return 0;
    }
    return ModelQueueSortedPackets_14f0d0(a, b, c);
}
