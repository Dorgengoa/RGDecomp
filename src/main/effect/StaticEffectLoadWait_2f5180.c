#include "types.h"

extern void DelayThread_117618(s32);
extern s16 *SysGetModeMsg_1c39b0(void);
extern s32 LoaderCountQueued_1cd620(s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void StaticEffectLoad_2014a0(s32);
extern void EffectMgrLoadPollGlobal_2d8880(void);
extern void LoaderTickGlobal_2f74c0(void);

void StaticEffectLoadWait_2f5180(void) {
    s32 t4;
    s32 t16;

    t4 = *SysGetModeMsg_1c39b0();
    if (t4 == 6 || t4 == 2) return;
        StaticEffectLoad_2014a0(t4);
        t16 = GetLoaderMgr_1f59d0();
        for (;;) {
            LoaderTickGlobal_2f74c0();
            EffectMgrLoadPollGlobal_2d8880();
            if (LoaderCountQueued_1cd620(t16) <= 0) {
                break;
            }
            DelayThread_117618(0xA);
        }
}
