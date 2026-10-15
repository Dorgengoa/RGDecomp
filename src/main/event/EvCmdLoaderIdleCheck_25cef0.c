#include "types.h"

extern s32 LoadingIconCanHide_2ee930(void);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderTick_1ccc30(s32);
extern s32 LoaderCountQueued_1cd620(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdLoaderIdleCheck_25cef0(s32 p0, s32 p1)
{
    s32 rv9;
    s32 r0;
    s32 rv8;
    s32 r1;
    s32 r2;
    s32 rv7;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;

    rv9 = rv8;
    if (p1 <= 0) {
        rv9 = 0;
    } else {
        r0 = LoadingIconCanHide_2ee930();
        rv8 = rv7;
        if (r0 == 0) {
            r1 = ScriptSetRefInt_26a1e0(p0, 0);
            rv8 = 1;
        } else {
            r2 = GetLoaderMgr_1f59d0();
            rv7 = 1;
            if (r2 == 0) {
                rv7 = 0;
            } else {
                r3 = LoaderTick_1ccc30(r2);
                r4 = LoaderCountQueued_1cd620(r2);
                if (r4 > 0) {
                    r5 = ScriptSetRefInt_26a1e0(p0, 0);
                } else {
                    r6 = ScriptSetRefInt_26a1e0(p0, 1);
                }
                rv7 = 1;
            }
            rv8 = rv7;
        }
        rv9 = rv8;
    }
    return rv9;
}
