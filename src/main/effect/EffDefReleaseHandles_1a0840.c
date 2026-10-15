#include "types.h"

typedef struct Node {
    struct Node *next;
    s32 data;
} Node;

typedef struct {
    Node *head;
    Node *cur;
} List;

typedef struct {
    u8 pad0[0x48];
    s32 w48;
    u8 pad4C[0x14];
    List l60;
    List l68;
    List l70;
} B;

typedef struct {
    u8 pad0[4];
    s32 id;
} Obj;

typedef struct {
    u8 pad0[8];
    s32 w8;
    u8 padC[8];
    u8 m14[0x34];
    u8 m48[0x34];
    u8 m7C[0x94];
    s32 n;
    s32 base;
    s32 *arr;
} A;

extern void MemStackHeapFree_14dcb0(s32, s32);
extern void EffHdlRemove_1a3360(void *, s32);
extern Obj **HandleTableGet_1a3580(void *, s32);
extern void EffHdlRemove_1a36e0(void *, s32);
extern void EffHdlRemove_1a3c80(void *, s32);
extern void EffTexResUnbind_1a8540(Obj *);

static inline void ListBegin(List *l)
{
    if (l->cur == NULL) {
        l->cur = l->head;
    }
}

static inline s32 *ListNext(List *l)
{
    Node *n = l->cur;
    s32 *p;
    if (n == NULL) {
        p = NULL;
    } else {
        p = &n->data;
        l->cur = n->next;
    }
    return p;
}

static inline void ListEnd(List *l)
{
    l->cur = NULL;
}

static inline s32 Index(A *a, s32 id)
{
    s32 i = id - a->base;
    if (i < 0 || i >= a->n) {
        i = -1;
    }
    return i;
}

void EffDefReleaseHandles_1a0840(A *arg0, B *arg1)
{
    s32 ctx;
    s32 *p;
    Obj **e;
    Obj *o;
    s32 i;

    if (arg1 == NULL) {
        return;
    }
    ctx = arg0->w8;
    ctx = (s32)(u32)ctx;
    ListBegin(&arg1->l60);
    while ((p = ListNext(&arg1->l60)) != NULL) {
        EffHdlRemove_1a3360(arg0->m14, *p);
    }
    ListEnd(&arg1->l60);
    ListBegin(&arg1->l70);
    while ((p = ListNext(&arg1->l70)) != NULL) {
        EffHdlRemove_1a3c80(arg0->m7C, *p);
    }
    ListEnd(&arg1->l70);
    ListBegin(&arg1->l68);
    while ((p = ListNext(&arg1->l68)) != NULL) {
        e = HandleTableGet_1a3580(arg0->m48, *p);
        if (e != NULL) {
            o = *e;
        } else {
            o = NULL;
        }
        if (o != NULL) {
            i = Index(arg0, o->id);
            if (i >= 0) {
                arg0->arr[i] = 0;
            }
            EffTexResUnbind_1a8540(o);
        }
        EffHdlRemove_1a36e0(arg0->m48, *p);
    }
    ListEnd(&arg1->l68);
    MemStackHeapFree_14dcb0(ctx, arg1->w48);
}
