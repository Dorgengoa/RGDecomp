#include "types.h"
extern "C" {



typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct P2 { s32 a, b; } P2;
typedef struct H2 { s16 a, b; } H2;
typedef struct Tri {
    s32 p[12];
    f32 n[4];
    s16 q[10];
    s32 z;
} Tri;
typedef struct Ent { Tri t; u8 pad58[0x60 - 0x58]; } Ent;
typedef struct Ctl {
    u8 pad0[0x50];
    u8 f50[0x24];
    f32 f74;
    u8 pad78[0x100 - 0x78];
    V4 v100;
    V4 tv[3];
    f32 f140[4];
    s16 h150[10];
    s32 f164;
    u8 pad168[0x3D0 - 0x168];
    s64 f3D0;
    s32 f3D8;
    u8 pad3DC[4];
    f32 f3E0;
    u8 pad3E4[8];
    f32 f3EC;
    u8 pad3F0[4];
    s32 f3F4;
    u8 pad3F8[0x40E - 0x3F8];
    s16 h40E;
    s16 h410;
} Ctl;

extern void SrtGetPos_1c7430(void *, V4 *);
extern void VecSub_1cbd00(V4 *, V4 *, V4 *);
extern s32 CollFindGroundTriMaybe_23af50(Ent *, s32, s32, V4 *, V4 *, f32 *);
extern s32 CollRaycastNearest_1c86e0(Ent *, s32, s32, V4 *, V4 *, f32 *);
extern s32 CollTriIsWaterMaybe_1ce5c0(Ent *);
extern f32 PointSegmentDistSq_1c92e0(V4 *, V4 *, V4 *);
extern void VecCopy_1cbe30(V4 *, V4 *);
extern void ClosestPointOnSegment_1c9f60(V4 *, V4 *, V4 *, V4 *);
extern void VecAdd3_1cbd60(V4 *, V4 *, V4 *, V4 *);
extern void VecDivScalarPoint_1cbbc0(V4 *, V4 *, f32);
extern f32 VecDist_1cb420(V4 *, V4 *);
extern void VecLerpPoint_1cbac0(V4 *, V4 *, V4 *, f32);
extern f32 D_0045B080[];
extern f32 D_0047DADC;
extern f32 D_0047DB14;
extern f32 D_0047DB20;

static inline s32 argmin3(f32 a, f32 b, f32 c) {
    if (a < b && a < c) return 0;
    if (b < c) return 1;
    return 2;
}
static inline s32 argmin3b(f32 a, f32 b, f32 c) {
    s32 r;
    if (a < b && a < c) r = 0;
    else if (b < c) r = 1;
    else r = 2;
    return r;
}

void CharaGroundSnapMaybe_237990(Ctl *o, Ent *ents, s32 cnt, f32 lim) {
    f32 dc;
    f32 d8;
    f32 d4;
    V4 c0 __attribute__((aligned(16)));
    V4 b0 __attribute__((aligned(16)));
    V4 a0 __attribute__((aligned(16)));
    V4 p __attribute__((aligned(16)));
    V4 v80 __attribute__((aligned(16)));
    V4 v70 __attribute__((aligned(16)));
    f32 u;
    s32 idx;
    Ent *e;
    u8 ok;
    s32 i;
    s32 *dp;
    s32 *sp_;
    s16 *dq;
    s16 *sq;
    f32 k3;
    f32 t;
    f32 f3;
    f32 f4;
    V4 *tv;
    f32 r;
    f32 rr;
    f32 m0;
    f32 m1;
    f32 m2;
    s32 k;
    s32 j;

    o->f3D8 &= ~1;
    o->f3D8 &= ~4;
    if (o->f3F4 == 0 || ents == 0 || cnt <= 0) return;
    SrtGetPos_1c7430(o->f50, &c0);
    SrtGetPos_1c7430(o->f50, &b0);
    u = D_0045B080[0];
    c0.y += u;
    b0.y = b0.y - 100.0f * u;
    VecSub_1cbd00(&a0, &b0, &c0);
    idx = CollFindGroundTriMaybe_23af50(ents, cnt, o->h40E, &c0, &a0, &dc);
    if (idx < 0) return;
    e = &ents[idx];
    o->f3EC = c0.y + a0.y * dc;
    ok = !(o->f3D8 & 0x10);
    if (!(o->f3D0 & (0x400LL << 32))) {
        k3 = D_0047DB14 * u;
        t = o->f3EC;
        if (o->f74 - 2.0f * k3 < t) {
            o->f74 = t + k3;
            if (lim < o->f74) {
                o->f3D8 |= 1;
                ok = 1;
                if (!(e->t.q[3] & 0x1000)) o->h410 = 0;
            }
        }
    }
    o->f3D8 |= 4;
    *(Tri *)o->tv = e->t;
    o->f3E0 = o->f74 - o->f3EC;
    if ((o->f3D0 & (0x40000000LL << 32)) && !(o->f3D0 & (0x10000LL << 32)) && !(o->f3D8 & 0x10)) {
        f4 = D_0047DB14;
        f3 = o->f3E0;
        if (f4 * u <= f3 && f3 <= D_0047DB20 * u) {
            f4 = f4 * D_0045B080[0];
            { f32 h = o->f3EC + 0.5f * (f3 - f4); o->f74 = h + f4; }
            ok = 1;
            o->f3E0 = o->f74 - o->f3EC;
        }
    }
    if (!ok) return;
    if ((((o->f3D0 & (0x1000000LL << 32)) != 0) ^ 1) == 0) return;
    if (!(o->f3D8 & 0x10)) {
        j = CollRaycastNearest_1c86e0(ents, cnt, 0, &c0, &a0, &d8);
        if (j >= 0 && CollTriIsWaterMaybe_1ce5c0(&ents[j]) != 0) ok = 0;
    }
    if (!ok) return;
    if (idx != CollRaycastNearest_1c86e0(ents, cnt, o->h40E, &c0, &a0, &d4)) return;
    if (o->h150[3] & 0x1042) return;
    if (!(-d4 * a0.y <= 4.0f * u)) return;
    p.x = c0.x;
    tv = o->tv;
    p.y = o->f3EC;
    p.z = c0.z;
    p.w = 1.0f;
    r = D_0047DADC * u;
    rr = r * r;
    m0 = PointSegmentDistSq_1c92e0(&tv[1], &tv[2], &p);
    m1 = PointSegmentDistSq_1c92e0(&tv[2], &tv[0], &p);
    m2 = PointSegmentDistSq_1c92e0(&tv[0], &tv[1], &p);
    if (!(m0 < rr) && !(m1 < rr) && !(m2 < rr)) {
        VecCopy_1cbe30(&o->v100, &p);
        return;
    }
    k = (m0 < m1 && m0 < m2) ? 0 : (m1 < m2) ? 1 : 2;
    ClosestPointOnSegment_1c9f60(&v80, &tv[(k + 1) % 3], &tv[(k + 2) % 3], &p);
    VecAdd3_1cbd60(&v70, &tv[0], &tv[1], &tv[2]);
    VecDivScalarPoint_1cbbc0(&v70, &v70, 3.0f);
    t = r / VecDist_1cb420(&v70, &v80);
    if (!(t <= 1.0f)) t = 1.0f;
    VecLerpPoint_1cbac0(&o->v100, &v70, &v80, t);
}

}
