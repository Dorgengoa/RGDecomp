/* rgp:protos */
#define RGP_SELF_WorldOnStateFlag256Changed_3ed930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
    u8 pad01C[0x4];
    s32 m20;
    u8 pad024[0x8];
    u8 m2C;
};

s32 WorldOnStateFlag256Changed_3ed930(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    u8 t0;
    s32 rv3;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 r2;

    t0 = p0->m2C;
    rv3 = 1;
    if ((t0 & 1) != 0) {
        rv3 = 0;
    } else {
        if ((p2 & 0xFF) != (p3 & 0xFF)) {
            t1 = p0->m18;
            PartySelectEncounter_3c9c30(t1);
            t2 = p0->m20;
            CharaSysEncounterDistRoll_3a59d0(t2, 0);
            t3 = p0->m18;
            r2 = PartyRefreshBgmOverride_3ca730(t3);
        }
        rv3 = 1;
    }
    return rv3;
}
