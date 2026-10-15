#include "types.h"

extern s32 GetNpcObjTable_312860(void);
extern s32 ScriptGetInt_26a2a0(s32);
extern void NpcObjDeactivateById_2fb680(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdNpcObjDeactivate_260510(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = GetNpcObjTable_312860();
    r1 = ScriptGetInt_26a2a0(p0);
    NpcObjDeactivateById_2fb680(r0, r1);
    return 1;
}
