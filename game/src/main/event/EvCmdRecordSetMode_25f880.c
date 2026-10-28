/* rgp:protos */
#define RGP_SELF_EvCmdRecordSetMode_25f880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EvCmdRecordSetSubState_25f4c0 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0;

struct Obj0 {
    u8 pad000[0x24];
    s32 m24;
};

s32 EvCmdRecordSetMode_25f880(s32 p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 t0;
    s32 r2;

    r0 = GetGameData_1fede0();
    r1 = ScriptGetInt_26a2a0(p0);
    t0 = r0->m24;
    r2 = RecordSetMode_431310(t0, r1);
    return 1;
}
