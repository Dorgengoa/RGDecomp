/* rgp:protos */
#define RGP_SELF_ScriptCmdGetSceneTimeStep_3325d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ScriptCmdGetSceneTimeStep_3325d0(s32 p0, s32 p1)
{
    s32 r0;
    f32 r1;

    if (p1 != 1) {
        return 0;
    }
    r0 = GetCurrentScene_1f5be0();
    r1 = GameSceneGetTimeStep_1ceba0(r0);
    ScriptSlotStoreFloatRef_3347d0(p0, r1);
    return 1;
}
