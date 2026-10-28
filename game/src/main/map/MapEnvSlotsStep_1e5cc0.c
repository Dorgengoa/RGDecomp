/* rgp:protos */
#define RGP_SELF_MapEnvSlotsStep_1e5cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec3E5 {
    f32 x;
    f32 y;
    f32 z;
} Vec3E5;

typedef struct BlkE5 {
    s32 i;
    Vec3E5 v;
    f32 e;
    f32 f;
    f32 g;
    f32 h;
} BlkE5;

typedef struct S1E5CC0 {
    BlkE5 out;
    BlkE5 cur;
    BlkE5 dst;
    f32 t;
} S1E5CC0;

extern f32 D_0047DAE0;

void MapEnvSlotsStep_1e5cc0(S1E5CC0 *p)
{
    if (p->t <= 0.0f) {
        return;
    }
    p->t = p->t - D_0047DAE0;
    if (p->t <= 0.0f) {
        p->cur.i = p->dst.i;
        p->cur.v = p->dst.v;
        p->cur.e = p->dst.e;
        p->cur.f = p->dst.f;
        p->cur.g = p->dst.g;
        p->cur.h = p->dst.h;
        p->out.i = p->cur.i;
        p->out.v = p->cur.v;
        p->out.e = p->cur.e;
        p->out.f = p->cur.f;
        p->out.g = p->cur.g;
        p->out.h = p->cur.h;
        p->t = 0.0f;
    } else {
        p->out.v.x = p->dst.v.x + p->t * (p->cur.v.x - p->dst.v.x);
        p->out.v.y = p->dst.v.y + p->t * (p->cur.v.y - p->dst.v.y);
        p->out.v.z = p->dst.v.z + p->t * (p->cur.v.z - p->dst.v.z);
        p->out.e = p->dst.e + p->t * (p->cur.e - p->dst.e);
        p->out.f = p->dst.f + p->t * (p->cur.f - p->dst.f);
        p->out.g = p->dst.g + p->t * (p->cur.g - p->dst.g);
        p->out.h = p->dst.h + p->t * (p->cur.h - p->dst.h);
    }
}
