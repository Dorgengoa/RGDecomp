#include "types.h"
#pragma opt_propagation off
#pragma opt_repositioncode off

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct {
    Vec r[4];
} Mtx;

typedef struct {
    s32 x;
    f32 y;
    s32 z;
    s32 w;
} Rot;

typedef struct {
    u8 pad0[8];
    s32 x8;
} Self;

extern void NodeSetRotation_186620(s32, Rot *);
extern void NodeSetTranslation_1866b0(s32, Vec *);
extern void MapAreaModelObjsClearOwner_188f60(s32);
extern void MapAreaModelObjsSetOwner_188fa0(s32);
extern s32 FuncDataTableIterNext_1908b0(s32);
extern void FuncDataTableIterBegin_1908e0(s32, s32);
extern s32 ArrayGetChecked_1936d0(s32, s32);
extern void MatToRotPos_1cade0(Vec *, Vec *, Mtx *);
extern void MatFromRotPos_1caf90(Mtx *, u8 *, u8 *);
extern void MatRotY_1cb200(Mtx *, f32);
extern void MatMul_1cb700(void *, Mtx *, void *);
extern void MatMulPoint_1cb8e0(void *, Mtx *, void *);
extern void VecCopyAsPoint_1cbe10(Vec *, Vec *);
extern void VecCopy_1cbe30(Vec *, Vec *);
extern void MatIdentity_1cbe40(Mtx *);
extern f32 AngleWrap_1cbf30(f32);
extern void GameSceneDoorGlareClear_1cf790(s32, s32);
extern f32 MapDataGetRotY_1e7710(Self *);
extern void MapDataGetPosVec4_1e7740(Self *, Vec *);
extern s32 MapDataIsFncLocal_1e7b80(Self *);
extern s32 MapAreaDataGetModel_1e8c00(s32);
extern s32 MapAreaDataGetLinks_1e8c10(s32);
extern s32 MapAreaDataGetNodeXform_1e8e40(s32, s32);
extern s32 MapAreaDataGetLightSetCount_1e8e80(s32);
extern s32 MapAreaDataGetLightSets_1e8e90(s32);
extern void MapLinkSetAngle_1e91f0(s32, f32);
extern void MapLinkSetTopY_1e9200(s32, f32);
extern void MapLinkSetPos_1e9220(s32, Vec *);
extern s32 MapLinkGetHeight_1e9240(s32);
extern s32 MapLinkGetEntIndex_1e9300(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void memcpy(s32, s32, s32);
extern f32 D_0045B080[];
extern f32 D_0047D1FC;
extern f32 D_0047DB50;

void MapDataPlaceModel_1e6dd0(Self *arg0, Vec *arg1, f32 arg2) {
    Vec pos;
    Mtx m1;
    Mtx m2;
    Vec e;
    Vec d;
    Mtx m3;
    Rot rot;
    s32 obj;
    f32 ang;
    u8 *p;
    u32 n;
    s32 list;
    s32 i;
    s32 k;
    s32 node;
    f32 scale;
    f32 t1;
    f32 t2;
    u8 *dst;
    u8 *src;
    s32 i2;
    s32 cnt;
    s32 j;


    if (arg0->x8 == 0) {
        return;
    }
    obj = MapAreaDataGetModel_1e8c00(arg0->x8);
    if (obj == 0) {
        return;
    }
    GameSceneDoorGlareClear_1cf790(GetCurrentScene_1f5be0(), obj);
    MapDataGetPosVec4_1e7740(arg0, &pos);
    ang = MapDataGetRotY_1e7710(arg0);
    MapAreaModelObjsClearOwner_188f60(obj);
    NodeSetTranslation_1866b0(obj, &pos);
    p = (u8 *)&rot;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    rot.x = 0;
    rot.y = ang;
    rot.z = 0;
    NodeSetRotation_186620(obj, &rot);
    MapAreaModelObjsSetOwner_188fa0(obj);
    switch (MapDataIsFncLocal_1e7b80(arg0)) {
    case 0:
        MatRotY_1cb200(&m1, arg2);
        VecCopyAsPoint_1cbe10(&m1.r[3], arg1);
        break;
    case 2:
        MatRotY_1cb200(&m1, ang);
        VecCopyAsPoint_1cbe10(&m1.r[3], &pos);
        break;
    default:
        MatIdentity_1cbe40(&m1);
        break;
    }
    list = obj + 0x1664;
    FuncDataTableIterBegin_1908e0(list, 6);
    i = 0;
    k = MapAreaDataGetLinks_1e8c10(arg0->x8);
    t1 = D_0045B080[0];
    scale = D_0047DB50 * t1;
    while ((node = FuncDataTableIterNext_1908b0(list)) != 0) {
        u8 *b = (u8 *)MapAreaDataGetNodeXform_1e8e40(arg0->x8, i);
        if (b == 0) {
            break;
        }
        MatFromRotPos_1caf90(&m2, b, b + 0x10);
        MatMul_1cb700(&m2, &m1, &m2);
        MatToRotPos_1cade0(&e, &d, &m2);
        NodeSetTranslation_1866b0(node, &d);
        NodeSetRotation_186620(node, (Rot *)&e);
        if (k != 0 && i == MapLinkGetEntIndex_1e9300(k)) {
            MapLinkSetPos_1e9220(k, &d);
            MapLinkSetTopY_1e9200(k, d.y + scale * (f32)MapLinkGetHeight_1e9240(k));
            MapLinkSetAngle_1e91f0(k, AngleWrap_1cbf30(D_0047D1FC + e.y));
            k += 0x20;
        }
        i++;
    }
    dst = (u8 *)MapAreaDataGetLightSets_1e8e90(arg0->x8);
    src = (u8 *)ArrayGetChecked_1936d0(obj + 0x70, 0);
    if (dst == 0) {
        return;
    }
    if (src == 0) {
        return;
    }
    MatRotY_1cb200(&m3, ang);
    VecCopy_1cbe30(&m3.r[3], &pos);
    cnt = MapAreaDataGetLightSetCount_1e8e80(arg0->x8);
    for (i2 = 0; i2 < cnt; i2++, dst += 0x1D0, src += 0x1D0) {
        memcpy((s32)dst, (s32)src, 0x1D0);
        MatMul_1cb700(dst + 0x30, &m3, src + 0x30);
        j = 0;
        do {
            MatMulPoint_1cb8e0(dst + j * 0x30 + 0xC0, &m3, src + j * 0x30 + 0xC0);
            j++;
        } while (j < 4);
    }
}
