/* rgp:protos */
#define RGP_SELF_EvCmdVoiceFlagSetMaybe_261de0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern u8 D_004BDA20[0x400];

s32 EvCmdVoiceFlagSetMaybe_261de0(s64 *arg0, s32 arg1)
{
    (*(s32 *)D_004BDA20) = 1;
    ScriptGetInt_26a2a0((s32)arg0++);
    switch (arg1) {
    case 1:
        return ScriptCmdStubRelated_261e70();
    case 2:
        return ((void)(ScriptGetInt_26a2a0((s32)arg0)), ScriptCmdStubRelated_261e70());
    default:
        return 0;
    }
}
