#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderTick_1ccc30(s32);
extern s32 LoaderCountQueued_1cd620(s32);
extern s32 ScriptSetRefInt_249030(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdLoaderIsBusy_248db0(s32 p0, s32 p1)
{
    s32 rv5;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    rv5 = 1;
    if (p1 <= 0) {
        rv5 = 0;
    } else {
        r0 = GetLoaderMgr_1f59d0();
        r1 = LoaderTick_1ccc30(r0);
        r2 = LoaderCountQueued_1cd620(r0);
        if (r2 > 0) {
            r3 = ScriptSetRefInt_249030(p0, 1);
        } else {
            r4 = ScriptSetRefInt_249030(p0, 0);
        }
        rv5 = 1;
    }
    return rv5;
}
