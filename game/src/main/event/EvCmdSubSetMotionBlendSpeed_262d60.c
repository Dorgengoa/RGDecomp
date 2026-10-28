/* rgp:protos */
#define RGP_SELF_EvCmdSubSetMotionBlendSpeed_262d60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047DD3C;

s32 EvCmdSubSetMotionBlendSpeed_262d60(s64 *arg0, s32 arg1)
{
    f32 var_f20;
    s32 temp_16;
    s32 temp_2;

    var_f20 = D_0047DD3C;
    temp_16 = ScriptGetInt_26a2a0((s32)arg0++);
    if (arg1 > 0) {
        var_f20 = TaggedGetFloat_26a280((s32)arg0);
    }
    temp_2 = ((s32)EvtGetSubMachine_26abb0(temp_16));
    if (temp_2 == 0) {
        return 0;
    }
    if (var_f20 <= 0.0f) {
        var_f20 = D_0047DD3C;
    }
    EventSubNodeAddSetMotionBlendSpeed_251170(temp_2, var_f20);
    return 1;
}
