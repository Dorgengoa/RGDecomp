/* rgp:protos */
#define RGP_SELF_ModelDrawSorted_14f650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ModelDrawSorted_14f650(void *a, void *b, void *c)
{
    if (ModelUpdateFrameWorlds_1502b0(a, b) == 0) {
        return 0;
    }
    ModelMeshUpdateBoundsMaybe_150170(a, c);
    if (ModelPrepareDrawMaybe_14f760(a, b, c) == 0) {
        return 0;
    }
    return ModelQueueSortedPackets_14f0d0(a, b, c);
}
