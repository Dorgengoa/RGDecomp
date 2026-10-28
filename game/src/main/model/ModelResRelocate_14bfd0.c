/* rgp:protos */
#define RGP_SELF_ModelResRelocate_14bfd0 1
#define RGP_SELF_cnt1 1
#define RGP_SELF_cnt2 1
#define RGP_SELF_get1 1
#define RGP_SELF_get2 1
#include "port/game_protos.h"
#line 1
#pragma opt_dead_assignments off
#include "types.h"

typedef struct E1 { s32 x0; s32 x4; s32 x8; s32 xC; } E1;
typedef struct E2 { u8 pad[0x30]; s32 x30; s32 x34; s32 x38; } E2;
typedef struct Q { s32 x0; s32 x4; s32 x8; s32 xC; } Q;
typedef struct B {
    s32 x0;
    u8 pad4[4];
    u8 n;
    u8 pad9[3];
    s32 xC;
    s32 x10;
} B;
typedef struct A {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
} A;
typedef struct Node {
    u8 pad0[0x60];
    s32 x60;
    u8 pad64[8];
    u16 h6C;
    u8 pad6E[6];
    s32 x74;
    u8 pad78[8];
    s32 x80;
} Node;
typedef struct Hdr {
    u8 b0;
    u8 pad1[0xB];
    s32 xC;
    u8 pad10[4];
    s32 x14;
    s32 x18;
    u8 pad1C[4];
    s32 x20;
    s32 x24;
    u8 pad28[4];
    s32 x2C;
    s32 x30;
    s32 x34;
    s32 x38;
    u8 pad3C[4];
    s32 x40;
} Hdr;
typedef struct Self {
    Hdr *h;
    s32 cnt;
} Self;

extern s32 memcmp(const void *, const void *, s32);
extern u8 D_00458AF8[];
extern u8 D_00458B00[];

static inline s32 cnt1(Self *s) { return s->h ? s->h->xC : 0; }
static inline s32 cnt2(Self *s) { return s->h ? s->h->x2C : 0; }
static inline E1 *get1(Self *s, s32 i)
{
    if (s->h == 0) return 0;
    if (i < 0 || i >= cnt1(s)) return 0;
    { s32 b = (*(Hdr **)s)->x18; return (E1 *)(b + (*(Hdr **)s)->x14 * i); }
}
static inline E2 *get2(Self *s, s32 i)
{
    if (s->h == 0) return 0;
    if (i < 0 || i >= cnt2(s)) return 0;
    { s32 b = (*(Hdr **)s)->x34; return (E2 *)(b + (*(Hdr **)s)->x30 * i); }
}
s32 ModelResRelocate_14bfd0(Self *self, u8 *base)
{
    s32 j;
    s32 n;
    s32 str;
    E1 *e;
    E2 *f;
    Node *node;
    A *a;
    B *b;
    Q *q;
    s32 i;

    self->h = (Hdr *)base;
    if (memcmp(base, D_00458AF8, 4) == 0) {
        return 1;
    }
    if (memcmp(self->h, D_00458B00, 4) != 0) {
        self->h = 0;
        return 0;
    }
    self->h->b0 = 0x40;
    self->h->x18 = (s32)(base + self->h->x18);
    self->h->x24 = (s32)(base + self->h->x24);
    self->h->x34 = (s32)(base + self->h->x34);
    self->h->x38 = (s32)(base + self->h->x38);
    str = self->h->x38;
    if (self->h->x40 != 0) {
        { s32 k = str; k += self->h->x40; self->h->x40 = k; }
    }
    n = cnt1(self);
    self->cnt = 0;
    for (i = 0; i < n; i++) {
        e = get1(self, i);
        if (e == 0) break;
        if (e->x0 != 0) { s32 k = str; k += e->x0; e->x0 = k; }
        if (e->x4 != 0) { s32 k = str; k += e->x4; e->x4 = k; }
        if (e->xC >= 0) self->cnt++;
    }
    n = cnt2(self);
    for (i = 0; i < n; i++) {
        f = get2(self, i);
        if (f == 0) break;
        if (f->x30 != 0) { s32 k = str; k += f->x30; f->x30 = k; }
        if (f->x34 != 0) { s32 k = str; k += f->x34; f->x34 = k; }
        if (f->x38 != 0) { s32 k = str; k += f->x38; f->x38 = k; }
    }
    node = (Node *)self->h->x24;
    if (self->h->x20 == 0) node = 0;
    while (node != 0) {
        if (node->x60 != 0) node->x60 = (s32)((u8 *)node + node->x60);
        if (node->h6C == 0) {
            if (node->x74 != 0) node->x74 = (s32)((u8 *)node + node->x74);
            a = (A *)node->x60;
            if (a != 0) {
                if (a->x4 != 0) a->x4 = (s32)((u8 *)a + a->x4);
                if (a->xC != 0) a->xC = (s32)((u8 *)a + a->xC);
                if (a->x14 != 0) a->x14 = (s32)((u8 *)a + a->x14);
                if (a->x1C != 0) a->x1C = (s32)((u8 *)a + a->x1C);
                if (a->x24 != 0) a->x24 = (s32)((u8 *)a + a->x24);
                if (a->x28 != 0) a->x28 = (s32)((u8 *)a + a->x28);
            }
            b = (B *)node->x74;
            while (b != 0) {
                if (b->xC != 0) b->xC = (s32)((u8 *)b + b->xC);
                if (b->x10 != 0) b->x10 = (s32)((u8 *)b + b->x10);
                q = (Q *)b->xC;
                for (j = 0; j < b->n; j++, q++) {
                    if (q->x4 != 0) q->x4 = (s32)((u8 *)b + q->x4);
                    if (q->x8 != 0) q->x8 = (s32)((u8 *)b + q->x8);
                    if (q->xC != 0) q->xC = (s32)((u8 *)b + q->xC);
                }
                if (b->x0 != 0) b->x0 = (s32)((u8 *)b + b->x0);
                b = (B *)b->x0;
            }
        } else if (node->h6C == 1) {
            node->x74 = 0;
            a = (A *)node->x60;
            if (a != 0) {
                if (a->xC != 0) a->xC = (s32)((u8 *)a + a->xC);
                if (a->x10 != 0) a->x10 = (s32)((u8 *)a + a->x10);
                if (a->x14 != 0) a->x14 = (s32)((u8 *)a + a->x14);
                if (a->x18 != 0) a->x18 = (s32)((u8 *)a + a->x18);
            }
        }
        if (node->x80 != 0) node->x80 = (s32)((u8 *)node + node->x80);
        node = (Node *)node->x80;
    }
    return 1;
}
