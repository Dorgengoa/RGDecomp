#include "types.h"

typedef unsigned __int128 u128;

struct NodeBase {
    NodeBase *next;
    NodeBase *prev;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
};

class Node : public NodeBase {
public:
    virtual void v8();
};

struct Data {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
};

struct Heap {
    u8 pad0[0x2C];
    s32 x2C;
};

struct Obj {
    u8 pad0[0x204];
    s32 n204;
    u8 *p208;
    u8 pad20C[8];
    s32 n214;
    u8 *p218;
    u8 *p21C;
    NodeBase *x220;
    s32 x224;
    u8 pad228[0x48];
    u8 x270[0x1C0];
    s32 x430;
    s32 x434;
    s32 x438;
    s32 x43C;
    s32 x440;
    u8 pad444[4];
    f32 x448;
    u8 pad44C[0xC];
    f32 x458;
    s32 x45C;
    s32 x460;
    s32 x464;
    u8 x468;
    u8 pad469[3];
    s32 x46C[2];
    s32 x474;
    u8 pad478[8];
    u128 x480;
    u128 x490;
    u128 x4A0;
    char x4B0[0x10];
    s32 x4C0;
    s32 x4C4;
    f32 x4C8;
    f32 x4CC;
    f32 x4D0;
    s32 x4D4;
    s32 x4D8;
    s32 x4DC;
};

extern "C" {
u8 *ConstructNewArray_100710(void *, void *, void *, s32, s32);
void *MemStackNew_14e1b0(s32, Heap *);
void *MemStackNew_14e230(s32, Heap *);
s32 ModelGetRootFrame_1511a0(Obj *);
void ModelCopy_151c40(u8 *, u8 *, Heap *);
void ModelPartCopy_152070(u8 *, u8 *, Heap *);
void TexAnimeTableCopy_162810(s32, s32, Heap *);
s32 TexAnimeTableCtor_162ed0(void *);
void DynClothCopy_168e90(u8 *, u8 *, s32, Heap *);
void ModelObjBaseCopy_186820(Obj *, Obj *, Heap *);
void ObjCopyAttachPoints_1ac8a0(Obj *, Obj *, Heap *);
void ModelObjCopyOutlineList_1aca70(Obj *, Obj *, Heap *);
void DynClothDefCtor_1aaa60(void);
char *strcpy(char *, const char *);
}
extern u8 D_00470F40[];

static inline u8 *at(u8 *p, s32 n, s32 i) {
    if (p == 0 || n == 0) return 0;
    if (i < 0 || i >= n) return 0;
    return p + i * 0x170;
}

