#include "types.h"

extern s32 ScriptVmReset_176bd0(void *);
extern s32 MemStackAllocQw_14d950(s32, s32);
extern s32 ScriptVmInit_176af0(void *, s32, s32, s32, s32, s32);
extern s32 SystemVmBuildCmdTable_2590b0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 gSystemVm[];

s32 SystemVmLoadScript_250ac0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    if (p0 == 0 || p2 == 0) {
        r0 = ScriptVmReset_176bd0(gSystemVm);
        return r0;
    }
    r1 = MemStackAllocQw_14d950(p2, 0x40);
    r2 = MemStackAllocQw_14d950(p2, 0x180);
    r3 = ScriptVmInit_176af0(gSystemVm, p0, r1, 0x80, r2, 0x200);
    r4 = SystemVmBuildCmdTable_2590b0(gSystemVm);
    return r4;
}
