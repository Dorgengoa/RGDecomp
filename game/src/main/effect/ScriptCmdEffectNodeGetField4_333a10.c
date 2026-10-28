/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectNodeGetField4_333a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004826E0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s16 m04;
};

s32 ScriptCmdEffectNodeGetField4_333a10(s32 p0)
{
    s32 r;

    r = (ScriptSlotStoreIntRef_3347f0(p0, D_004826E0->m04), (s32)0);
    return 1;
}
