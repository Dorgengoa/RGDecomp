/* rgp:protos */
#define RGP_SELF_UiUpdateWidgets_2913a0 1
#include "port/game_protos.h"
#line 1
#pragma opt_dead_code off
#include "types.h"

typedef struct V2 { f32 a; f32 b; } V2;
typedef struct Obj {
    u8 pad0[0x14];
    f32 x;
    f32 y;
    u8 pad1C[0x14];
    f32 cur[4];
    f32 tgt[4];
    f32 spd[4];
    f32 tx;
    f32 ty;
    f32 sx;
    f32 sy;
    f32 px;
    f32 py;
    f32 rate;
    f32 t;
    s16 mode;
    s8 dirx;
    s8 diry;
} Obj;

typedef struct Node {
    Obj *obj;
    u8 pad4[4];
    struct Node *next;
} Node;

/*rgp*/
extern f32 D_0047D1E8;
extern f32 D_0047D1FC __attribute__((section(".sdata")));
extern volatile f32 D_0047D354;
extern f32 D_0047D404;

void UiUpdateWidgets_2913a0(Node **list) {
    Node *nd;
    Obj *o;
    s32 mode;
    f32 dx;
    f32 dy;
    f32 s;
    f32 a;
    f32 c;
    f32 p;
    f32 q;
    f32 ex;
    f32 ey;
    s32 i;

    for (nd = *list; nd != 0; nd = nd->next) {
        o = nd->obj;
        if (o == 0) return;
        mode = o->mode;
        if (mode == 0) {
            dx = o->tx - o->x;
            dy = o->ty - o->y;
            if (dx != 0.0f) {
                s = dx * o->sx;
                if (s < 0.0f) a = -s; else a = s;
                if (a < D_0047D1E8) {
                    o->x = o->tx;
                } else {
                    o->x = o->x + s;
                }
            }
            if (dy != 0.0f) {
                s = dy * o->sy;
                if (s < 0.0f) a = -s; else a = s;
                if (a < D_0047D1E8) {
                    o->y = o->ty;
                } else {
                    o->y = o->y + s;
                }
            }
        } else if (mode == 3) {
            if (!(o->t < (s = *(f32 *)&D_0047D1FC))) {
                o->x = o->tx;
                o->y = o->ty;
                o->t = s;
            } else {
                c = 1.0f + Cosf_128d30(o->t);
                c = Cosf_128d30(*(f32 *)&D_0047D1FC - *(f32 *)&D_0047D1FC * c / 2.0f) - 1.0f;
                p = c * (o->sx / 2.0f);
                q = c * (o->sy / 2.0f);
                ex = p - o->px;
                ey = q - o->py;
                if ((ex < 0.0f ? -ex : ex) < D_0047D354 && (ey < 0.0f ? -ey : ey) < D_0047D354) {
                    if (o->t <= D_0047D404) {
                        if ((ex < 0.0f ? -ex : ex) < 1.0f && (ey < 0.0f ? -ey : ey) < 1.0f) {
                            o->px = p;
                            o->py = q;
                            o->t = o->t + o->rate;
                            return;
                        }
                    } else {
                        o->x = o->tx;
                        o->y = o->ty;
                        o->t = D_0047D1FC;
                    }
                }
                if (ex < 0.0f) {
                    if (o->dirx > 0) ex = -ex;
                } else if (o->dirx < 0) {
                    ex = -ex;
                }
                o->x = o->x + ex;
                if (ex > 0.0f) {
                    if (!(o->x < o->tx)) o->x = o->tx;
                } else {
                    if (o->x <= o->tx) o->x = o->tx;
                }
                if (ey < 0.0f) {
                    if (o->diry > 0) ey = -ey;
                } else if (o->diry < 0) {
                    ey = -ey;
                }
                o->y = o->y + ey;
                if (ey > 0.0f) {
                    if (!(o->y < o->ty)) o->y = o->ty;
                } else {
                    if (o->y <= o->ty) o->y = o->ty;
                }
                o->px = p;
                o->py = q;
                o->t = o->t + o->rate;
            }
        } else if (mode == 1) {
            goto m12;
        } else if (mode == 2) {
        m12:
            dx = o->tx - o->x;
            dy = o->ty - o->y;
            if (dx != 0.0f) {
                if (dx > 0.0f) {
                    o->x = o->x + o->sx;
                    if (!(o->x < o->tx)) o->x = o->tx;
                } else {
                    o->x = o->x - o->sx;
                    if (o->x <= o->tx) o->x = o->tx;
                }
            }
            if (dy != 0.0f) {
                if (dy > 0.0f) {
                    o->y = o->y + o->sy;
                    if (!(o->y < o->ty)) o->y = o->ty;
                } else {
                    o->y = o->y - o->sy;
                    if (o->y <= o->ty) o->y = o->ty;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (o->tgt[i] <= -1.0f) continue;
            o->cur[i] = o->cur[i] + o->spd[i];
            if (o->spd[i] < 0.0f) {
                if (o->cur[i] <= o->tgt[i]) {
                    o->cur[i] = o->tgt[i];
                    o->tgt[i] = -1.0f;
                }
            } else {
                if (!(o->cur[i] < o->tgt[i])) {
                    o->cur[i] = o->tgt[i];
                    o->tgt[i] = -1.0f;
                }
            }
        }
    }
}
