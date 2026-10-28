/* rgp:protos */
#define RGP_SELF_EvCmdSoundSetReverb_261b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_261b20;
/*rgp*/
/*rgp*/

s32 EvCmdSoundSetReverb_261b20(E8_261b20 *p0)
{
    s32 a;
    s32 b;
    s32 c;

    a = ScriptGetInt_26a2a0(p0++);
    b = ScriptGetInt_26a2a0(p0++);
    c = ScriptGetInt_26a2a0(p0);
    SoundSetReverb_1bb610(a, b, c);
    return 1;
}
