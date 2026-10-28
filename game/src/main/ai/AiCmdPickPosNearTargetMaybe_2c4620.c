/* rgp:protos */
#define RGP_SELF_AiCmdPickPosNearTargetMaybe_2c4620 1
#include "port/game_protos.h"
#line 1
/* MATCH s88m (lane 2c46): file-default O4 (no opt pragmas), arg0++ stream reads, native soft-double ops,
   f21 statement before f20, decl order o1 before o2. */
#include "types.h"
#pragma divbyzerocheck on
#pragma opt_arithtransformation off

typedef rg_u128 u128;
typedef struct { f32 x, y, z, w; } Vec4;
#define VCOPY(d, s) (*(u128 *)&(d) = *(u128 *)&(s))

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
/*rgp*/
/*rgp*/
extern f32 D_0047D240;
extern f32 D_0047D278;
extern f32 D_0047D354;
extern f32 D_0047EE00;
extern f32 D_0047EE04;
extern f32 D_0047EE08;
extern f32 D_0047EE0C;
extern s32 D_004DB920[];

s32 AiCmdPickPosNearTargetMaybe_2c4620(s64 *arg0)
{
    Vec4 m100 __attribute__((aligned(16)));
    Vec4 mF0 __attribute__((aligned(16)));
    Vec4 vE0 __attribute__((aligned(16)));
    Vec4 vD0 __attribute__((aligned(16)));
    Vec4 v[4] __attribute__((aligned(16)));
    s32 flags[4] __attribute__((aligned(16)));
    Vec4 out __attribute__((aligned(16)));
    s32 a;
    s32 b;
    s32 tbl;
    u8 *o1;
    u8 *o2;
    void *m1;
    void *m2;
    f32 f21;
    f32 f20;
    f32 f22;
    f32 mx;
    f64 d;
    s32 n;
    f32 c;
    s32 i;
    void *w;
    s32 found;
    s32 bi;
    f32 best;
    f32 thr;
    f32 da;
    f32 db;

    a = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    b = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    tbl = D_004DB920[0];
    o1 = ((u8 *)ObjRecGetLiveObject_1c4a90(tbl, a));
    o2 = ((u8 *)ObjRecGetLiveObject_1c4a90(tbl, b));
    if (o1 == 0) return 0;
    if (o2 == 0) {
        VCOPY(m100, *(Vec4 *)(o1 + 0x180));
        ScriptSlotStoreIntRef_2cc900((s32)arg0++, 0);
        ScriptSlotStoreVec3_2cc8a0((s32)arg0, &m100);
        return 1;
    }
    m1 = ModelGetRootFrame_1511a0(o1);
    m2 = ModelGetRootFrame_1511a0(o2);
    if (m1 == 0 || m2 == 0) return 0;
    FrameGetWorldPos_148f30(m1, &m100);
    FrameGetWorldPos_148f30(m2, &mF0);
    { f32 kk, x1, x2; x2 = *(f32 *)(o2 + 0x4C8); kk = D_0047D240; x1 = *(f32 *)(o1 + 0x4C8); f21 = kk * x1; f20 = kk * x2; }
    { f32 lim = 120.0f; mx = f20; if (f20 < lim) mx = lim; }
    d = (f64)mx + 0.5 * f21;
    f22 = 0.5 * f20 + d;
    VecSub_13be40(&vE0, &m100, &mF0);
    { Vec4 *pe = &vE0; VecNormalize_13bd90(pe, pe); }
    vD0.x = D_0047EE00;
    vD0.y = D_0047EE04;
    vD0.z = D_0047EE08;
    vD0.w = D_0047EE0C;
    { Vec4 *pd = &vD0; FrameTransformDir_148ed0(m2, pd, pd); }
    c = VecDistance_13d3d0(&m100, &mF0);
    if (D_0047D278 * f22 < c && c < D_0047D354 * f22) {
        ScriptSlotStoreIntRef_2cc900((s32)arg0++, 0);
        ScriptSlotStoreVec3_2cc8a0((s32)arg0, &m100);
        return 1;
    }
    n = f22;
    d = 0.5 * f22;
    v[0].x = litodp(Rand_133710() % n) - d;
    *(s32 *)&v[0].y = 0;
    v[0].z = f22;
    *(s32 *)&v[0].w = 0;
    v[1].x = f22;
    *(s32 *)&v[1].y = 0;
    v[1].z = litodp(Rand_133710() % n) - d;
    f22 = -f22;
    *(s32 *)&v[1].w = 0;
    v[2].x = f22;
    *(s32 *)&v[2].y = 0;
    v[2].z = litodp(Rand_133710() % n) - d;
    *(s32 *)&v[2].w = 0;
    v[3].x = litodp(Rand_133710() % n) - d;
    *(s32 *)&v[3].y = 0;
    v[3].z = f22;
    *(s32 *)&v[3].w = 0;
    i = 0;
    do {
        { Vec4 *pv = &v[i]; FrameTransformPoint_148f60(m2, pv, pv); pv->y = m100.y; }
        i++;
    } while (i < 4);
    w = GetNavMgr_2d1950();
    i = 1;
    do {
        { Vec4 *pv = &v[i]; flags[i] = NavSnapPosInAreaGraph_30ab90(w, pv, pv); }
        i++;
    } while (i < 4);
    found = 0;
    best = 0xFFFF;
    bi = -1;
    VCOPY(out, m100);
    thr = f21 + 1.5f * f20;
    i = 0;
    do {
        if (flags[i] != 0) {
            Vec4 *pv = &v[i];
            da = VecDistance_13d3d0(&m100, pv);
            db = VecDistance_13d3d0(&mF0, pv);
            if (da <= db && !(db - thr < 0.0f) && da < best) {
                best = da;
                bi = i;
                found = 1;
            }
        }
        i++;
    } while (i < 4);
    if (found) VCOPY(out, v[bi]);
    ScriptSlotStoreIntRef_2cc900((s32)arg0++, found);
    ScriptSlotStoreVec3_2cc8a0((s32)arg0, &out);
    return 1;
}
