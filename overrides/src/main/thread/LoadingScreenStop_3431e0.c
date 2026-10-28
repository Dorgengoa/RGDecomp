/* rg-override: replaces game/src/main/thread/LoadingScreenStop_3431e0.c sha256 357cf20fc3ecc25431644f9dddbb58fb7e6022f4b7e9b9253dcc25196be83636
 * why: native frame driver (docs/NATIVE-THREADS.md "Frame driver"): the wait for the
 *      loading-screen thread to leave its loop (DelayThread(100) polls) is a condition wait in the
 *      driver with RG_THREADS=native|frame.  Slice 4: the loading screen's frame loop
 *      (LoadingScreenThread_343510) is registered here as the frame driver's second game
 *      coroutine (a "flow" of the frame-driven kernel, RG_THREADS=native). */
/* rgp:protos */
#define RGP_SELF_LoadingScreenStop_3431e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */

extern void DelayThread_117618(s32);
extern void TerminateThread(s32);
extern void DeleteThread(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F650;
extern s32 D_00482D70;
extern s32 D_00482D74;

/* rg-override: the loading-screen thread has left its loop */
static int rg_LsThreadDone(void *arg)
{
    (void)arg;
    return D_00482D74 != 0;
}

void LoadingScreenStop_3431e0(void)
{
    s32 t1;
    s32 t2;

    if (D_0047F650 > 0) {
        D_00482D70 = 0;
        if (rg_frame_native()) { /* rg-override: condition wait instead of 100 us polls */
            rg_frame_wait_cond(rg_LsThreadDone, 0, "LoadingScreenStop");
        }
        while (!D_00482D74) {
            DelayThread_117618(0x64);
        }
        t1 = D_0047F650;
        TerminateThread(t1);
        t2 = D_0047F650;
        DeleteThread(t2);
        D_0047F650 = -1;
    }
}

/* rg-override: slice 4 (docs/NATIVE-THREADS.md): the loading screen stays a game coroutine
 * (its own stack, resumed by the frame driver when its vsync wait is satisfied) */
extern void LoadingScreenThread_343510(void);
__attribute__((constructor)) static void rg_LsFlowRegister(void)
{
    rg_threads_flow((void *)LoadingScreenThread_343510, "LoadingScreenThread_343510");
}
