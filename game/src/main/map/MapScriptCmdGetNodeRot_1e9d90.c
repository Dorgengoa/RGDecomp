/* rgp:protos */
#define RGP_SELF_MapScriptCmdGetNodeRot_1e9d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047E450 __attribute__((section(".sdata")));
extern f32 D_0047E454 __attribute__((section(".sdata")));
extern f32 D_0047E458 __attribute__((section(".sdata")));
extern f32 D_0047E45C __attribute__((section(".sdata")));

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapScriptCmdGetNodeRot_1e9d90(u8 *p, s32 mode)
{
    f32 t[4] __attribute__((aligned(16)));
    void *w;
    void *y;
    void *z;
    void *r;

    if (mode != 5) {
        return 0;
    }
    t[0] = D_0047E450;
    t[1] = D_0047E454;
    t[2] = D_0047E458;
    t[3] = D_0047E45C;
    w = GetMapMgr_201a90();
    if (*(s32 *)p == 2) {
        y = TaggedGetStr_1e9ff0(p);
        z = TaggedGetStr_1e9ff0(p + 8);
        r = MapFindNodeInAreaByName_1e43f0(w, y, z);
    } else {
        y = TaggedGetInt_1ea050(p);
        z = TaggedGetStr_1e9ff0(p + 8);
        r = MapFindNodeInAreaById_1e4430(w, y, z);
    }
    if (r != 0) {
        NodeGetRotation_1865e0(r, t);
    }
    ScriptSlotStoreFloatRef_1e9fb0(p + 0x10, t[0]);
    ScriptSlotStoreFloatRef_1e9fb0(p + 0x18, t[1]);
    ScriptSlotStoreFloatRef_1e9fb0(p + 0x20, t[2]);
    return 1;
}
