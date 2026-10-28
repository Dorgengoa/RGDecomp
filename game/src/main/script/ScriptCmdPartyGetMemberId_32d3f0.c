/* rgp:protos */
#define RGP_SELF_ScriptCmdPartyGetMemberId_32d3f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct Obj0032d3f0 {
    u8 pad000[0x18];
    s32 unk18;
} Obj0032d3f0;

s32 ScriptCmdPartyGetMemberId_32d3f0(s64 *p0)
{
    Obj0032d3f0 *r0;
    s32 t1;

    r0 = GetGameData_1fede0();
    t1 = ScriptSlotGetInt_3348b0((s32)p0++);
    ScriptSlotStoreIntRef_3347f0((s32)p0, ((short)PartyGetMemberId_3c2490(r0->unk18, t1)));
    return 1;
}
