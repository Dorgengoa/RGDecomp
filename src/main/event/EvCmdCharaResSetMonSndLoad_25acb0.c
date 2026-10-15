#include "types.h"

extern s32 GetCharaResMgr_1fdb60(void);
extern s32 ScriptGetInt_26a2a0(s32);
extern s32 CharaResMgrSetMonSndLoad_1f0050(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdCharaResSetMonSndLoad_25acb0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetCharaResMgr_1fdb60();
    r1 = ScriptGetInt_26a2a0(p0);
    r2 = CharaResMgrSetMonSndLoad_1f0050(r0, r1);
    return 1;
}
