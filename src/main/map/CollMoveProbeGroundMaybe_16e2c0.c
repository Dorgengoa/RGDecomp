#include "types.h"

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) Vec4;
typedef struct { s32 v[12]; } M12;
typedef struct { f32 v[4]; } F4;
typedef struct { s16 v[3]; } H3;
typedef struct { s16 v[2]; } H2;
typedef struct { s16 a, b, c, d, e; H3 p; H2 q; } T10;
typedef struct {
    M12 m;
    F4 n;
    T10 ids;
    s32 f54;
    s32 f58;
    s32 f5C;
} Tri;

s32 CollSweepSphereGroundTrisMaybe_16eff0(Tri *, s32, Vec4 *, s32, s32 *, Vec4 *, s32, s32, f32);
void VecNormalize_13bd90(F4 *, F4 *);

s32 CollMoveProbeGroundMaybe_16e2c0(Vec4 *pos, Tri *out, Vec4 *outv, Tri *tris, s32 a, s32 b, f32 r, f32 h) {
    s32 idx[32];
    Vec4 seg[2];
    Vec4 hits[64];
    T10 loc;
    F4 tmp;
    s32 n;
    s32 i;
    T10 *t;
    Tri *src;

    seg[1] = *pos;
    seg[0] = *pos;
    seg[1].w = h;
    seg[0].y -= r;
    n = CollSweepSphereGroundTrisMaybe_16eff0(tris, a, &seg[1], 0x20, idx, hits, 1, b, -r);
    if (n == 0) {
        return 0;
    }
    loc.a = 0;
    loc.b = 0;
    loc.c = 0;
    while (n > 0) {
        VecNormalize_13bd90(&tmp, &tris[idx[0]].n);
        *outv = hits[0];
        src = &tris[idx[0]];
        out->m = src->m;
        out->n = src->n;
        out->ids = src->ids;
        out->f54 = src->f54;
        outv->x = seg[1].x;
        outv->z = seg[1].z;
        loc.a = out->ids.a;
        loc.b = out->ids.b;
        loc.c = out->ids.c;
        loc.d = out->ids.d;
        loc.e = out->ids.e;
        loc.p = out->ids.p;
        loc.q = out->ids.q;
        break;
    }
    for (i = 0; i < n; i++) {
        t = &tris[idx[i]].ids;
        if (!loc.a) {
            loc.a = t->a;
        }
        if (!loc.b) {
            loc.b = t->b;
        }
        if (!loc.c) {
            loc.c = t->c;
        }
    }
    out->ids.a = loc.a;
    out->ids.b = loc.b;
    out->ids.c = loc.c;
    out->ids.d = loc.d;
    out->ids.e = loc.e;
    out->ids.p = loc.p;
    out->ids.q = loc.q;
    return n > 0;
}
