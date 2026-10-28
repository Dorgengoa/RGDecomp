/* rgp:protos */
#define RGP_SELF_MapScriptCmdAddMoveReqXyz_1e9bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapScriptCmdAddMoveReqXyz_1e9bc0(s32 arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f24;
    s32 temp_18;
    s32 temp_17;
    s32 temp_16;

    if (arg1 != 8) {
        return 0;
    }
    temp_18 = ((s32)GetMapSequencer_201a80());
    temp_17 = TaggedGetInt_1ea050(arg0);
    temp_16 = TaggedGetInt_1ea050(arg0 + 8);
    temp_f24 = TaggedGetFloat_1ea010(arg0 + 0x10);
    temp_f23 = TaggedGetFloat_1ea010(arg0 + 0x18);
    temp_f22 = TaggedGetFloat_1ea010(arg0 + 0x20);
    temp_f21 = TaggedGetFloat_1ea010(arg0 + 0x28);
    temp_f20 = TaggedGetFloat_1ea010(arg0 + 0x30);
    MapSequencerAddMoveReqXyz_2fa0d0(temp_18, temp_17, temp_16, temp_f24, temp_f23, temp_f22, temp_f21, temp_f20, TaggedGetFloat_1ea010(arg0 + 0x38));
    return 1;
}
