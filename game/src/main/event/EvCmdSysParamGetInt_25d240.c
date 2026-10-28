/* rgp:protos */
#define RGP_SELF_EvCmdSysParamGetInt_25d240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S8 { s32 a; s32 b; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSysParamGetInt_25d240(struct S8 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;

    if (p1 != 2) {
        return 0;
    }
    r0 = ((s32)GetSysParamTable_1c6be0());
    r1 = ScriptGetInt_26a2a0(p0++);
    r2 = SysParamTableGetInt_15fe80(r0, r1);
    ScriptSetRefInt_26a1e0(p0, r2);
    return 1;
}
