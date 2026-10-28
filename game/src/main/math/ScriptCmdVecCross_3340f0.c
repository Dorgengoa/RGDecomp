/* rgp:protos */
#define RGP_SELF_ScriptCmdVecCross_3340f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdVecCross_3340f0(u8 *p0, s32 p1)
{
    u128 v40;
    u128 v30;
    u128 v20;

    if (p1 != 9) {
        return 0;
    }
    ScriptSlotsToVec4_334810(&v30, p0 + 0x18);
    ScriptSlotsToVec4_334810(&v20, p0 + 0x30);
    sceVu0OuterProduct(&v40, &v30, &v20);
    ScriptSlotStoreVec3_334790(p0, &v40);
    return 1;
}
