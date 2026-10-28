/* rgp:protos */
#define RGP_SELF_CharaSysGetEncounterEntryIdMaybe_3a36f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x238];
    struct Obj1 *m238;
};

struct Obj1 {
    u8 pad000[0x14];
    struct Obj2 *m14;
};

struct Obj2 {
    s16 m00;
};

s32 CharaSysGetEncounterEntryIdMaybe_3a36f0(struct Obj0 *p0)
{
    struct Obj2 * t1;
    s16 t2;

    t1 = p0->m238->m14;
    if (t1 != 0) {
        t2 = p0->m238->m14->m00;
        return t2;
    }
    return -1;
}
