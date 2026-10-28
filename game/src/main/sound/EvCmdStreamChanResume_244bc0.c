/* rgp:protos */
#define RGP_SELF_EvCmdStreamChanResume_244bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D288;

s32 EvCmdStreamChanResume_244bc0(s32 *arg0, s32 arg1) {
    f32 var_f20;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_f0;

    if (arg1 != 1) {
        return 0;
    }
    var_f20 = 1.0f;
    temp_2 = *arg0;
    if (temp_2 == 1) {
        var_f20 = TaggedGetFloat_2490d0((void *)arg0);
    } else if (temp_2 == 0) {
        temp_f0 = (s32)TaggedGetFloat_2490d0((void *)arg0);
        if (temp_f0 == 0) {
            var_f20 = 1.0f;
        }
        if (temp_f0 == 1) {
            var_f20 = D_0047D288;
        }
    }
    temp_2_2 = ((s32)GetStreamMgr_207ea0());
    StreamMgrPlayChan_1d6670(temp_2_2, 0, 0.0f);
    StreamMgrSetChanVolumeFade_1d63a0(temp_2_2, 0, 0, var_f20);
    return 1;
}
