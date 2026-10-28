/* rgp:protos */
#define RGP_SELF_FileCdSearchLocked_180360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same semaphore-guarded dispatch shape as the already-admitted sibling
   src/s12c/CdDiskWatchThread_17fdc0.c / src/s12h/CdWaitFileFound_180290.c -- the redundant
   `if (D_004811DC != 0) {..} else {var_6=0;}` inside the already-true
   `D_004811DC != 0` branch is written LITERALLY in those sibling units
   too, so it is reproduced here rather than simplified away. */

extern s32 sceCdLayerSearchFile_1297e0(void *, s8 *, s32);
extern s32 sceCdSearchFile_129ae0(void *, s8 *);
extern void SignalSema(s32);
extern void WaitSema(s32);
extern s32 D_0047E028;
extern s32 D_004811C4;
extern s32 D_004811DC;
extern s32 D_004811E0;

s32 FileCdSearchLocked_180360(void *arg0, s8 *arg1)
{
    s32 var_2;
    s32 var_6;

    if (D_0047E028 >= 0) {
        WaitSema(D_0047E028);
    }
    D_004811C4 += 1;
    if (D_004811DC != 0) {
        if (D_004811DC == 0) {
            var_6 = 0;
        } else {
            var_6 = D_004811E0;
        }
        var_2 = sceCdLayerSearchFile_1297e0(arg0, arg1, var_6);
    } else {
        var_2 = sceCdSearchFile_129ae0(arg0, arg1);
    }
    if (D_0047E028 >= 0) {
        SignalSema(D_0047E028);
    }
    D_004811C4 -= 1;
    return var_2;
}
