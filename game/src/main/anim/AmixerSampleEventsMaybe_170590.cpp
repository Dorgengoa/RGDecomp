/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct Key {
    u8 pad0[0xC];
    f32 start;                          /* 0x0C */
    f32 end;                            /* 0x10 */
    f32 time;                           /* 0x14 */
    f32 step;                           /* 0x18 */
    f32 scale;                          /* 0x1C */
    f32 mult;                           /* 0x20 */
} Key;

typedef struct Track {
    u8 pad0[0x10];
    f32 f10;
} Track;

typedef struct Blend {
    Key *a;
    Key *b;
    Track *ta;
    Track *tb;
    u8 pad10[4];
} Blend;

typedef struct Ev {
    s32 count;
    u8 *tracks;
    s32 nblend;
    Blend *blends;
} Ev;

typedef struct Item {
    Key *node;
    f32 t;
    f32 w;
} Item;

typedef struct V3 {
    f32 x[3];
} V3;

typedef struct Vec {
    u32 cap;
    u32 size;
    Item *data;
} Vec;

class Iter {
public:
    Item *p;

    Iter() {}
    Iter &operator=(Item *q) { p = q; return *this; }
    Iter &operator++() { p = p + 1; return *this; }
};

inline bool operator==(const Iter &a, const Iter &b)
{
    return a.p == b.p;
}
inline bool operator!=(const Iter &a, const Iter &b) { return !(a == b); }

extern "C" {
void Vec3VectorReserve_171230(Vec *, u32);
s32 AmixerTrackSampleKey_170bb0(u8 *, Item *, f32);
void Vec3VectorInsertN_170df0(Vec *, Item *, u32, Item *);
f32 AmixerBlendCurveEvalMaybe_170180(Blend *, f32);
void Vec3VectorDeletingDtor_1713b0(Vec *, s32);
extern volatile f32 D_0047D24C;
}

static inline f32 snap(f32 q)
{
    f32 r = (f32)(s32)(0.5f + q);
    f32 d = q - r;
    d = (d < 0.0f) ? -d : d;
    return (d <= D_0047D24C) ? r : q;
}

static inline Item *find(Vec *v, Key *k)
{
    Iter it __attribute__((aligned(16)));
    Iter end __attribute__((aligned(16)));

    if (k == 0) {
        return 0;
    }
    for (it = v->data, end = v->data + v->size; it != end; ++it) {
        if (it.p->node == k) {
            return it.p;
        }
    }
    return 0;
}

extern "C" void AmixerSampleEventsMaybe_170590(Ev *ev, Vec *out, f32 t)
{
    Vec tmp __attribute__((aligned(16)));
    u8 *p;
    s32 i;
    Item val __attribute__((aligned(16)));
    s32 n;
    s32 j;
    Blend *e;
    Key *a;
    Key *b;
    Item *ka;
    Item *kb;
    f32 q;
    f32 d;
    f32 w;
    f32 f;
    Item i1 __attribute__((aligned(16)));
    Item i2 __attribute__((aligned(16)));
    Iter it __attribute__((aligned(16)));
    Iter end __attribute__((aligned(16)));
    V3 v __attribute__((aligned(16)));
    Track *ta;
    Track *tb;

    tmp.cap = 0;
    tmp.size = 0;
    tmp.data = 0;
    Vec3VectorReserve_171230(&tmp, ev->count * 2);
    for (i = 0, p = ev->tracks; i < ev->count; i++, p += 0x14) {
        val.w = 1.0f;
        val.node = 0;
        val.t = 0.0f;
        if (AmixerTrackSampleKey_170bb0(p, &val, t) != 0) {
            Vec3VectorInsertN_170df0(&tmp, tmp.data + tmp.size, 1, &val);
        }
    }
    n = ev->nblend;
    for (j = 0; j < n; j++) {
        if (j < 0 || j >= ev->nblend) {
            e = 0;
        } else {
            e = &ev->blends[j];
        }
        if (e == 0) {
            break;
        }
        a = e->a;
        b = e->b;
        if (a == 0 || b == 0) {
            continue;
        }
        ka = find(&tmp, a);
        kb = find(&tmp, b);
        if (ka != 0 && kb != 0) {
            {
            f32 bt = b->time;
            q = snap((1.0f + (a->end - a->start)) / a->step); { f32 r; f32 dd; f32 x = q * a->mult; r = (f32)(s32)(0.5f + x); dd = x - r; dd = (dd < 0.0f) ? -dd : dd; q = (dd <= D_0047D24C) ? r : x; }
            d = (a->time + q) - bt;
            }
            if (d < 0.0f) {
                continue;
            }
            f = (t - b->time) / d;
            if (f < 0.0f || !(f <= 1.0f)) {
                continue;
            }
            w = AmixerBlendCurveEvalMaybe_170180(e, f);
            ka->w *= 1.0f - w;
            kb->w *= w;
        } else if (ka == 0 && kb == 0) {
            q = snap((1.0f + (a->end - a->start)) / a->step); q = a->time + snap(q * a->mult);
            d = b->time - q;
            if (d < 0.0f) {
                continue;
            }
            f = (t - q) / d;
            if (f < 0.0f || !(f <= 1.0f)) {
                continue;
            }
            w = AmixerBlendCurveEvalMaybe_170180(e, f);
            ta = e->ta;
            tb = e->tb;
            if ((f32)(s32)a->mult == a->mult) {
                i1.t = a->start + (1.0f + (a->end - a->start));
            } else {
                i1.t = a->start + ((f32)a->mult - (f32)(s32)a->mult) * (1.0f + (a->end - a->start));
            }
            i1.node = a;
            i1.w = a->scale;
            i2.node = b;
            i2.t = b->start;
            i2.w = b->scale;
            i1.w = a->scale * (ta->f10 * (1.0f - w));
            i2.w = b->scale * (tb->f10 * w);
            Vec3VectorInsertN_170df0(&tmp, tmp.data + tmp.size, 1, &i1);
            Vec3VectorInsertN_170df0(&tmp, tmp.data + tmp.size, 1, &i2);
        }
    }
    for (it = tmp.data, end = tmp.data + tmp.size; it != end; ++it) {
        v = *(V3 *)it.p;
        Vec3VectorInsertN_170df0(out, out->data + out->size, 1, (Item *)&v);
    }
    Vec3VectorDeletingDtor_1713b0(&tmp, 0);
}
