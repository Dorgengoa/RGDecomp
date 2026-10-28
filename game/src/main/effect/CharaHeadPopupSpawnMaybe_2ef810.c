/* rgp:protos */
#define RGP_SELF_CharaHeadPopupSpawnMaybe_2ef810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Obj {
    u8 pad0[0x4CC];
    f32 m4CC;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s64 D_0047D190;

s32 CharaHeadPopupSpawnMaybe_2ef810(s32 arg0)
{
    Vec a __attribute__((aligned(16)));
    Vec b __attribute__((aligned(16)));
    f32 f;
    s32 h;
    s32 id;
    s32 k;
    Obj *o;

    h = ((s32)GetActionMgr_1fdb50());
    if (h == 0) {
        return 0;
    }
    id = ((s32)ActionMgrFindById_233b50(h, arg0));
    if (id == 0) {
        return 0;
    }
    CharaGetPos_2388a0(id, &a);
    f = 40.0f;
    k = GetCurrentScene_1f5be0();
    o = 0;
    if (k != 0) {
        o = ((Obj *)ObjRecGetLiveObject_1c4a90(k, arg0));
    }
    if (o != 0) {
        f = dptofp(dpmul(__builtin_bit_cast(double, (long long)(D_0047D190)), fptodp(o->m4CC)));
    }
    a.y += f;
    if (CharaGetNthAttachPointPos_238580(id, 0, 0, &b) == 0) {
        VecCopy_1cbe30(&b, &a);
    }
    DamagePopupSpawn_2d2da0(((s32)GetDamagePopupList_2d9020()), 0, &b, 0, 3, 0, 1.0f);
    return 1;
}
