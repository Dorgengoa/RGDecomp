/* rgp:protos */
#define RGP_SELF_DamagePopupListInitCullDist_2d8890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
};

s32 DamagePopupListInitCullDist_2d8890(void)
{
    s32 r0;
    s32 r1;
    struct Obj0 *r2;
    s32 t0;
    s32 r3;
    s32 rv5;
    s32 r4;

    r0 = ((s32)GetDamagePopupList_2d9020());
    r1 = (DamagePopupListSetDefaultCullDist_2d3210(r0), (s32)0);
    r2 = GetGameData_1fede0();
    t0 = r2->m20;
    r3 = CharaSysGetEncounterIdMaybe_3a36d0(t0);
    rv5 = r3;
    if (r3 == 0x271B) {
        r4 = (DamagePopupListSetCullDist_2d2e60(r0, -1.0f), (s32)0);
        rv5 = r4;
    }
    return rv5;
}
