#include "types.h"

extern f32 D_0047E440 __attribute__((section(".sdata")));
extern f32 D_0047E444 __attribute__((section(".sdata")));
extern f32 D_0047E448 __attribute__((section(".sdata")));
extern f32 D_0047E44C __attribute__((section(".sdata")));

extern void *GetMapMgr_201a90(u8 *p);
extern void *TaggedGetStr_1e9ff0(u8 *p);
extern void *TaggedGetInt_1ea050(u8 *p);
extern void *MapFindNodeInAreaByName_1e43f0(void *a, void *b, void *c);
extern void *MapFindNodeInAreaById_1e4430(void *a, void *b, void *c);
extern void NodeGetTranslation_186650(void *r, f32 *t);
extern void ScriptSlotStoreFloatRef_1e9fb0(u8 *p, f32 v);

s32 MapScriptCmdGetNodePos_1e9ea0(u8 *p, s32 mode)
{
    f32 t[4];
    void *w;
    void *y;
    void *z;
    void *r;

    if (mode != 5) {
        return 0;
    }
    t[0] = D_0047E440;
    t[1] = D_0047E444;
    t[2] = D_0047E448;
    t[3] = D_0047E44C;
    w = GetMapMgr_201a90(p);
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
        NodeGetTranslation_186650(r, t);
    }
    ScriptSlotStoreFloatRef_1e9fb0(p + 0x10, t[0]);
    ScriptSlotStoreFloatRef_1e9fb0(p + 0x18, t[1]);
    ScriptSlotStoreFloatRef_1e9fb0(p + 0x20, t[2]);
    return 1;
}
