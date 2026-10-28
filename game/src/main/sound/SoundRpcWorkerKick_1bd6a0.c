/* rgp:protos */
#define RGP_SELF_SoundRpcWorkerKick_1bd6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
            return;
        }
        D_00481504 = 0;
        return;
    }
}
