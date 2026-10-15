#include "types.h"
#pragma opt_loop_invariants off

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

typedef struct { s32 w[12]; } W12;
typedef struct { f32 x, y, z, w; } F4;
typedef struct { s16 h[10]; } H10;

typedef struct {
    W12 a;
    F4 p;
    H10 s;
    s32 e;
    s32 pad[2];
} Ent;

extern s32 ObjMgrCountFiltered_3baf10(s32, s32, s32, s32, s32);
extern u32 AlignUp16_1cacd0(s32);
extern s32 MemStackHeapAllocFront_14dd10(s32, u32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern void VecCopy_1cbe30(void *, void *);
extern void VecCopyAsPoint_1cbe10(V4 *, V4 *);
extern s32 MapEvCollectCollPolysMaybe_1ff270(s32, s32, V4 *, s32);
extern void VecNormalize_1cbb80(void *, void *);
extern void VecAdd3_1cbd60(V4 *, void *, void *, void *);
extern void VecDivScalarPoint_1cbbc0(V4 *, V4 *, f32);
extern void VecSub_1cbd00(V4 *, void *, void *);
extern s32 ActionMgrFindById_233b50(void *, s32);
extern f32 RandFloat_13c010(void);
extern void CharaSetPosXYZ_2139e0(s32, f32, f32, f32);
extern void CharaSetYaw_2138f0(s32, f32);
extern f32 Atan2f_1291a8(f32, f32);
extern void *GetGameData_1fede0(void);
extern void *GetCurrentScene_1f5be0(void);
extern f32 D_0045B080[];
extern f32 D_0047D288;
extern u8 D_004B8680[];

s32 ScatterCharasOnGroundMaybe_1fbe70(V4 *arg0, V4 *arg1)
{
    s32 pool;
    V4 base;
    V4 box[2];
    V4 c;
    V4 d;
    s32 buf;
    Ent *res;
    s32 n;
    s32 t;
    s32 cnt;
    Ent *dst;
    Ent *src;
    s32 i;
    s32 ok;
    s32 o;
    s32 j;
    s32 e;
    s32 idx;
    Ent *q;
    f32 k;
    f32 b;
    f32 a;
    f32 h;
    f32 v;
    f32 x;
    u8 *tbl;

    if (ObjMgrCountFiltered_3baf10(*(s32 *)((s32)GetGameData_1fede0() + 0x1C), -1, 1, 0, 0) <= 0) {
        return 0;
    }
    pool = *(s32 *)((s32)GetCurrentScene_1f5be0() + 0x180C);
    if (pool == 0) {
        return 0;
    }
    buf = MemStackHeapAllocFront_14dd10(pool, AlignUp16_1cacd0(0x18000) >> 4);
    if (buf == 0) {
        return 0;
    }
    VecCopy_1cbe30(&base, arg0);
    res = 0;
    k = D_0045B080[0];
    b = 7.5f * k;
    a = 5.0f * k;
    n = 0;
    h = 3.0f * k;
    for (t = 0; t < 2; t++) {
        VecCopyAsPoint_1cbe10(&box[0], &base);
        VecCopyAsPoint_1cbe10(&box[1], &base);
        box[0].x += b;
        box[0].y += a;
        box[0].z += b;
        box[1].x -= b;
        box[1].y -= h;
        box[1].z -= b;
        cnt = MapEvCollectCollPolysMaybe_1ff270(buf, 0x400, box, -1);
        n = 0;
        res = (Ent *)buf + cnt;
        if (cnt > 0) {
            dst = res;
            src = (Ent *)buf;
            for (i = 0; i < cnt; i++, src++) {
                if (src->s.h[0] != 1) {
                    continue;
                }
                VecNormalize_1cbb80(&src->p, &src->p);
                if (src->p.y < D_0047D288) {
                    continue;
                }
                VecAdd3_1cbd60(&c, src, (u8 *)src + 0x10, (u8 *)src + 0x20);
                VecDivScalarPoint_1cbbc0(&c, &c, 3.0f);
                v = c.y - base.y;
                v = (v < 0.0f) ? -v : v;
                if (v <= 2.0f * k) {
                    dst->a = src->a;
                    dst->p = src->p;
                    dst->s = src->s;
                    dst->e = src->e;
                    VecCopy_1cbe30(&dst->p, &c);
                    dst++;
                    n++;
                }
            }
        }
        if (n > 0) {
            break;
        }
        VecCopy_1cbe30(&base, arg1);
    }
    ok = 0;
    if (n <= 0) {
        tbl = D_004B8680;
        o = *(s32 *)(*(s32 *)((s32)GetGameData_1fede0() + 0x20) + 0x238);
        for (j = 0; j < *(s16 *)(o + 0x44); j++) {
            e = ActionMgrFindById_233b50(tbl, *(s32 *)(*(s32 *)(o + j * 8 + 0x4C) + 0xC));
            if (e == 0) {
                continue;
            }
            x = 0.0f + arg1->x + 2.0f * (RandFloat_13c010() - 0.5f);
            CharaSetPosXYZ_2139e0(e, x, arg1->y, 0.0f + arg1->z + 2.0f * (RandFloat_13c010() - 0.5f));
            CharaSetYaw_2138f0(e, 0.0f);
        }
    } else {
        tbl = D_004B8680;
        o = *(s32 *)(*(s32 *)((s32)GetGameData_1fede0() + 0x20) + 0x238);
        for (j = 0; j < *(s16 *)(o + 0x44); j++) {
            e = ActionMgrFindById_233b50(tbl, *(s32 *)(*(s32 *)(o + j * 8 + 0x4C) + 0xC));
            if (e == 0) {
                continue;
            }
            idx = (s32)((f32)n * RandFloat_13c010());
            if (idx < 0) {
                idx = 0;
            }
            if (idx >= n) {
                idx = n - 1;
            }
            q = res + idx;
            VecSub_1cbd00(&d, arg1, &q->p);
            x = q->p.x + (RandFloat_13c010() - 0.5f);
            CharaSetPosXYZ_2139e0(e, x, q->p.y, q->p.z + (RandFloat_13c010() - 0.5f));
            CharaSetYaw_2138f0(e, Atan2f_1291a8(d.x, d.z));
        }
        ok = 1;
    }
    if (buf != 0) {
        MemStackHeapFree_14dcb0(pool, buf);
    }
    return ok != 0;
}
