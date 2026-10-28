/* rgp:protos */
#define RGP_SELF_EvCmdSoundSetEntryVolume_262140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSoundSetEntryVolume_262140(s64 *arg0)
{
    s32 a;
    s32 b;

    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetInt_26a2a0((s32)arg0++);
    switch (*(s32 *)arg0) {
    case 0:
        SoundSetEntryVolume_1b87c0(a, b, ScriptGetInt_26a2a0((s32)arg0), 0);
        break;
    case 1:
        SoundSetEntryVolumeScaled_1b9820(a, b, 0, TaggedGetFloat_26a280((s32)arg0));
        break;
    default:
        return 0;

    }
    return 1;
}
