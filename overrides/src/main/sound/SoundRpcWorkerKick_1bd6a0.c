/* rg-override: replaces game/src/main/sound/SoundRpcWorkerKick_1bd6a0.c sha256 1c586eaf147fb375395872580fb07fe6247e25dba2d1293df5950e41cfe499c3
 * why: native frame driver (docs/NATIVE-THREADS.md "Driven threads"): the only caller,
 *      SoundStreamSlotShutdown_1bdfd0, busy-waits on the stream slot's state around this
 *      kick.  On retail the SignalSema switched at once to the higher-priority slot thread
 *      (and the stream thread it wakes ran before main resumed); the driven slot step runs
 *      only at a driver point, which that loop never reached (Insectron return-to-title
 *      hang, BRINGUP-HISTORY 2026-10-25 (stream close)).  The kick ends in a driver point. */
/* rgp:protos */
#define RGP_SELF_SoundRpcWorkerKick_1bd6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "port/native_threads.h" /* rg-override */

extern s32 PollSema(s32);
extern s32 SignalSema(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047E214;
extern s32 D_00481504;

void SoundRpcWorkerKick_1bd6a0(void)
{
    s32 t0;
    s32 t1;
    s32 r0;
    s32 t2;
    s32 r1;

    t0 = D_00481504;
    if (t0 == 0) {
        t1 = D_0047E214;
        D_00481504 = 1;
        r0 = PollSema(t1);
        if (r0 < 0) {
            t2 = D_0047E214;
            r1 = SignalSema(t2);
            D_00481504 = 0;
            rg_frame_point(); /* rg-override: as below */
            return;
        }
        D_00481504 = 0;
        rg_frame_point(); /* rg-override: the woken slot step (and what it wakes) runs here */
        return;
    }
}
