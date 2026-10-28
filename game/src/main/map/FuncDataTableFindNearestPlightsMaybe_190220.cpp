#include "types.h"

struct Pair8 {
    s32 a;
    s32 b;
};

struct Ent {
    Pair8 hdr[6];
    s16 x30;
    s16 x32;
    s32 x34;
    s32 x38;
    s32 x3C;
    s32 x40;
    s32 x44;
    s32 x48;
    s32 x50 __attribute__((aligned(8)));
    s32 x54;
    f32 x58;
    f32 x5C;
    Pair8 body[10];
};

struct Obj {
    Ent e;
    f32 x70x;
};

struct OutEnt {
    Pair8 hdr[6];
    s16 x30;
    s16 x32;
    s32 x34;
    s32 x38;
    s32 x3C;
    s32 x40;
    s32 x44;
    s32 x48;
    s32 x50 __attribute__((aligned(8)));
    s32 x54;
    f32 x58;
    f32 x5C;
    Pair8 body[10];
};

struct Node {
    Node *next;
    s8 _4[0xC];
    u8 *obj;
};

struct Lists {
    s8 _0[8];
    Node *h2;
    Node *h3;
    Node *h1;
};

struct Mgr {
    s8 _0[4];
    Lists *lists;
    Node *cur;
};

typedef struct {
    f32 x, y, z, w;
} Vec4;

extern "C" {
void VecScale_13be00(void *, void *, f32);
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
void NodeGetScale_186560(void *, Vec4 *);
void NodeGetTranslation_186650(void *, Vec4 *);
s32 FuncDataTableFindNearestPlightsMaybe_190220(Mgr *m, Vec4 *p, Ent *out, s32 max, s32 unused, u32 flags);
}

static inline u8 *nextObj(Mgr *m) {
    Node *n = m->cur;
    if (n == 0) {
        return 0;
    }
    m->cur = n->next;
    return n->obj;
}

#define F(o, off, T) (*(T *)((o) + (off)))

s32 FuncDataTableFindNearestPlightsMaybe_190220(Mgr *m, Vec4 *p, Ent *out, s32 max, s32 unused, u32 flags) {
    f32 dists[64] __attribute__((aligned(16)));
    void *ents[64];
    Vec4 v __attribute__((aligned(16)));
    Vec4 v2 __attribute__((aligned(16)));
    s32 n;
    s32 alt;
    u8 *o;
    s32 i;

    if (max <= 0) {
        return 0;
    }
    n = 0;
    alt = 0;
    if (flags & 1) {
        alt = 1;
    }
    m->cur = 0;
    if (m->lists != 0) {
        m->cur = m->lists->h1;
    }
    while ((o = nextObj(m)) != 0) {
        f32 d;
        if (n >= 64) {
            break;
        }
        if (F(o, 0x48, s32) == 0) {
            continue;
        }
        if (F(o, 0x78, s32) != 2) {
            continue;
        }
        if (alt) {
            if (F(o, 0x7C, s32) == 0) {
                continue;
            }
        } else {
            if (F(o, 0x88, s32) != 0) {
                continue;
            }
        }
        NodeGetTranslation_186650(o, &v);
        d = VecDistance_13d3d0(p, &v);
        if (d < F(o, 0x74, f32) + p->w) {
            dists[n] = d;
            ents[n] = o;
            n++;
        }
    }
    m->cur = 0;
    if ((flags & 3) == 3) {
        m->cur = 0;
        if (m->lists != 0) {
            m->cur = m->lists->h2;
        }
        while ((o = nextObj(m)) != 0) {
            f32 d;
            if (n >= 64) {
                break;
            }
            if (F(o, 0x78, s32) == 0) {
                continue;
            }
            if (F(o, 0x48, s32) == 0) {
                continue;
            }
            NodeGetTranslation_186650(o, &v);
            d = VecDistance_13d3d0(p, &v);
            if (d <= 300.0f) {
                dists[n] = d;
                ents[n] = o;
                n++;
            }
        }
        m->cur = 0;
        m->cur = 0;
        if (m->lists != 0) {
            m->cur = m->lists->h3;
        }
        while ((o = nextObj(m)) != 0) {
            f32 d;
            if (n >= 64) {
                break;
            }
            if (F(o, 0x78, s32) == 0) {
                continue;
            }
            if (F(o, 0x48, s32) == 0) {
                continue;
            }
            NodeGetTranslation_186650(o, &v);
            d = VecDistance_13d3d0(p, &v);
            if (d <= 300.0f) {
                dists[n] = d;
                ents[n] = o;
                n++;
            }
        }
        m->cur = 0;
    }
    if (n <= 0) {
        return 0;
    }
    if (n < max) {
        max = n;
    }
    for (i = 0; i < max; i++) {
        f32 *di = &dists[i];
        void **ei = &ents[i];
        s32 j;
        for (j = i + 1; j < n; j++) {
            f32 *dj = &dists[j];
            f32 a = *dj;
            f32 b = *di;
            if (!(b <= a)) {
                void *t;
                *di = a;
                *dj = b;
                t = *ei;
                *ei = ents[j];
                ents[j] = t;
            }
        }
    }
    for (i = 0; i < max; i++) {
        Ent *src = (Ent *)ents[i];
        Ent *dst = &out[i];
        void *sb = &src->body[0];
        switch (src->x40) {
        case 4:
            *dst = *src;
            break;
        case 2:
        case 3:
            *dst = *src;
            dst->x40 = 4;
            NodeGetScale_186560(src, &v2);
            VecScale_13be00(&dst->body[0], sb, 1.0f);
            F((u8 *)dst, 0x70, f32) = 60.0f * v2.y;
            F((u8 *)dst, 0x74, f32) = 8.0f * F((u8 *)dst, 0x70, f32);
            F((u8 *)dst, 0x78, s32) = 2;
            F((u8 *)dst, 0x7C, s32) = 1;
            F((u8 *)dst, 0x80, s32) = 1;
            F((u8 *)dst, 0x84, s32) = 0;
            F((u8 *)dst, 0x8C, s32) = 1;
            F((u8 *)dst, 0x90, f32) = 0.2f;
            break;
        }
    }
    return max;
}
