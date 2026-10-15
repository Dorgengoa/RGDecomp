#include "types.h"

typedef struct Sub {
    s16 h0;         /* 0x00 */
    u8 pad2[8];
    s8 bA;          /* 0x0A */
    u8 padB;
    u32 c;          /* 0x0C */
} Sub;

typedef struct Elem {
    u16 id;         /* 0x00 */
    u8 pad2[0x12];
    f32 f14;        /* 0x14 */
    f32 f18;        /* 0x18 */
    s16 h1C;        /* 0x1C */
    u8 pad1E[0xA];
    Sub *sub;       /* 0x28 */
    u8 pad2C[0x14];
    f32 f40[4];     /* 0x40 */
    s32 m50[4];     /* 0x50 */
    f32 f60;        /* 0x60 */
    f32 f64;        /* 0x64 */
    u8 pad68[0x18];
    s16 h80;        /* 0x80 */
    u8 pad82[2];
    s32 m84;        /* 0x84 */
    s32 m88;        /* 0x88 */
    s32 m8C;        /* 0x8C */
    s32 m90;        /* 0x90 */
} Elem;

typedef struct Link {
    Elem *e;            /* 0x00 */
    struct Link *c;     /* 0x04 */
    struct Link *next;  /* 0x08 */
} Link;

typedef struct Mgr {
    Link *head;     /* 0x00 */
    u8 pad4[8];
    s16 n;          /* 0x0C */
} Mgr;

extern void UiLinkWidgetTree_290150(Mgr *);
extern Link *UiWidgetPoolFindFree_291300(Mgr *, Link *);
extern Link *UiWidgetListFindTail_291360(Mgr *, Link *);

static inline void fix(Sub *p)
{
    if (p == 0) {
        return;
    }
    while (p->h0 >= 0) {
        if (p->bA != 2 && p->bA != 1) {
            p->bA = 2;
        }
        if (p->c == 0) {
            p->c = 0xFF606060;
        }
        p++;
    }
}

void UiAddWidgets_2901d0(Mgr *m, Elem *e, s32 flag)
{
    Link *prev;
    Link *c;
    s32 k;
    Link *t;
    Sub *p;
    s32 i;
    Link *q;
    Elem *r;

    prev = UiWidgetPoolFindFree_291300(m, 0);
    c = UiWidgetListFindTail_291360(m, 0);
    k = 0;
    while (e->id > 0) {
        c = UiWidgetListFindTail_291360(m, c);
        t = UiWidgetPoolFindFree_291300(m, prev);
        t->e = e;
        prev = t;
        t->c = c;
        t->next = 0;
        if (c != 0) {
            c->next = prev;
        }
        e->m84 = 0;
        e->m88 = 0;
        e->m8C = 0;
        e->m90 = 0;
        if (flag != 0) {
            e->id += (u16)k;
        }
        p = e->sub;
        k++;
        if (p != 0) {
            fix(p);
        }
        e->f60 = e->f14;
        e->f64 = e->f18;
        i = 0;
        do {
            e->f40[i] = -1.0f;
            e->m50[i] = 0;
            i++;
        } while (i < 4);
        e->h80 = 0;
        e->h1C |= 1;
        e++;
        m->n++;
    }
    q = m->head;
    while (q != 0) {
        r = q->e;
        if (r == 0) {
            break;
        }
        r->m84 = 0;
        r->m88 = 0;
        r->m8C = 0;
        r->m90 = 0;
        q = q->next;
    }
    UiLinkWidgetTree_290150(m);
}
