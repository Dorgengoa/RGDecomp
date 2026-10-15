#include "types.h"

extern s32 ObjMgrUnloadDead_2f2fa0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdObjMgrUnloadDead_2699b0(void)
{
    s32 r;

    r = ObjMgrUnloadDead_2f2fa0(1);
    return 1;
}
