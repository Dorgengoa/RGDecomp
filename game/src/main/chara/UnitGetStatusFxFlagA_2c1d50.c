/* rgp:protos */
#define RGP_SELF_UnitGetStatusFxFlagA_2c1d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x409];
    u8 m409;
};

u64 UnitGetStatusFxFlagA_2c1d50(struct Obj0 *p0)
{
    return (((u64)(((s64)p0->m409) << 0x3D)) >> 0x3F);
}
