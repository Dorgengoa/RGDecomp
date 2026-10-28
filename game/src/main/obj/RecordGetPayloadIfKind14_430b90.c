/* rgp:protos */
#define RGP_SELF_RecordGetPayloadIfKind14_430b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x1188];
    struct Obj1 *m1188;
};

struct Obj1 {
    u8 pad000[0x4];
    s32 m04;
};

struct Obj1 *RecordGetPayloadIfKind14_430b90(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 t1;

    t0 = p0->m1188;
    t1 = p0->m1188->m04;
    if (t1 != 0x14) {
        return (struct Obj1 *)0;
    }
    return (struct Obj1 *)((u8 *)p0->m1188 + 0x20);
}
