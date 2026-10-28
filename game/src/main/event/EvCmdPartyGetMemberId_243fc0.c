/* rgp:protos */
#define RGP_SELF_EvCmdPartyGetMemberId_243fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E8 { s32 a; s32 b; };

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

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    s32 m18;
};

s32 EvCmdPartyGetMemberId_243fc0(struct E8 *p0, s32 p1)
{
    struct Obj0 *r0;
    s32 r2;
    s32 t0;
    s32 r3;
    s32 t1;
    s32 r4;
    s32 t2;
    s32 r7;
    s32 t3;
    s32 r8;

    r0 = GetGameData_1fede0();
    if (p1 == 2) {
        goto ok;
    }
    if (p1 == 3) {
        goto ok;
    }
    return 0;
ok:
    r2 = ScriptGetInt_2490f0(p0++);
    t0 = r0->m18;
    r3 = PartyCountMembers_3c2010(t0, 1, 1);
    if (r2 < r3) {
        t1 = r0->m18;
        r4 = ((short)PartyGetMemberId_3c2490(t1, r2));
        ScriptSetRefInt_249030(p0++, r4);
    } else {
        ScriptSetRefInt_249030(p0++, -1);
    }
    if (p1 >= 3) {
        if (r2 < r3) {
            t2 = r0->m18;
            r7 = ((short)PartyGetMemberId_3c2490(t2, r2));
            t3 = r0->m14;
            r8 = CharaGetDataIdById_3a8a10(t3, r7);
            ScriptSetRefInt_249030(p0, r8);
        } else {
            ScriptSetRefInt_249030(p0, -1);
        }
    }
    return 1;
}
