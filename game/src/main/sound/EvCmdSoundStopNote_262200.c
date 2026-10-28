/* rgp:protos */
#define RGP_SELF_EvCmdSoundStopNote_262200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/

s32 EvCmdSoundStopNote_262200(E8 *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0++);
    r1 = ScriptGetInt_26a2a0(p0);
    r2 = (SoundStopEntry_1b8bc0(r0, r1, 0), (s32)0);
    return 1;
}
