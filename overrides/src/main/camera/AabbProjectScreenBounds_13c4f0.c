/* rg-override: replaces game/src/main/camera/AabbProjectScreenBounds_13c4f0.c sha256 e4bad57a57fa776272e6339672b25e583fb8f73cf7463eb43bf48047afaf1af7
 * why: asm body (asmexclude, L5 VU0 library); C port from the retail listing.
 * AabbProjectScreenBounds_13c4f0(max, min, A, B, bmin, bmax): the 8 corners of the box
 * (AabbCorners_13e190) through M = A x B (M[j] = A[0]*B[j].x + A[1]*B[j].y + A[2]*B[j].z
 * + A[3]*B[j].w, the vmula/vmadd column chains), each projected p.xy *= 1/|p.w|
 * (vabs.w, vdiv Q = vf0w / |w|, vmulq.xy; z and w are kept), then the component-wise
 * max (sqc2 to $a0) and min (to $a1) over all eight.  Caller:
 * ModelPrepareDrawMaybe_14f760 (model draw with req->bounds). */
#include "types.h"

void AabbCorners_13e190(void *, void *, void *);

typedef struct { f32 v[4]; } Q4_13c4f0;

void AabbProjectScreenBounds_13c4f0(void *max, void *min, void *a, void *b, void *bmin, void *bmax)
{
    Q4_13c4f0 corners[8] __attribute__((aligned(16)));
    const Q4_13c4f0 *A = (const Q4_13c4f0 *)a;
    const Q4_13c4f0 *B = (const Q4_13c4f0 *)b;
    Q4_13c4f0 M[4], hi, lo;
    int i, j, k;

    AabbCorners_13e190(corners, bmin, bmax);
    for (j = 0; j < 4; j++)
        for (k = 0; k < 4; k++)
            M[j].v[k] = A[0].v[k] * B[j].v[0] + A[1].v[k] * B[j].v[1] +
                        A[2].v[k] * B[j].v[2] + A[3].v[k] * B[j].v[3];
    for (i = 0; i < 8; i++) {
        Q4_13c4f0 p;
        f32 w, q;
        for (k = 0; k < 4; k++)
            p.v[k] = M[0].v[k] * corners[i].v[0] + M[1].v[k] * corners[i].v[1] +
                     M[2].v[k] * corners[i].v[2] + M[3].v[k] * corners[i].v[3];
        w = p.v[3] < 0.0f ? -p.v[3] : p.v[3];
        q = 1.0f / w;
        p.v[0] *= q;
        p.v[1] *= q;
        if (i == 0) {
            hi = p;
            lo = p;
        } else {
            for (k = 0; k < 4; k++) {
                if (p.v[k] > hi.v[k]) hi.v[k] = p.v[k];
                if (p.v[k] < lo.v[k]) lo.v[k] = p.v[k];
            }
        }
    }
    *(Q4_13c4f0 *)max = hi;
    *(Q4_13c4f0 *)min = lo;
}
