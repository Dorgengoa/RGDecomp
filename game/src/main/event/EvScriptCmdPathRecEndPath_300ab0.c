/* rgp:protos */
#define RGP_SELF_EvScriptCmdPathRecEndPath_300ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

extern s32 D_00482840;
extern s32 D_00482844;
extern s32 D_00482848;
extern s32 D_0048284C;

s32 EvScriptCmdPathRecEndPath_300ab0(s32 p0, s32 p1)
{
    s32 t0;
    s32 t1;
    s32 e;
    s32 r0;
    s32 diff;

    if (p1 != 0) {
        return 0;
    }
    t0 = D_00482840;
    if (t0 != 0) {
        t1 = D_00482844;
        if (t1 < 0x40) goto ok;
    }
    return 1;
ok:
    e = t0 + (t1 << 4);
    r0 = EventPathGetSegs_2e4540(e);
    diff = (D_00482848 + (D_0048284C << 3)) - r0;
    EventPathSetSegCount_2e4530(e, diff / 8);
    D_00482844 = D_00482844 + 1;
    return 1;
}
