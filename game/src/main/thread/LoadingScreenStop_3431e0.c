/* rgp:protos */
#define RGP_SELF_LoadingScreenStop_3431e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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

void LoadingScreenStop_3431e0(void)
{
    s32 t1;
    s32 t2;

    if (D_0047F650 > 0) {
        D_00482D70 = 0;
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
