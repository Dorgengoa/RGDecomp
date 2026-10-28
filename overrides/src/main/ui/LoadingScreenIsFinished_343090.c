/* rg-override: replaces game/src/main/ui/LoadingScreenIsFinished_343090.c sha256 457ac898b1fdee9b0d22a18e60c800e12ee1ad138f7964fd3fd00f25999cfcff
 * why: native frame driver (docs/NATIVE-THREADS.md "Frame driver"): its only caller,
 *      GameSessionInit_1f5d80, polls it with DelayThread(10) (1.7M polls per NEW GAME load; the
 *      loop's other exit, IsTgsDemoBuild_207f20, is a constant 0); with RG_THREADS=native the wait
 *      happens here as a condition wait in the driver, then the test returns 1 */
/* rgp:protos */
#define RGP_SELF_LoadingScreenIsFinished_343090 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482D78;

/* rg-override */
static int rg_LsFinished(void *arg)
{
    (void)arg;
    return D_00482D78 == 7;
}

u8 LoadingScreenIsFinished_343090(void)
{
    if (rg_frame_native()) /* rg-override: the caller's poll loop is a condition wait */
        rg_frame_wait_cond(rg_LsFinished, 0, "LoadingScreenIsFinished");
    return (D_00482D78 == 7);
}
