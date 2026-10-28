/* rg-override: replaces game/src/main/ui/LoadingScreenRequestEnd_343100.c sha256 6bd293c3d3e1e7cc328cb5855977a02d345cdd8c93afb03507b0c60f3181513c
 * why: native frame driver (docs/NATIVE-THREADS.md "Frame driver"): its only caller,
 *      GameSessionInit_1f5d80, polls it with DelayThread(10) until it succeeds; with RG_THREADS=native
 *      the wait happens here, as a condition wait in the driver (woken when another thread or
 *      handler ran), then the original body makes the state change */
/* rgp:protos */
#define RGP_SELF_LoadingScreenRequestEnd_343100 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482D78;
extern s32 D_004E897C;

/* rg-override: the loading screen is in state 3 or 4 (its "ready to end" states) */
static int rg_LsCanEnd(void *arg)
{
    (void)arg;
    return (u32)(D_00482D78 + -3) < 2;
}

s32 LoadingScreenRequestEnd_343100(void)
{
    s32 t0;

    if (rg_frame_native()) /* rg-override: the caller's poll loop is a condition wait */
        rg_frame_wait_cond(rg_LsCanEnd, 0, "LoadingScreenRequestEnd");

    t0 = D_00482D78;
    if ((u32)(t0 + -3) < 2) {
        *(s32 *)&D_004E897C = 0x3F800000;
        D_00482D78 = 5;
        return 1;
    }
    return 0;
}
