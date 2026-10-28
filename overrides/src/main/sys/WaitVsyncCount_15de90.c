/* rg-override: replaces game/src/main/sys/WaitVsyncCount_15de90.c sha256 9858a845bbc499572c41250676265f57ac26c50cf3d23ceae98324dcde4ddcef
 * why: native frame driver (docs/NATIVE-THREADS.md "Frame driver"): the frame wait of every
 *      game flow is a driver point; with RG_THREADS=native the driven steps (VBlank services)
 *      run at the top of each round, so right after the VBLANK_START wake and before the flow
 *      continues (the order the HLE gave the higher-priority service threads).  The vsync
 *      semaphore protocol itself is unchanged; other modes run the generated loop. */
/* rgp:protos */
#define RGP_SELF_WaitVsyncCount_15de90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */

/* Spin until D_004810C4 has advanced `b` past `a`, signalling the IOP each
   time round. */

extern s32 D_004810C4;
extern s32 D_004810C0;
extern s32 D_0047DF18;
extern s32 DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern s32 WaitSema(s32 sema);

void WaitVsyncCount_15de90(s32 a, s32 b)
{
    s32 t;
    int drv = rg_frame_native(); /* rg-override */

    if (drv) /* rg-override: a logic tick (main flow; paced mode reports them) */
        rg_frame_frame_wait();

    for (;;) {
        if (drv) /* rg-override: driver point */
            rg_frame_point();
        if (D_004810C4 - a >= b) {
            break;
        }
        t = DisableIntr_120660();
        D_004810C0 = 1;
        if (t != 0) {
            EnableIntr_1206b0();
        }
        WaitSema(D_0047DF18);
    }
}
