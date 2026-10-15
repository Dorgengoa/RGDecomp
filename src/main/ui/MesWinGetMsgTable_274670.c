#include "types.h"

extern s32 MesWinGetMsgData_276e90(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MesWinGetMsgTable_274670(s32 p0)
{
    s32 r;

    r = MesWinGetMsgData_276e90(p0);
    return (r + 2);
}
