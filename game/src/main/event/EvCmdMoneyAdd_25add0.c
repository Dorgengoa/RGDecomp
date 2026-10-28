/* rgp:protos */
#define RGP_SELF_EvCmdMoneyAdd_25add0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 EvCmdMoneyAdd_25add0(s32 p0)
{
    s32 r0;
    struct Obj0 *r1;
    s32 t0;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = ((struct Obj0 *)GetGameData_1fede0());
    t0 = r1->m18;
    r2 = PartyAddMoney_3c8e90(t0, r0);
    return 1;
}
