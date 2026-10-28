/* rgp:protos */
#define RGP_SELF_BattleEncounterIsLoadingMaybe_2f2530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
    u8 pad01C[0x4];
    struct Obj1 *m20;
};

struct Obj1 {
    u8 pad000[0x238];
    struct Obj2 *m238;
};

struct Obj2 {
    u8 pad000[0x18];
    s32 m18;
};

s32 BattleEncounterIsLoadingMaybe_2f2530(void)
{
    struct Obj0 *r0;
    struct Obj2 * t1;
    s32 rv1;
    s32 r2;
    s32 t3;
    s32 r3;
    s32 l4;
    s32 t4;
    s32 r5;
    s32 r6;
    s32 r7;

    r0 = (struct Obj0 *)GetGameData_1fede0();
    t1 = r0->m20->m238;
    if (t1 != 0) {
        rv1 = t1->m18;
    } else {
        rv1 = 0;
    }
    if (rv1 == 0) {
        return 0;
    }
    r2 = ((s32)GetCharaResMgr_1fdb60());
    t3 = r0->m18;
    r3 = PartyCountMembers_3c2010(t3, 1, 1);
    l4 = 0;
    while (l4 < r3) {
        t4 = r0->m18;
        r5 = ((short)PartyGetMemberId_3c2490(t4, l4));
        r6 = ((unsigned char)CharaResSptLoadDoneMaybe_1f08f0(r2, r5));
        if (r6 == 0) {
            return 1;
        }
        l4 = (l4 + 1);
    }
    r7 = BattleEncounterUnitsIsLoadingMaybe_2f2880();
    return r7;
}
