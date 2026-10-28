#pragma optimization_level 3
#pragma opt_propagation off
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct Mtx { f32 m[4][4]; } Mtx;
typedef struct Res {
    s32 w0;     /* 0x00 */
    s32 w4;     /* 0x04 */
    s32 pad8[2];
    Mtx m;      /* 0x10 */
    s32 w50;    /* 0x50 */
    s32 w54;    /* 0x54 */
} Res;
typedef struct MtxP { volatile s32 a; s32 pad[3]; Mtx m; } MtxP;

void MtxIdentity_13d2e0(Mtx *);
s32 FuncDataRecVolumeContainsPointMaybe_187080(u8 *, s32, s32, Res *, f32 *);
void FuncDataTableIterBegin_1908e0(u8 *, s32);
u8 *FuncDataTableIterNext_1908b0(u8 *);
void NodeCalcWorldMatrixThunk_186130(u8 *, Mtx *);

u8 *MapAreaModelFindVolumeAtPointMaybe_187a00(u8 *arg0, s32 arg1, s32 arg2, Res *out) {
    f32 dist[4] __attribute__((aligned(16)));
    Res r __attribute__((aligned(16)));
    Res best __attribute__((aligned(16)));
    Mtx m1 __attribute__((aligned(16)));
    Mtx m2 __attribute__((aligned(16)));
    struct { volatile s32 a; s32 pad[3]; } aa;
    struct { s32 pad[3]; volatile s32 b; } ab;
    u8 *bestObj;
    Res *res;
    u8 *obj;
    u8 *chr;
    u8 *list;
    u8 **arr;
    s32 n;
    s32 err;
    s32 i;
    s32 v;
    f32 bestDist;
    bool flag;

    aa.a = arg1;
    ab.b = arg2;
    bestObj = NULL;
    res = &r;
    res->w4 = 0;
    MtxIdentity_13d2e0(&res->m);
    res->w54 = -1;
    res->w50 = -1;
    FuncDataTableIterBegin_1908e0(arg0 + 0x1664, 6);
    bestDist = 0.0f;
    err = 0;
    while ((obj = FuncDataTableIterNext_1908b0(arg0 + 0x1664)) != NULL) {
        if (FuncDataRecVolumeContainsPointMaybe_187080(obj, aa.a, ab.b, res, &dist[3]) == 0) {
            if (res != NULL && res->w4 != 0) {
                err = res->w4;
            }
            continue;
        }
        res->w54 = *(s32 *)(obj + 0x68);
        if (bestObj == NULL || dist[3] < bestDist) {
            bestDist = dist[3];
            bestObj = obj;
            best.w0 = res->w0;
            best.w4 = res->w4;
            best.m = res->m;
            best.w50 = res->w50;
            best.w54 = res->w54;
        }
    }
    n = *(s32 *)(arg0 + 0x51C);
    arr = *(u8 ***)(arg0 + 0x520);
    if (*(s32 *)(arg0 + 0x1660) != 0) {
        for (i = 0; i < n; i++) {
            chr = arr[i];
            if (chr == NULL) continue;
            list = chr + 0x114;
            if (!(*(s32 *)(chr + 0x114) & 0x100)) continue;
            flag = *(s8 *)(chr + 0x6C) == 0;
            if (flag) continue;
            if (*(s16 *)(chr + 0x32) == 0) continue;
            NodeCalcWorldMatrixThunk_186130(chr, &m1);
            MtxIdentity_13d2e0(&m2);
            FuncDataTableIterBegin_1908e0(list, 6);
            while ((obj = FuncDataTableIterNext_1908b0(list)) != NULL) {
                { s32 a_ = aa.a;
                *(u8 **)(obj + 0x34) = chr;
                *(s32 *)(obj + 0x38) = 0;
                v = FuncDataRecVolumeContainsPointMaybe_187080(obj, a_, ab.b, res, &dist[3]); }
                *(u8 **)(obj + 0x34) = NULL;
                *(s32 *)(obj + 0x38) = 0;
                if (res != NULL) {
                    res->w50 = i;
                    if (res->w4 != 0) {
                        err = res->w4;
                    }
                }
                if (v == 0) continue;
                res->w54 = *(s32 *)(obj + 0x68);
                if (bestObj == NULL || dist[3] < bestDist) {
                    bestDist = dist[3];
                    bestObj = obj;
            best.w0 = res->w0;
            best.w4 = res->w4;
            best.m = res->m;
            best.w50 = res->w50;
            best.w54 = res->w54;
                }
            }
        }
    }
    if (out != NULL) {
        out->w0 = best.w0;
        out->w4 = best.w4;
        out->m = best.m;
        out->w50 = best.w50;
        out->w54 = best.w54;
        out->w4 = err;
    }
    return bestObj;
}
}
