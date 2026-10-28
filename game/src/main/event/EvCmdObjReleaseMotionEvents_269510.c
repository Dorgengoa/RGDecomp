/* rgp:protos */
#define RGP_SELF_EvCmdObjReleaseMotionEvents_269510 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED -- `if (temp_2 == 0) return 1; ModelMotionEventReleaseHandlers_1b02b0(temp_2); return 1;`:
   the duplicated early return lays the call OUT OF LINE (bnel + b), s32 temp. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdObjReleaseMotionEvents_269510(s32 arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_2;

    if (arg1 <= 0) {
        return 0;
    }
    temp_16 = GetCurrentScene_1f5be0();
    temp_2 = ((s32)ObjRecGetLiveObject_1c4a90(temp_16, ScriptGetInt_26a2a0(arg0)));
    if (temp_2 == 0) {
        return 1;
    }
    ModelMotionEventReleaseHandlers_1b02b0(temp_2, 0);
    return 1;
}
