/* rgp:protos */
#define RGP_SELF_ScriptCmdAttackObjDestroy_32f950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 { u8 pad000[0xB6]; s16 mB6; };
struct Obj1 { u8 pad000[0x18]; s32 m18; };

/*rgp*/
/*rgp*/
/*rgp*/

extern struct Obj1 * D_004826E0;

s32 ScriptCmdAttackObjDestroy_32f950(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    struct Obj0 *r2;
    struct Obj1 *g;
    s32 *pm;

    if (p1 != 1) {
        return 0;
    }
    r0 = ScriptSlotGetInt_3348b0(p0);
    r1 = ((s32)GetObjRefTable_313de0());
    r2 = ((struct Obj0 *)HandleRegistryLookup_314aa0(r1, r0));
    if (r2 == 0) {
        return 1;
    }
    r2->mB6 = 1;
    g = D_004826E0;
    if (g != 0) {
        pm = &g->m18;
        if (r0 == g->m18) {
            *pm = -1;
        }
    }
    return 1;
}
