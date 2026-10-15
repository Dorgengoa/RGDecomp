#include "types.h"

extern void EffectResSlotsReset_2e30c0(void *);
extern void ScriptVmCmdTableInit_32c8b0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x407C];
    s32 m407C;
};

void EffectMgrResetSlots_2e3270(struct Obj0 *p0)
{
    EffectResSlotsReset_2e30c0(p0);
    ScriptVmCmdTableInit_32c8b0();
    p0->m407C = 0;
}
