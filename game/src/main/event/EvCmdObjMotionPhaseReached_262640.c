/* rgp:protos */
#define RGP_SELF_EvCmdObjMotionPhaseReached_262640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481F78;

s32 EvCmdObjMotionPhaseReached_262640(s64 *arg0) {
    s32 r;
    f32 f;

    r = ((s32)ObjRecGetLiveObject_1c4a90(D_00481F78, ScriptGetInt_26a2a0((s32)arg0++)));
    if (r == 0) {
        return 0;
    }
    f = TaggedGetFloat_26a280((s32)arg0++);
    ScriptSetRefInt_26a1e0((s32)arg0, ModelObjGetMotionPhase_1add70(r) >= f);
    return 1;
}
