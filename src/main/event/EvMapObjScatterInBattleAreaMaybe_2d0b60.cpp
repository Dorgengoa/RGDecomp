#include "types.h"
#pragma optimization_level 3
#pragma divbyzerocheck on

struct Vec4 {
    f32 x, y, z, w;
};

struct Elem {
    s32 a[12];
    Vec4 v;
    s16 h[10];
    s32 i54;
} __attribute__((aligned(16)));

struct Slot {
    s16 id;
    s16 n;
};

extern "C" {
void Sprintf_1343b8(char *, u8 *, s32, s32);
f32 RandFloat_13c010();
f32 fabsf(f32);
void MemStackHeapFree_14dcb0(s32, Elem *);
Elem *MemStackHeapAllocFront_14dd10(s32, u32);
u32 AlignUp16_1cacd0(s32);
f32 VecDistSqXZ_1cb390(Vec4 *, Vec4 *);
void VecNormalize_1cbb80(Vec4 *, Vec4 *);
void VecDivScalarPoint_1cbbc0(Vec4 *, Vec4 *, f32);
void VecAdd3_1cbd60(Vec4 *, s32 *, s32 *, s32 *);
void VecCopyAsPoint_1cbe10(Vec4 *, Vec4 *);
s32 VecCopy_1cbe30(Vec4 *, Vec4 *);
f32 AngleWrap_1cbf30(f32);
s32 MapSlotsFindById_1e4b90(s32, s32, s32);
u8 *MapDataFindObjByName_1e71d0(s32, char *);
u8 *GetCurrentScene_1f5be0();
u8 *GetGameData_1fede0();
s32 MapEvCollectCollPolysMaybe_1ff270(Elem *, s32, Vec4 *, s32);
s32 GetMapMgr_201a90();
s32 ReturnZero_207f00();
f32 GameFlowGetBattleRadius_283380();
s32 GetEventObjMgr_2d1960();
s32 TargetRefGetId_2e7120(s32);
void EvMapObjResetAreaObjsAllMaybe_2e9440(s32);
u8 *EvMapObjFindById_2e9810(s32, s32);
s32 EvObjGetTargetRef_2f9ca0(u8 *);
void EvMapObjPlaceAtMaybe_366840(u8 *, u8 *, Vec4 *, f32);
s32 EvMapObjGetName_366b90(u8 *);
extern f32 D_0045B080[];
extern u8 D_00461570[];
extern f32 D_0047D1FC;
extern f32 D_0047D288;
extern f32 D_0047DCD8;
void EvMapObjScatterInBattleAreaMaybe_2d0b60(Vec4 *pos);
}

#define CNT(o) (*(s16 *)((o) + 0x154))
#define SLOTS(o) ((Slot *)((o) + 0x156))

void EvMapObjScatterInBattleAreaMaybe_2d0b60(Vec4 *pos) {
    Vec4 hi; Vec4 lo; Vec4 c; char name[32]; s32 mgr; s32 spawn; s32 tbl; s32 heap; u8 *slp; Elem *buf; f32 h5; u8 *o; f32 tol; f32 d; f32 far; Slot *sl; s32 m; f32 dd; Elem *base; u8 *g; s32 i; s32 j; Elem *dst; s32 cnt; Elem *src; u8 *u; u8 *p; s32 i2; f32 near2; f32 far2; f32 sc; s32 n; s32 k;

    g = GetGameData_1fede0();
    mgr = GetEventObjMgr_2d1960();
    EvMapObjResetAreaObjsAllMaybe_2e9440(mgr);
    o = *(u8 **)(*(u8 **)(g + 0x20) + 0x238);
    if (o == 0) return;
    if (ReturnZero_207f00() != 0) {
        CNT(o) = 0;
        for (i = 0; i < 11; i++) {
            u = EvMapObjFindById_2e9810(mgr, i);
            if (u == 0) continue;
            if (!(*(u32 *)(u + 0xD0) & 0x2000000)) continue;
            *(s16 *)(o + CNT(o) * 4 + 0x156) = i;
            *(s16 *)(o + CNT(o) * 4 + 0x158) = 5;
            CNT(o)++;
            if (CNT(o) >= 3) break;
        }
    }
    if (CNT(o) <= 0) return;
    heap = *(s32 *)(GetCurrentScene_1f5be0() + 0x180C);
    if (heap == 0) return;
    buf = MemStackHeapAllocFront_14dd10(heap, AlignUp16_1cacd0(0x18000) >> 4);
    if (buf == 0) return;
    sc = D_0045B080[0];
    far = 20.0f * sc;
    near2 = (5.0f * sc) * (5.0f * sc);
    d = GameFlowGetBattleRadius_283380() - sc;
    if (d < 0.0f) {
        d = 1000.0f * sc;
    }
    far2 = d * d;
    VecCopyAsPoint_1cbe10(&lo, pos);
    VecCopyAsPoint_1cbe10(&hi, pos);
    lo.x += far;
    lo.y += 5.0f * D_0045B080[0];
    lo.z += far;
    hi.x -= far;
    hi.y -= 5.0f * D_0045B080[0];
    hi.z -= far;
    n = MapEvCollectCollPolysMaybe_1ff270(buf, 0x400, &lo, -1);
    base = buf + n;
    cnt = 0;
    if (n > 0) {
        dst = base;
        src = buf;
        tol = 2.0f * sc;
        for (j = 0; j < n; j++, src++) {
            if (src->h[0] != 1) continue;
            VecNormalize_1cbb80(&src->v, &src->v);
            if (src->v.y < D_0047D288) continue;
            VecAdd3_1cbd60(&c, &src->a[0], &src->a[4], &src->a[8]);
            VecDivScalarPoint_1cbbc0(&c, &c, 3.0f);
            if (!(fabsf(c.y - pos->y) <= tol)) continue;
            dd = VecDistSqXZ_1cb390(&c, pos);
            if (dd < near2) continue;
            if (!(dd <= far2)) continue;
            *dst = *src;
            VecCopy_1cbe30(&dst->v, &c);
            dst++;
        }
        cnt = dst - base;
    }
    if (cnt > 0) {
        spawn = GetMapMgr_201a90();
        for (i2 = 0; i2 < CNT(o); i2++) {
            slp = o + i2 * 4;
            u = EvMapObjFindById_2e9810(mgr, *(s16 *)(slp + 0x156));
            if (u == 0) continue;
            tbl = MapSlotsFindById_1e4b90(spawn, TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(u)), 0);
            if (tbl == 0) continue;
            for (j = 0; j < *(s16 *)(o + i2 * 4 + 0x158); j++) {
                Sprintf_1343b8(name, D_00461570, EvMapObjGetName_366b90(u), j + 1);
                p = MapDataFindObjByName_1e71d0(tbl, name);
                if (p == 0) continue;
                k = (s32)(RandFloat_13c010() * (f32)cnt);
                if (k < 0) k = 0;
                if (!(k < cnt)) k = cnt - 1;
                *(s32 *)(p + 0x64) = 0;
                EvMapObjPlaceAtMaybe_366840(u, p, &base[k].v, AngleWrap_1cbf30(D_0047DCD8 * RandFloat_13c010() - D_0047D1FC));
                for (m = k + 1; m < cnt; m++) {
                    base[m - 1] = base[m];
                }
                cnt--;
                if (cnt <= 0) break;
            }
            if (cnt <= 0) break;
        }
    }
    if (buf != 0) {
        MemStackHeapFree_14dcb0(heap, buf);
    }
}
