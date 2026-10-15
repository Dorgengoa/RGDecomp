#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Obj {
    u8 pad0[0x4CC];
    f32 m4CC;
} Obj;

extern s64 dpmul(s64, s64);
extern Obj *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void VecCopy_1cbe30(Vec *, Vec *);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetNthAttachPointPos_238580(s32, s32, s32, Vec *);
extern void CharaGetPos_2388a0(s32, Vec *);
extern void DamagePopupSpawn_2d2da0(s32, s32, Vec *, s32, s32, s32, f32);
extern s32 GetDamagePopupList_2d9020(void);
extern f32 dptofp(s64);
extern s64 fptodp(f32);
extern s64 D_0047D190;

s32 CharaHeadPopupSpawnMaybe_2ef810(s32 arg0)
{
    Vec a;
    Vec b;
    f32 f;
    s32 h;
    s32 id;
    s32 k;
    Obj *o;

    h = GetActionMgr_1fdb50();
    if (h == 0) {
        return 0;
    }
    id = ActionMgrFindById_233b50(h, arg0);
    if (id == 0) {
        return 0;
    }
    CharaGetPos_2388a0(id, &a);
    f = 40.0f;
    k = GetCurrentScene_1f5be0();
    o = 0;
    if (k != 0) {
        o = ObjRecGetLiveObject_1c4a90(k, arg0);
    }
    if (o != 0) {
        f = dptofp(dpmul(D_0047D190, fptodp(o->m4CC)));
    }
    a.y += f;
    if (CharaGetNthAttachPointPos_238580(id, 0, 0, &b) == 0) {
        VecCopy_1cbe30(&b, &a);
    }
    DamagePopupSpawn_2d2da0(GetDamagePopupList_2d9020(), 0, &b, 0, 3, 0, 1.0f);
    return 1;
}
