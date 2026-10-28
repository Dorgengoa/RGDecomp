#pragma opt_common_subs off
#pragma always_inline on
#include "types.h"

struct Entry { s8 name[0x30]; };
struct Tbl { s32 x0; s32 count; Entry *data; };
struct Node { Node *next; s32 x4; s32 x8; s8 *key; Tbl tbl; };
struct Obj { Node *cur; s32 idx; s32 arg; s32 pad[14]; s32 x44; Node *head; };

static inline bool StrEq(const s8 *a, const s8 *b)
{
    s8 c;
    if (*a != *b) return 0;
    while ((c = *a) != 0 || *b != 0) {
        if (c != *b) return 0;
        a++;
        b++;
    }
    return 1;
}

static inline s32 Find(Tbl *t, const s8 *name)
{
    s32 i;
    if (name == 0) return -1;
    if (t->data == 0) return 0;
    for (i = 0; i < t->count; i++) {
        if (StrEq(t->data[i].name, name)) return i;
    }
    return -1;
}

static inline Node *FindNode(Node *head, s8 *key)
{
    Node *q;
    for (q = head; q != 0; q = q->next) {
        if (key == q->key) return q;
    }
    return 0;
}

static inline int Valid(Tbl *t, s32 i)
{
    if (t->data == 0) return 0;
    if (i < 0 || i >= t->count) return 0;
    return 1;
}

extern "C" void MotionPlayerSelectByName_173640(Obj *self, s8 *name, s32 arg2)
{
    Node *q;
    s32 idx;
    Node *p;
    Node *head;

    head = self->head;
    for (p = head; p != 0; p = p->next) {
        Tbl *t = &p->tbl;
        if (t != 0) {
            idx = Find(t, name);
            if (idx >= 0) {
                name = p->key;
                goto found;
            }
        }
    }
    idx = -1;
found:
    if (idx < 0) return;
    q = FindNode(head, name);
    if (q == 0) return;
    {
    Tbl *tt = &q->tbl;
    if (Valid(tt, idx)) {
        self->cur = q;
        self->idx = idx;
        self->arg = arg2;
        self->x44 = 0;
    }
    }
}
