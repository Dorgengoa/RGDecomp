/* rgp:protos */
#define RGP_SELF_CollMeshGatherFacesInBox_16cd90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) Vec4;
typedef struct V3 { f32 x, y, z; } V3;
typedef struct Mat { s16 h0, h2, h4, h6, flags, hA, hC, hE; } Mat;
typedef struct { s16 t[3]; } T3;
typedef struct { s16 v[4]; } V4h;

typedef struct {
    u16 m;
    u16 i0;
    u16 i1;
    u16 i2;
    s32 id;
} Face;

typedef struct {
    Vec4 v0;
    Vec4 v1;
    Vec4 v2;
    Vec4 n;
    Mat mat;
    s32 x50;
    s32 id;
    u8 pad58[8];
} Tri;

typedef struct {
    u8 pad0[0x44];
    V3 *verts;
    u8 pad48[4];
    Mat *mats;
} Mesh;

typedef struct {
    V3 a;
    s32 pad;
    V3 b;
} Seg;

/*rgp*/
/*rgp*/
/*rgp*/

s32 CollMeshGatherFacesInBox_16cd90(Mesh *mesh, Face *face, s32 n, s32 mask, Tri *tri, Seg *seg, s32 max)
{
    Vec4 p0 __attribute__((aligned(16)));
    Vec4 p1 __attribute__((aligned(16)));
    Vec4 tmin __attribute__((aligned(16)));
    Vec4 tmax __attribute__((aligned(16)));
    Vec4 nrm __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    V3 *va;
    V3 *vb;
    V3 *vc;
    Tri *out;
    s32 i;
    s32 cnt;
    Face *f;
    Mat *m;

    i = 0;
    cnt = 0;
    f = face;
    out = tri;
    p0.x = seg->a.x; p0.y = seg->a.y; p0.z = seg->a.z; p0.w = 1.0f;
    p1.x = seg->b.x; p1.y = seg->b.y; p1.z = seg->b.z; p1.w = 1.0f;
    for (; i < n; i++, f++) {
        m = &mesh->mats[f->m];
        if (!(mask & m->flags)) continue;
        va = &mesh->verts[f->i0];
        vb = &mesh->verts[f->i1];
        vc = &mesh->verts[f->i2];
        a.x = va->x; a.y = va->y; a.z = va->z;
        b.x = vb->x; b.y = vb->y; b.z = vb->z;
        c.x = vc->x; c.y = vc->y; c.z = vc->z;
        a.w = 1.0f; b.w = 1.0f; c.w = 1.0f;
        VecMinMax3_13df40(&tmin, &tmax, &a, &b, &c);
        if (AabbOverlap_13e0e0(&p0, &p1, &tmin, &tmax) == 0) continue;
        *(u128 *)&out->v0 = *(u128 *)&a;
        *(u128 *)&out->v1 = *(u128 *)&b;
        *(u128 *)&out->v2 = *(u128 *)&c;
        *(u128 *)&out->mat = 0;
        *(u64 *)&out->x50 = 0;
        out->mat.h0 = m->h0;
        out->mat.h2 = m->h2;
        out->mat.h4 = m->h4;
        out->mat.h6 = m->h6;
        out->mat.flags = m->flags;
        *(T3 *)&out->mat.hA = *(T3 *)&m->hA;
        out->id = f->id;
        VecTriCross_13de70(&nrm, &out->v0, &out->v1, &out->v2);
        cnt++;
        out->n = nrm;
        out++;
        if (cnt == max) break;
    }
    return cnt;
}
