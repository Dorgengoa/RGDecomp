#include "types.h"

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    s32 m8;
    s32 id;
    s32 data;
} Node;

typedef struct {
    Node *head;
    Node *cur;
    s32 end;
} List;

extern void EffDefDestroyInstancesByTag_19ff40(void *, s32, s32);
extern void EffDefDestroy_1a0a90(void *, s32);
extern void MotionEventListReleaseHandlers_1b4910(void *);

static inline s32 *next(List *l, s32 *k)
{
    Node *c;
    Node *nx;
    Node *pv;
    s32 *e;

    c = l->cur;
    if (c == NULL) {
        e = NULL;
    } else {
        *k = c->id;
        e = &c->data;
        nx = c->next;
        l->cur = nx;
        if (nx == NULL) {
            l->end = 1;
        }
    }
    return e;
}

typedef struct {
    u8 pad0[0x538];
    s32 m538;
    void *m53C;
    u8 flag;
    u8 pad541[3];
    List *l544;
    List l548;
    u8 pad554[0x568 - 0x554];
    u8 pad568[4];
} A;

void ModelObjExEffectsStop_1b0880(A *a, s32 id, s32 all)
{
    s32 *e;
    s32 k;
    Node *n;
    Node *nx;
    Node *pv;
    List *l;

    MotionEventListReleaseHandlers_1b4910(a->pad568);
    if (a->flag == 0) {
        if (a->l548.cur == NULL) {
            a->l548.cur = a->l548.head;
            a->l548.end = 0;
        }
        while ((e = next(&a->l548, &k)) != NULL) {
            if (all != 0 || k == id) {
                if (a->m53C != NULL) {
                    EffDefDestroy_1a0a90(a->m53C, *e);
                }
            }
        }
        a->l548.cur = NULL;
        a->l548.end = 0;
        if (all != 0) {
            a->l548.head = NULL;
            a->l548.cur = NULL;
            a->l548.end = 0;
            return;
        }
        n = a->l548.head;
        while (n != NULL) {
            nx = n->next;
            if (id == n->id) {
                if (n->prev == NULL) {
                    a->l548.head = nx;
                    if (nx != NULL) {
                        nx->prev = NULL;
                    }
                } else {
                    pv = n->prev;
                    pv->next = nx;
                    if (nx != NULL) {
                        nx->prev = pv;
                    }
                }
                n->next = NULL;
                n->prev = NULL;
            }
            n = nx;
        }
    } else {
        l = a->l544;
        if (l == NULL) {
            return;
        }
        if (l->cur == NULL) {
            l->cur = l->head;
            l->end = 0;
        }
        while ((e = next(a->l544, &k)) != NULL) {
            if (all != 0 || k == id) {
                if (a->m53C != NULL) {
                    EffDefDestroyInstancesByTag_19ff40(a->m53C, *e, a->m538);
                }
            }
        }
        l = a->l544;
        l->cur = NULL;
        l->end = 0;
    }
}
