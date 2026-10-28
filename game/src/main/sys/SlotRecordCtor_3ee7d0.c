/* rgp:protos */
#define RGP_SELF_SlotRecordCtor_3ee7d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x340];
    s64 m340;
};

struct Obj0 *SlotRecordCtor_3ee7d0(struct Obj0 *p0)
{
    s32 r0;

    p0->m340 = 0;
    r0 = ((s32)SlotRecordReset_3eeca0(p0));
    return p0;
}
