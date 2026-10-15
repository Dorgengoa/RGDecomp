#include "types.h"

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    s32 x8;
    s32 xC;
} Node;

typedef struct {
    u8 pad0[0xC];
    Node *xC;
    Node *x10;
    u8 pad14[0x28 - 0x14];
    s32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
    u8 pad38[0x48 - 0x38];
    Node *x48;
} Obj;

extern void MotionPlayerReset_173870(Obj *);
s32 FUN_00172700_e1(Obj *arg0, s32 key);
static inline Node *Head(Node *q) { while (q->prev != NULL) { q = q->prev; } return q; }

s32 MotionPlayerRemoveById_172700(Obj *arg0, s32 arg1)
{
    Node *p;
    s32 k;

    for (p = arg0->x48; p != NULL; p = p->next) {
        if (arg1 == p->xC) {
            k = p->x8;
            goto found;
        }
    }
    k = 0;
found:
    return FUN_00172700_e1(arg0, k);
}

s32 FUN_00172700_e1(Obj *arg0, s32 key)
{
    Node *p;
    Node *prev;
    Node *q;
    s32 cnt;
    Node *next;

    p = arg0->x48;
    cnt = 0;
    while (p != NULL) {
        next = p->next;
        if (key == p->x8) {
            if (p == arg0->xC) {
                MotionPlayerReset_173870(arg0);
            }
            if (p == arg0->x10) {
                arg0->x10 = NULL;
                arg0->x28 = 0;
                arg0->x2C = -1;
                arg0->x30 = 0;
                arg0->x34 = 0;
            }
            if (arg0->x48 != NULL) {
                prev = p->prev;
                if (prev != NULL) {
                    q = p->next;
                    prev->next = q;
                    if (q != NULL) {
                        q->prev = prev;
                    }
                    q = Head(p->prev);
                } else {
                    q = p->next;
                    if (q != NULL) {
                        q->prev = NULL;
                    }
                    q = p->next;
                }
                p->prev = NULL;
                p->next = NULL;
                arg0->x48 = q;
            }
            cnt++;
        }
        p = next;
    }
    return cnt;
}
