#include "types.h"

typedef struct Vec { f32 x, y, z, w; } Vec;
typedef struct Hit { Vec pos; s32 idx; f32 dist; s32 pad[2]; } Hit;
typedef struct Item { Vec a; Vec b; Vec c; u8 pad[0x46 - 0x30]; s16 flags; u8 pad2[0x60 - 0x48]; } Item;
typedef struct Obj { Vec f0; Vec f10; f32 f20; f32 f24; f32 pad28[2]; Vec f30; Vec f40; Vec f50; Vec f60; } Obj;

extern s32 CollSweepTri_1c7790(Obj *, Vec *, Vec *, Vec *);
extern void VecMinMax_1cb570(Vec *, Vec *, Obj *, Vec *);
extern void VecLinearCombine_1cb8b0(void *, Vec *, Obj *, f32, f32);
extern void VecSub_1cbd00(Vec *, Vec *, Vec *);
extern void VecAdd_1cbdc0(Vec *, Vec *, Vec *);

static inline void Zero(void *p, u32 n) {
    u8 *b;
    u32 k;
    k = n;
    b = (u8 *)p;
    if (b != 0) {
        do {
            *b = 0;
            k--;
            b++;
        } while (k != 0);
    }
}

s32 CollSweepCollectHits_1c7550(Obj *obj, Hit *list, s32 max, Item *items, s32 n, s32 mask) {
    Vec tmp;
    Vec sc;
    f32 saved;
    s32 count;
    Item *it;
    s32 i;
    s32 j;
    s32 k;
    Hit *h;
    f32 f;
    f32 x, y, z, w;

    if (list == 0 || max <= 0) return 0;
    if (items == 0 || n <= 0) return 0;
    saved = obj->f24;
    count = 0;
    it = items;
    for (i = 0; i < n; i++, it++) {
        if (it->flags & mask) continue;
        if (CollSweepTri_1c7790(obj, &it->a, &it->b, &it->c) == 0) continue;
        for (j = 0, h = list; j < count; j++, h++) {
            if (!(h->dist <= obj->f24)) break;
        }
        if (count < max) count++;
        if (j < count) {
            for (k = count - 1; j < k; k--) {
                h = &list[k];
                h->pos = h[-1].pos;
                h->idx = h[-1].idx;
                h->dist = h[-1].dist;
            }
            h = &list[j];
            h->idx = i;
            h->dist = obj->f24;
            VecLinearCombine_1cb8b0(h, &obj->f10, obj, obj->f24, 1.0f);
        }
        obj->f24 = saved;
        VecLinearCombine_1cb8b0(&tmp, &obj->f10, obj, obj->f24, 1.0f);
        VecMinMax_1cb570(&obj->f40, &obj->f30, obj, &tmp);
        Zero(&sc, 16);
        f = obj->f20;
        sc.x = f;
        sc.y = f;
        sc.z = f;
        VecAdd_1cbdc0(&obj->f60, &obj->f40, &sc);
        VecSub_1cbd00(&obj->f50, &obj->f30, &sc);
    }
    return count;
}
