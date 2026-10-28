/* rgp:protos */
#define RGP_SELF_PlayTimeStep_2f7570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN PlayTimeStep_2f7570.  $f20 is a callee-saved float held across
   GameSceneGetTimeStep_1ceba0, i.e. a named local for the int-to-float conversion. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void PlayTimeStep_2f7570(void)
{
    void *t;
    void *a;
    void *b;
    f32 n;

    FrameCounterInc_1c6b00();
    t = GetGameData_1fede0();
    if (ReturnZero_207f40() == 0) {
        a = GetDrawCtx_15de80();
        b = GetCurrentScene_1f5be0();
        n = (f32)DrawEnvGetVsyncInterval_144130(a);
        PlayTimeTick_3e6360(t, n * GameSceneGetTimeStep_1ceba0(b));
    }
}
