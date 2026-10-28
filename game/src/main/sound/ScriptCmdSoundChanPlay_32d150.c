/* rgp:protos */
#define RGP_SELF_ScriptCmdSoundChanPlay_32d150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdSoundChanPlay_32d150(E8 *p0, s32 p1)
{
    s32 a;
    f32 t;
    s32 r;

    if (p1 <= 0) {
        return 0;
    }
    a = ScriptSlotGetInt_3348b0(p0);
    t = 1.0f;
    if (p1 > 1) {
        t = ScriptSlotGetFloat_334890(p0 + 1);
    }
    r = GetCurrentScene_1f5be0();
    GameSceneSoundSlot5PlaySeVol_1d05d0(r, a, t);
    return 1;
}
