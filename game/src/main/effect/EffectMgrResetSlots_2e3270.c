/* rgp:protos */
#define RGP_SELF_EffectMgrResetSlots_2e3270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

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
