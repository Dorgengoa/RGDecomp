/* rgp:protos */
#define RGP_SELF_ProjectileQueueHit_317860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct Ent {
    s16 a;
    s16 id;
    s16 c;
    s16 d;
    s16 e;
    s16 f;
    f32 t;
    Vec3 v;
} Ent;

typedef struct Tl {
    u8 pad[0x1CC];
    s32 count;
    Ent e[40];
} Tl;

typedef struct Arg {
    s32 a;
    s32 pad04;
    s32 id;
    s32 d;
    s32 c;
    u8 pad14[0xC];
    f32 vx;
    f32 vy;
    f32 vz;
    u8 pad2c[4];
    f32 t;
    s32 e;
    s32 f;
} Arg;

s32 ProjectileQueueHit_317860(Tl *tl, Arg *arg) {
    s32 i;
    s32 j;
    s32 n;
    s32 k;
    s32 m;

    n = tl->count;
    for (i = 0; i < n; i++) {
        if (arg->id == tl->e[i].id) {
            return 0;
        }
        if (arg->t <= tl->e[i].t) {
            break;
        }
    }
    if (i < n) {
        for (j = i + 1; j < (n = tl->count); j++) {
            if (arg->id == tl->e[j].id) {
                for (k = j + 1; k < tl->count; k++) {
                    tl->e[k - 1].a = tl->e[k].a;
                    tl->e[k - 1].id = tl->e[k].id;
                    tl->e[k - 1].c = tl->e[k].c;
                    tl->e[k - 1].d = tl->e[k].d;
                    tl->e[k - 1].e = tl->e[k].e;
                    tl->e[k - 1].f = tl->e[k].f;
                    tl->e[k - 1].t = tl->e[k].t;
                    tl->e[k - 1].v = tl->e[k].v;
                }
                j--;
                tl->count--;
            }
        }
    }
    if (n >= 40) {
        return 0;
    }
    m = n;
    for (; i < m; m--) {
        tl->e[m].a = tl->e[m - 1].a;
        tl->e[m].id = tl->e[m - 1].id;
        tl->e[m].c = tl->e[m - 1].c;
        tl->e[m].d = tl->e[m - 1].d;
        tl->e[m].e = tl->e[m - 1].e;
        tl->e[m].f = tl->e[m - 1].f;
        tl->e[m].t = tl->e[m - 1].t;
        tl->e[m].v = tl->e[m - 1].v;
    }
    tl->e[i].a = arg->a;
    tl->e[i].id = arg->id;
    tl->e[i].c = arg->c;
    tl->e[i].d = arg->d;
    tl->e[i].t = arg->t;
    tl->e[i].e = arg->e;
    tl->e[i].f = arg->f;
    tl->e[i].v.x = arg->vx;
    tl->e[i].v.y = arg->vy;
    tl->e[i].v.z = arg->vz;
    tl->count++;
    return 1;
}
