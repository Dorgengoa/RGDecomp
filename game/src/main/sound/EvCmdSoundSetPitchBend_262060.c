/* rgp:protos */
#define RGP_SELF_EvCmdSoundSetPitchBend_262060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

/*rgp*/
/*rgp*/

s32 EvCmdSoundSetPitchBend_262060(R8 *q)
{
    s32 a;
    s32 b;
    s32 c;

    a = ScriptGetInt_26a2a0(q++);
    b = ScriptGetInt_26a2a0(q++);
    c = ScriptGetInt_26a2a0(q++);
    SoundSetPitchBend_1b8360(a, b, c, 0);
    return 1;
}
