/* rgp:protos */
#define RGP_SELF_EquipSlotGetRecName_3a07a0 1
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
    u8 pad000[0x4];
    struct Obj1 *m04;
};

struct Obj1 {
    u8 pad000[0x8];
    s32 m08;
};

s32 EquipSlotGetRecName_3a07a0(struct Obj0 *p0)
{
    return p0->m04->m08;
}
