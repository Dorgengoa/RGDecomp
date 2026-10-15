#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 StreamPlayChan_1cda20(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdStreamChanPlay_25ce20(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetLoaderMgr_1f59d0();
    r1 = ScriptGetInt_26a2a0(p0);
    r2 = StreamPlayChan_1cda20(r0, r1, 1.0f);
    return 1;
}
