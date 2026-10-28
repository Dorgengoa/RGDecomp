/* rgp:protos */
#define RGP_SELF_SifDmaSendSync_1c21e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void DelayThread_117618(s32);
extern void FlushCache(s32);
extern void SignalSema(s32);
extern void WaitSema(s32);
extern s32 sceSifDmaStat(s32);
extern s32 sceSifSetDma(s32 *, s32);
extern s32 D_00481514;

s32 SifDmaSendSync_1c21e0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp40[4] __attribute__((aligned(16)));
    s32 temp_2;
    s32 var_16;

    if (arg2 == 0) {
        return 0;
    }
    WaitSema(D_00481514);
    sp40[0] = arg0;
    sp40[1] = arg1;
    sp40[2] = arg2;
    sp40[3] = 0;
    FlushCache(0);
    temp_2 = sceSifSetDma(sp40, 1);
    if (temp_2 == 0) {
        var_16 = -1;
    } else {
        while (sceSifDmaStat(temp_2) >= 0) {
            DelayThread_117618(0xA);
        }
        var_16 = 0;
    }
    SignalSema(D_00481514);
    return var_16;
}
