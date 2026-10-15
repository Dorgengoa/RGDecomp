#include "types.h"

struct Node2460e0 { u8 pad0[0x32]; s16 f32; u8 pad34[8]; s32 f3C; };

extern "C" {
extern s32 GetMapMgr_201a90(void);
extern s32 ScriptGetCodeAddr_249050(void *p);
extern s32 ScriptGetInt_2490f0(void *p);
extern Node2460e0 *MapFindObjInAreaByName_1e4470(s32 ctx, s32 u, s32 v);
extern Node2460e0 *MapFindObjInAreaById_1e44b0(s32 ctx, s32 u, s32 v);
}

extern "C" s32 EvCmdMapAreaNodeEnableMaybe_2460e0(u8 *p, s32 kind)
{
    s32 ctx;
    Node2460e0 *obj;
    s32 u;
    bool ok;

    if (kind != 3) {
        return 0;
    }
    ctx = GetMapMgr_201a90();
    if (*(s32 *)p == 2) {
        u = ScriptGetCodeAddr_249050(p);
        obj = MapFindObjInAreaByName_1e4470(ctx, u, ScriptGetCodeAddr_249050(p + 8));
    } else {
        u = ScriptGetInt_2490f0(p);
        obj = MapFindObjInAreaById_1e44b0(ctx, u, ScriptGetCodeAddr_249050(p + 8));
    }
    if (obj == 0) {
        return 0;
    }
    ok = ScriptGetInt_2490f0(p + 0x10) != 0;
    if (ok) {
        obj->f32 = 1;
        obj->f3C &= ~1;
    } else {
        obj->f32 = 0;
        obj->f3C |= 1;
    }
    return 1;
}
