#include "types.h"

/* MAIN PlayTimeStep_2f7570.  $f20 is a callee-saved float held across
   GameSceneGetTimeStep_1ceba0, i.e. a named local for the int-to-float conversion. */

extern void FrameCounterInc_1c6b00(void);
extern void *GetGameData_1fede0(void);
extern s32 ReturnZero_207f40(void);
extern void *GetDrawCtx_15de80(void);
extern void *GetCurrentScene_1f5be0(void);
extern s32 DrawEnvGetVsyncInterval_144130(void *);
extern f32 GameSceneGetTimeStep_1ceba0(void *);
extern void PlayTimeTick_3e6360(void *, f32);

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
