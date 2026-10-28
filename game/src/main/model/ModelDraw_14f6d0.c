/* rgp:protos */
#define RGP_SELF_ModelDraw_14f6d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ModelDraw_14f6d0(s32 arg0, s32 arg1, s32 arg2)
{
    if (arg2 == 0) {
        return 0;
    }
    if (ModelUpdateFrameWorlds_1502b0((void *)arg0, (int)arg1) == 0) {
        return 0;
    }
    ModelMeshUpdateBoundsMaybe_150170(arg0, arg2);
    if (ModelPrepareDrawMaybe_14f760(arg0, arg1, arg2) == 0) {
        return 0;
    }
    return ModelEmitDrawPacketsMaybe_14ec20(arg0, arg1, arg2);
}
