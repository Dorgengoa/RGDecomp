/* rgp:protos */
#define RGP_SELF_MeshRaycastTris_16f3c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) Vec4;

typedef struct {
    Vec4 v0;
    Vec4 v1;
    Vec4 v2;
    Vec4 n;
    u8 pad40[6];
    s16 flags;
    u8 pad48[0x18];
} Tri;

typedef struct {
    s32 count;
    Tri *tris;
} Mesh;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MeshRaycastTris_16f3c0(Mesh *mesh, Vec4 *p0, Vec4 *p1, Vec4 *out, s32 nearest, s32 mask) { RG_VU0_FRAME;
    s32 have;
    s32 n;
    s32 i;
    s32 best;
    Tri *tri;
    f32 d0;
    f32 d1;
    f32 dist;
    f32 bestd;
    Vec4 hit __attribute__((aligned(16)));
    Vec4 tmax __attribute__((aligned(16)));
    Vec4 tmin __attribute__((aligned(16)));
    Vec4 bmin __attribute__((aligned(16)));
    Vec4 bmax __attribute__((aligned(16)));
    Vec4 tmp __attribute__((aligned(16)));

    if (mesh == 0) {
        return 0;
    }
    best = -1;
    have = 0;
    VecMaxMin_13df70(&bmin, &bmax, p0, p1);
    tri = mesh->tris;
    n = mesh->count;
    if (tri == 0 || n == 0) {
        return -1;
    }
    for (i = 0; i < n; i++, tri++) {
        if (tri->flags & mask) {
            continue;
        }
        VecMinMax3_13df40(&tmin, &tmax, &tri->v0, &tri->v1, &tri->v2);
        if (AabbOverlap_13e0e0(&bmin, &bmax, &tmin, &tmax) == 0) {
            continue;
        }
        VecSub_13be40(&tmp, p0, &tri->v0);
        d0 = Vu0InnerProduct_13bd60(&tri->n, &tmp);
        VecSub_13be40(&tmp, p1, &tri->v0);
        d1 = Vu0InnerProduct_13bd60(&tri->n, &tmp);
        if (!(d0 <= 0.0f || d1 <= 0.0f)) {
            continue;
        }
        if (d0 < 0.0f && d1 < 0.0f) {
            continue;
        }
        if (RayTriIntersect_13d8c0(p0, p1, &tri->v0, &tri->v1, &tri->v2, &tri->n, &hit) == 0) {
            continue;
        }
        if (nearest == 0) {
            best = i;
            *out = hit;
            break;
        }
        {
            f32 dx = p0->x - hit.x;
            f32 dy = p0->y - hit.y;
            f32 dz = p0->z - hit.z;
            dist = dx * dx + dy * dy + dz * dz;
        }
        if (have == 0) {
            bestd = dist;
            best = i;
            *out = hit;
        } else if (!(bestd <= dist)) {
            bestd = dist;
            best = i;
            *out = hit;
        }
        have = 1;
    }
    return best;
}
