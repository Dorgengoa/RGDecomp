/* rgp:protos */
#define RGP_SELF_ScriptCmdPartyCountTotal_32d380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
    u8 pad000[0x18];
    s32 m18;
};

s32 ScriptCmdPartyCountTotal_32d380(s32 p0)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = GetGameData_1fede0();
    t0 = r0->m18;
    r1 = PartyCountMembers_3c2010(t0, 1, 1);
    r2 = PartyCountReserve_3c1c20(t0, 1, 1);
    r3 = (ScriptSlotStoreIntRef_3347f0(p0, (r1 + r2)), (s32)0);
    return 1;
}
