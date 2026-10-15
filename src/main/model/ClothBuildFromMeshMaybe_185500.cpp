#include "types.h"
static inline f32 *BroadWrite(f32 *dest, f32 value){*dest=value;return dest+1;}

#include "vec.h"

class Mdl {
public:
    virtual void v08();
    virtual s32 Has(s32);
    s32 x4;
    u8 pad8[8];
    f32 x10;
    f32 x14;
    f32 x18;
    u8 pad1C[0x50 - 0x1C];
    s32 x50;
    s32 x54;
};

typedef struct Prim {
    struct Prim *x0;
    s32 x4;
    s32 x8;
    u8 padC[0xC];
    struct Idx *x18;
} Prim;

typedef struct Idx {
    u8 pad0[4];
    u16 *x4;
} Idx;

typedef struct Grp {
    struct Grp *x0;
    Prim *x4;
} Grp;

class Obj {
public:
    u8 pad0[0x50];
    virtual void v08();
    virtual s32 Has(s32);
    virtual Mdl *GetMdl(void);
    u8 pad54[0xF0 - 0x54];
    Grp *xF0;
};

typedef struct Holder {
    Obj *x0;
} Holder;

typedef struct Edge {
    s32 a;
    s32 b;
    f32 len;
    f32 w;
} Edge;

typedef struct Mesh {
    Mdl *x0;
    s32 x4;
    Vec4 *x8;
    Vec4 *xC;
    Vec4 *x10;
    Vec4 *x14;
    s32 x18;
    Edge *x1C;
    u8 pad20[0x60 - 0x20];
    f32 x60;
    f32 x64;
    f32 x68;
} Mesh;

extern "C" {
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
void *MemStackNew_14e1b0(s32, s32);
void VertsUnpackQuantized_164d30(Vec4 *, s32, s32, s32, f32 *);
s32 ClothBuildFromMeshMaybe_185500(Mesh *m, Holder *h, s32 heap);
}

static inline s32 AddEdge(Mesh *m, Edge *out, s32 a, s32 b) {
    Edge *e = m->x1C;
    s32 n = m->x18;
    s32 i;
    for (i = 0; i < n; i++, e++) {
        if (e->a == a && e->b == b) {
            return 0;
        }
        if (e->b == a && e->a == b) {
            return 0;
        }
    }
    out->a = a;
    out->b = b;
    out->w = 0.5f;
    out->len = VecDistance_13d3d0(&m->x8[a], &m->x8[b]);
    return 1;
}

extern "C" s32 ClothBuildFromMeshMaybe_185500(Mesh *m, Holder *h, s32 heap)
{
    s32 i;
    Edge *out;
    s32 n;
    f32 mx;
    Mdl *mdl;
    Obj *o;
    u16 *s;
    s32 cnt;
    Prim *p2;
    Grp *g;
    Prim *p;
    s32 k;
  s32 k_w120;

    if (h == 0 || (o = h->x0) == 0) {
        return 0;
    }
    if (o == 0) {
        return 0;
    }
    mdl = o->GetMdl();
    if (!mdl->Has(8)) {
        return 0;
    }
    if (!o->Has(2)) {
        return 0;
    }
    m->x0 = mdl;
    m->x4 = mdl->x50;
    if (m->x4 == 0) {
        m->x0 = 0;
        return 0;
    }
    if ((m->x8 = (Vec4 *)MemStackNew_14e1b0(m->x4 << 4, heap)) == 0) {
        return 0;
    }
    if ((m->xC = (Vec4 *)MemStackNew_14e1b0(m->x4 << 4, heap)) == 0) {
        return 0;
    }
    if ((m->x10 = (Vec4 *)MemStackNew_14e1b0(m->x4 << 4, heap)) == 0) {
        return 0;
    }
    if ((m->x14 = (Vec4 *)MemStackNew_14e1b0(m->x4 << 4, heap)) == 0) {
        return 0;
    }
    VertsUnpackQuantized_164d30(m->x8, m->x0->x54, m->x0->x50, m->x0->x4, &m->x0->x10);
    for (i = 0; i < m->x4; i++) {
        m->xC[i] = m->x8[i];
        m->x14[i] = m->x8[i];
        m->x14[i].w = 0.0f;
        VEC4_ZERO(m->x10[i]);
    }
    {
        f32 b = m->x0->x14, a = m->x0->x10;
        if (a > b) {
            mx = (a > m->x0->x18) ? a : m->x0->x18;
        } else {
            mx = (b > m->x0->x18) ? b : m->x0->x18;
        }
    }
    mx *= 4.0f;
    {f32 *cursor=&m->x60;cursor=BroadWrite(cursor,mx);cursor=BroadWrite(cursor,mx);cursor=BroadWrite(cursor,mx);}
    cnt = 0;
    for (g = o->xF0; g != 0; g = g->x0) {
        for (p = g->x4; p != 0; p = p->x0) {
            switch (p->x4) {
            case 3:
                cnt += p->x8;
                break;
            case 4:
                cnt += (p->x8 - 2) * 2 + 1;
                break;
            }
        }
    }
    m->x1C = (Edge *)MemStackNew_14e1b0(cnt << 4, heap);
    m->x18 = 0;
    out = m->x1C;
{
    Grp *g2;
    for (g2 = o->xF0; g2 != 0; g2 = g2->x0) {
        for (p2 = g2->x4; p2 != 0; p2 = p2->x0) {
            s = p2->x18->x4;
            n = p2->x8;
            switch (p2->x4) {
            case 3:
                for (k = 0; k < n; k += 3, s += 3) {
                    if (AddEdge(m, out, s[0], s[1])) {
                        m->x18++;
                        out++;
                    }
                    if (AddEdge(m, out, s[1], s[2])) {
                        m->x18++;
                        out++;
                    }
                    if (AddEdge(m, out, s[2], s[0])) {
                        m->x18++;
                        out++;
                    }
                }
                break;
            case 4:
                if (AddEdge(m, out, s[0], s[1])) {
                    m->x18++;
                    out++;
                }
                s += 2;
                for (k_w120 = 0; k_w120 < n - 2; k_w120++, s++) {
                    if (AddEdge(m, out, s[0], s[-1])) {
                        m->x18++;
                        out++;
                    }
                    if (AddEdge(m, out, s[0], s[-2])) {
                        m->x18++;
                        out++;
                    }
                }
                break;
            }
        }
    }
    }
    return 1;
}
