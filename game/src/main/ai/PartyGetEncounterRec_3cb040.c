/* rgp:protos */
#define RGP_SELF_PartyGetEncounterRec_3cb040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj1 * D_00483894;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x7E];
    s16 m7E;
    s16 m80;
};

struct Obj1 {
    u8 pad000[0x70];
    s32 m70;
};

int PartyGetEncounterRec_3cb040(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s16 t1;
    s16 t2;
    s32 t3;

    t0 = D_00483894;
    t1 = p0->m7E;
    t2 = p0->m80;
    t3 = D_00483894->m70;
    return GroupGetRecordById_402240(t3, (long long)(t1), (long long)(t2));
}
