/* rgp:protos */
#define RGP_SELF_CharaCloneObjSpawn_2ccf00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct H2ccf00 {
    u8 pad00[4];
    s16 m04;
} H2ccf00;

extern f32 D_004825D8;
extern s32 D_0047EDD0;
extern s32 D_0047EDD4;
extern u8 D_00461548[];

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
/*rgp*/

void CharaCloneObjSpawn_2ccf00(void *p, s32 q, s32 k, f32 t, f32 u)
{
    u128 va;
    u128 vb;
    void *a;
    void *n;
    H2ccf00 *h;
    void *e;
    u8 *r;

    a = GetCharaResMgr_1fdb60();
    n = GetCharaDataMgr_1fdb70();
    h = ((H2ccf00 *)CharaResFindById_1f0530(a, q));
    if (h == 0) {
        return;
    }
    e = CharaDataFindNode_1ed6d0(n, h->m04, 0, 0);
    if (e == 0) {
        return;
    }
    if (((short)CharaDataNodeGetSubObjCount_1eeb80(e)) <= 0) {
        return;
    }
    e = CharaDataNodeGetSubObj_1eeb30(e, 0);
    if (e == 0) {
        return;
    }
    r = (u8 *)ObjRecGetLiveObject_1c4a90(p, q);
    if (r == 0) {
        return;
    }
    va = *(u128 *)(r + 0x180);
    vb = *(u128 *)(r + 0x190);
    ModelSetPos_151110(e, &va);
    ModelSetRot_151080(e, &vb);
    GameSceneObjBindMaybe_1cfcd0(p, 0x9C, e, 0);
    ObjRecSetFlag2_1c3e80(p, 1, 0x9C);
    ParamTableSetAlpha_1cfb10(p, 0x9C, t);
    ModelObjPlayMotionByName_1867a0(e, D_00461548, 4);
    D_004825D8 = u;
    D_0047EDD0 = k;
    D_0047EDD4 = q;
}
