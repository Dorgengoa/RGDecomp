/* rgp:protos */
#define RGP_SELF_CdDiskWatchWakeIsr_17ff10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 iPollSema(s32);
extern s32 iSignalSema(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047E038;
extern s32 D_00481218;
extern s32 D_0048121C;
extern s32 D_00481228;

void CdDiskWatchWakeIsr_17ff10(void)
{
    s32 r1;
    s32 rv3;
    s32 r2;

    if (D_00481218 != 0) {
        if (D_0048121C != 0 && D_0047E038 >= 0 && D_00481228 == 0) {
            r1 = iPollSema(D_0047E038);
            rv3 = r1;
            if (r1 < 0) {
                r2 = iSignalSema(D_0047E038);
                rv3 = r2;
            }
            return;
        }
        return;
    }
}
