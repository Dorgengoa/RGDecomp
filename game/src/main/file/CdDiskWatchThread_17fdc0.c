/* rgp:protos */
#define RGP_SELF_CdDiskWatchThread_17fdc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 sceCdGetDiskType_12a9d8(void);
/*rgp*/
extern void SignalSema(s32);
extern void WaitSema(s32);
extern s32 D_0047E028;
extern s32 D_0047E038;
extern s32 D_004811C4;
extern s32 D_0048121C;
extern s32 D_00481220;
extern s32 D_00481224;
extern s32 D_00481228;

void CdDiskWatchThread_17fdc0(void) {
    s32 ok;

    do {
        ok = !(D_00481220 != 0);
        if (!ok) {
            break;
        }
        WaitSema(D_0047E038);
        if (D_0048121C != 0 && D_00481228 == 0) {
            if (D_0047E028 >= 0) {
                WaitSema(D_0047E028);
            }
            D_004811C4 += 1;
            if (sceCdGetDiskType_12a9d8() == 0) {
                CdWaitFileFound_180290();
            }
            if (D_0047E028 >= 0) {
                SignalSema(D_0047E028);
            }
            D_004811C4 -= 1;
        }
        ok = !(D_00481220 != 0);
    } while (ok);
    D_00481224 = 1;
}