static inline Node *newNode(Heap *h) {
    Node *v = (Node *)MemStackNew_14e230(0x28, h);
    if (v != 0) {
        *(void **)((u8 *)v + 0x24) = D_00470F40;
        v->x10 = 0;
        v->x14 = 0;
        v->x1C = 0;
        v->x20 = 0;
        v->x18 = 1;
        v->v8();
    }
    return v;
}
static inline s32 newO(Heap *h) {
    s32 o = (s32)MemStackNew_14e230(0x3C4, h);
    if (o != 0) o = TexAnimeTableCtor_162ed0((void *)o);
    return o;
}
static inline u8 *at2(Obj *o, s32 i) {
    if (o->p208 == 0 || o->n204 == 0) return 0;
    if (i < 0 || i >= o->n204) return 0;
    return o->p208 + i * 0x170;
}
extern "C" void ModelObjCopy_1acc00(Obj *a, Obj *b, Heap *h) {
    s32 base;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    NodeBase *p;
    s32 id;
    Node *v;
    Data *d;
    NodeBase *e;
    Data *sd;
    s32 o;
    u8 *dst;
    u8 *src;

    base = 0;
    if (h != 0) base = h->x2C;
    ModelObjBaseCopy_186820(a, b, h);
    ModelObjCopyOutlineList_1aca70(a, b, h);
    ObjCopyAttachPoints_1ac8a0(a, b, h);
    if (h != 0) {
        n = a->n214;
        if (n > 0 && a->p218 != 0 && a->p21C != 0) {
            b->p218 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x50 + 0x10, h), 0, 0, 0x50, n);
            n = a->n214;
            b->p21C = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x50 + 0x10, h), 0, 0, 0x50, n);
            if (b->p218 != 0) {
                for (i = 0; i < a->n214; i++) {
                    ModelPartCopy_152070(a->p218 + i * 0x50, b->p218 + i * 0x50, h);
                    ModelPartCopy_152070(a->p21C + i * 0x50, b->p21C + i * 0x50, h);
                }
                b->n214 = a->n214;
            }
        } else {
            b->n214 = 0;
            b->p218 = 0;
            b->p21C = 0;
        }
    } else {
        b->n214 = a->n214;
        b->p218 = a->p218;
        b->p21C = a->p21C;
    }
    b->x45C = a->x45C;
    ModelCopy_151c40(a->x270, b->x270, h);
    b->x430 = a->x430;
    b->x434 = a->x434;
    b->x438 = a->x438;
    b->x43C = a->x43C;
    b->x440 = a->x440;
    for (k = 0; k < 2; k++) b->x46C[k] = a->x46C[k];
    b->x474 = a->x474;
    b->x480 = a->x480;
    b->x490 = a->x490;
    b->x4A0 = a->x4A0;
    strcpy(b->x4B0, a->x4B0);
    b->x448 = a->x448;
    b->x4C0 = a->x4C0;
    b->x4C4 = a->x4C4;
    b->x4C8 = a->x4C8;
    b->x4CC = a->x4CC;
    b->x4D0 = a->x4D0;
    b->x4D4 = a->x4D4;
    b->x4D8 = a->x4D8;
    if (h != 0) {
        b->x220 = 0;
        for (p = a->x220; p != 0; p = p->next) {
            id = p->xC;
            v = newNode(h);
            if (v == 0) {
                d = 0;
            } else {
                v->x10 = 0;
                v->x14 = 0;
                v->x1C = 0;
                v->x20 = 0;
                v->x18 = 1;
                v->xC = id;
                d = (Data *)&v->x10;
                if (b->x220 == 0) {
                    b->x220 = v;
                } else {
                    e = b->x220;
                    while (e != 0) {
                        if (e->next == 0) break;
                        e = e->next;
                    }
                    e->next = v;
                    if (v != 0) v->prev = e;
                }
            }
            if (d == 0) break;
            d->x0 = 0;
            d->x4 = 0;
            d->xC = 0;
            d->x10 = 0;
            d->x8 = 1;
            sd = (Data *)&p->x10;
            o = newO(h);
            d->x4 = o;
            if (sd->x4 != 0 && d->x4 != 0) TexAnimeTableCopy_162810(sd->x4, d->x4, h);
            d->x8 = sd->x8;
        }
    } else {
        b->x220 = a->x220;
    }
    b->x4DC = a->x4DC;
    b->x224 = a->x224;
    if (h != 0) {
        if (a->p208 != 0 && (n = a->n204) > 0) {
            {
                if (n != 0) {
                    b->p208 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x170 + 0x10, h), (void *)DynClothDefCtor_1aaa60, 0, 0x170, n);
                    if (b->p208 == 0) {
                        b->n204 = 0;
                    } else {
                        b->n204 = n;
                    }
                }
                for (j = 0; j < a->n204; j++) {
                    dst = at2(b, j);
                    src = at(a->p208, a->n204, j);
                    if (dst != 0 && src != 0) DynClothCopy_168e90(src, dst, ModelGetRootFrame_1511a0(b), h);
                }
            }
        } else {
            b->p208 = 0;
            b->n204 = 0;
        }
    } else {
        b->p208 = a->p208;
        b->n204 = a->n204;
    }
    if (h != 0) a->x4D8 = h->x2C - base;
    b->x460 = a->x460;
    b->x464 = a->x464;
    b->x468 = a->x468;
    b->x458 = a->x458;
}
