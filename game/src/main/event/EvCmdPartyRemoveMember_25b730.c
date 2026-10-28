/* rgp:protos */
#define RGP_SELF_EvCmdPartyRemoveMember_25b730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdPartyRemoveMember_25b730(E8 *p0, s32 p1)
{
    struct Obj0 *r0;
    s32 r1;
    s32 rv3;
    s32 t0;
    s32 r4;

    if (p1 != 1 && p1 != 2) {
        return 0;
    }
    r0 = ((struct Obj0 *)GetGameData_1fede0());
    r1 = ScriptGetInt_26a2a0(p0++);
    rv3 = 0;
    if (p1 == 2) {
        rv3 = ScriptGetInt_26a2a0(p0);
    }
    t0 = r0->m18;
    r4 = PartyRemoveMember_3c0fa0(t0, r1, (rv3 != 0), 0);
    if (r4 == 0) {
        return 0;
    }
    return 1;
}
