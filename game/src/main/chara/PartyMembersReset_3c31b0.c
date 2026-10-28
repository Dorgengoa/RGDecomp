/* rgp:protos */
#define RGP_SELF_PartyMembersReset_3c31b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18C];
    s16 m18C;
    s16 m18E;
};

void PartyMembersReset_3c31b0(struct Obj0 *p0)
{
    s32 l0;
    s32 l1;
    s32 l2;
    s32 l3;

    p0->m18C = 3;
    p0->m18E = -1;
    l0 = 3;
    l1 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l1 << 1) + 0x190) = -1;
        l0 = ((l1 + 1) < 3);
        l1 = (l1 + 1);
    } while (l0 != 0);
    l2 = l0;
    l3 = 0;
    do {
        *(s16 *)((u8 *)p0 + (l3 << 1) + 0x196) = -1;
        l2 = ((l3 + 1) < 7);
        l3 = (l3 + 1);
    } while (l2 != 0);
}
