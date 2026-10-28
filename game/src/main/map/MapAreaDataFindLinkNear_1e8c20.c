/* rgp:protos */
#define RGP_SELF_MapAreaDataFindLinkNear_1e8c20 1
#define RGP_SELF_clr 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Tgt {
    u8 pad[0x20];
} Tgt;

typedef struct Owner {
    u8 pad0[0x16DC];
    Tgt *list;
    s32 count;
} Owner;

typedef struct V2 {
    f32 x;
    f32 y;
} V2;

typedef struct V3 {
    f32 x;
    f32 y;
    f32 z;
} V3;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[4];
extern f32 D_0047D404;
extern f32 D_0047D5D0;

static inline void clr(void *p, s32 n)
{
    u8 *q;
    s32 c;
    q = (u8 *)p;
    c = n;
    if (q != NULL) {
        do {
            *q++ = 0;
        } while (--c != 0);
    }
}
Tgt *MapAreaDataFindLinkNear_1e8c20(Owner *o, V3 *p)
{
    V2 d __attribute__((aligned(16)));
    Tgt *t;
    Tgt *best;
    s32 i;
    f32 bestd;
    f32 dist;
    f32 margin;
    f32 ang;
    f32 hi;
    f32 a;
    f32 r;

    t = o->list;
    if (t == NULL || o->count <= 0) {
        return NULL;
    }
    best = NULL;
    r = 1.5f * D_0045B080[0];
    bestd = r * r;
    margin = D_0047D5D0 * D_0045B080[0];
    for (i = 0; i < o->count; i++, t++) {
        if (p->y < MapLinkGetY_1e92d0(t) - margin) continue;
        hi = MapLinkGetTopY_1e92c0(t);
        hi = hi + margin;
        if (hi < p->y) continue;
        clr(&d, sizeof(V2));
        d.x = p->x - MapLinkGetX_1e92f0(t);
        d.y = p->z - MapLinkGetZ_1e92e0(t);
        dist = d.x * d.x + d.y * d.y;
        if (!(dist <= bestd)) continue;
        ang = AngleWrap_1cbf30(Atan2f_1291a8(d.x, d.y) - MapLinkGetAngle_1e9250(t));
        if (p->y - MapLinkGetY_1e92d0(t) > MapLinkGetTopY_1e92c0(t) - p->y) {
            ang = (ang < 0.0f) ? -ang : ang;
            if (!(ang <= D_0047D404)) continue;
        } else {
            ang = (ang < 0.0f) ? -ang : ang;
            if (ang < D_0047D404) continue;
        }
        bestd = dist;
        best = t;
    }
    return best;
}
