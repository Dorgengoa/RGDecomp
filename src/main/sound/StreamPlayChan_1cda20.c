#include "types.h"

extern s32 GetStreamMgr_207ea0(void);
extern void StreamMgrPlayChan_1d6670(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void StreamPlayChan_1cda20(s32 p0, s32 p1, f32 fa0)
{
    s32 r0;

    r0 = GetStreamMgr_207ea0();
    StreamMgrPlayChan_1d6670(r0, p1, fa0);
}
