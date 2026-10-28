/* rgp:protos */
#define RGP_SELF_MapEnvSlotsSetTarget_1e5e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z; } V3e;

typedef struct T1e5e40 {
    s32 f00;
    V3e v04;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    s32 f20;
    V3e v24;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    s32 f40;
    V3e v44;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5C;
    f32 f60;
} T1e5e40;

void MapEnvSlotsSetTarget_1e5e40(T1e5e40 *s, s32 a, s32 flag, f32 x, f32 y, f32 z,
                  f32 w, f32 p, f32 q, f32 r)
{
    if (w == p) {
        return;
    }
    if (flag == 0) {
        if (a == s->f20) {
            return;
        }
        if (a == s->f40) {
            return;
        }
    }
    s->f40 = a;
    s->v44.x = x;
    s->v44.y = y;
    s->v44.z = z;
    s->f50 = w;
    s->f54 = p;
    s->f58 = q;
    s->f5C = r;
    if (flag == 0 && s->f00 >= 0 && a >= 0) {
        goto one;
    }
    s->f20 = s->f40;
    s->v24 = s->v44;
    s->f30 = s->f50;
    s->f34 = s->f54;
    s->f38 = s->f58;
    s->f3C = s->f5C;
    s->f00 = s->f20;
    s->v04 = s->v24;
    s->f10 = s->f30;
    s->f14 = s->f34;
    s->f18 = s->f38;
    s->f1C = s->f3C;
    s->f60 = 0.0f;
    return;
one:
    s->f60 = 1.0f;
}
