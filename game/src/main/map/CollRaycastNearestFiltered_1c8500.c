/* rgp:protos */
#define RGP_SELF_CollRaycastNearestFiltered_1c8500 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct {
    Vec4 start;
    Vec4 dir;
    f32 r;
    f32 t;
    u8 pad28[8];
    Vec4 d;
    Vec4 e;
    Vec4 f;
    Vec4 g;
    f32 rr;
    f32 len;
} Seg;

typedef struct {
    u8 pad0[0x34];
    f32 x34;
    u8 pad38[0xE];
    s16 x46;
    u8 pad48[0x18];
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CollRaycastNearestFiltered_1c8500(Ent *ent, s32 n, s32 mask, Vec4 *start, Vec4 *end, f32 *out, f32 r0, f32 r1)
{
    Seg seg __attribute__((aligned(16)));
    Vec4 m __attribute__((aligned(16)));
    Vec4 v __attribute__((aligned(16)));
    s32 best;
    s32 i;
    u8 *p;
    u32 c;

    if (out != NULL) {
        *out = 1.0f;
    }
    if (ent == NULL || n <= 0) {
        return -1;
    }
    VecCopyAsPoint_1cbe10(&seg.start, start);
    VecCopyAsDir_1cbe20(&seg.dir, end);
    seg.r = 0.0f;
    seg.rr = seg.r * seg.r;
    seg.len = VecLengthSq_1cb470(&seg.dir, 0);
    seg.t = 1.0f;
    VecLinearCombine_1cb8b0(&m, &seg.dir, &seg.start, 1.0f, 1.0f);
    VecMinMax_1cb570(&seg.e, &seg.d, &seg.start, &m);
    c = 0x10;
    p = (u8 *)&v;
    if (p != NULL) {
        do {
            *p = 0;
            c--;
            p++;
        } while (c != 0);
    }
    v.x = seg.r;
    v.y = seg.r;
    v.z = seg.r;
    VecAdd_1cbdc0(&seg.g, &seg.e, &v);
    VecSub_1cbd00(&seg.f, &seg.d, &v);
    best = -1;
    for (i = 0; i < n; i++, ent++) {
        if ((ent->x46 & mask) == 0 && !FloatOutOfRange_1c9210(ent->x34, r0, r1) &&
            CollSweepTri_1c7790(&seg, ent, (u8 *)ent + 0x10, (u8 *)ent + 0x20) != 0) {
            best = i;
        }
    }
    if (out != NULL) {
        *out = seg.t;
    }
    return best;
}
