/* rgp:protos */
#define RGP_SELF_EvCmdSoundPlay_262250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/         /* extern */
/*rgp*/              /* extern */
/*rgp*/                   /* extern */
/*rgp*/                              /* extern */

s32 EvCmdSoundPlay_262250(s64 *arg0, s32 arg1) {
    s32 a;
    s32 b;
    s32 c;

    switch (arg1) {
    case 2:
        a = ScriptGetInt_26a2a0((s32)arg0++);
        SoundPlayDefault_1b9ae0(a, ScriptGetInt_26a2a0((s32)arg0), 0);
        return 1;
    case 3:
        a = ScriptGetInt_26a2a0((s32)arg0++);
        b = ScriptGetInt_26a2a0((s32)arg0++);
        SoundPlayVol_1b9ac0(a, b, ScriptGetInt_26a2a0((s32)arg0), 0);
        return 1;
    case 4:
        a = ScriptGetInt_26a2a0((s32)arg0++);
        b = ScriptGetInt_26a2a0((s32)arg0++);
        c = ScriptGetInt_26a2a0((s32)arg0++);
        SoundPlayVolPan_1b9aa0(a, b, c, ScriptGetInt_26a2a0((s32)arg0), 0);
        return 1;
    default:
        return 0;
    }
}
