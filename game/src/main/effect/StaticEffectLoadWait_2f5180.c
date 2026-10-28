/* rgp:protos */
#define RGP_SELF_StaticEffectLoadWait_2f5180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void DelayThread_117618(s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void StaticEffectLoadWait_2f5180(void) {
    s32 t4;
    s32 t16;

    t4 = *((s16 *)SysGetModeMsg_1c39b0());
    if (t4 == 6 || t4 == 2) return;
        StaticEffectLoad_2014a0();
        t16 = ((s32)GetLoaderMgr_1f59d0());
        for (;;) {
            LoaderTickGlobal_2f74c0();
            EffectMgrLoadPollGlobal_2d8880();
            if (LoaderCountQueued_1cd620(t16) <= 0) {
                break;
            }
            DelayThread_117618(0xA);
        }
}
