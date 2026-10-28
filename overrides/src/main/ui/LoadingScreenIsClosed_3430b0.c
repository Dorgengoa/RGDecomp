/* rg-override: replaces game/src/main/ui/LoadingScreenIsClosed_3430b0.c sha256 699595feffa5eccac6f75cd2593889025661258e09967e3444889344b8f01162
 * why: native frame driver (docs/NATIVE-THREADS.md "Frame driver"): its only caller,
 *      GameSessionInit_1f5d80, polls it with DelayThread(10); with RG_THREADS=native the wait
 *      happens here as a condition wait in the driver, then the test returns 1 */
/* rgp:protos */
#define RGP_SELF_LoadingScreenIsClosed_3430b0 1
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
static int rg_LsClosed(void *arg)
{
    (void)arg;
    return D_00482D78 == 8;
}

u8 LoadingScreenIsClosed_3430b0(void)
{
    if (rg_frame_native()) /* rg-override: the caller's poll loop is a condition wait */
        rg_frame_wait_cond(rg_LsClosed, 0, "LoadingScreenIsClosed");
    return (D_00482D78 == 8);
}
