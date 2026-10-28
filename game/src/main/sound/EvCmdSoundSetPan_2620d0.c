/* rgp:protos */
#define RGP_SELF_EvCmdSoundSetPan_2620d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

/*rgp*/
/*rgp*/

s32 EvCmdSoundSetPan_2620d0(R8 *q)
{
    s32 a;
    s32 b;
    s32 c;

    a = ScriptGetInt_26a2a0(q++);
    b = ScriptGetInt_26a2a0(q++);
    c = ScriptGetInt_26a2a0(q++);
    SoundSetPan_1b8590(a, b, c, 0);
    return 1;
}
