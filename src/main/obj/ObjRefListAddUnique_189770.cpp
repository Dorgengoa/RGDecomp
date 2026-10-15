#include "types.h"

class Node00189770 {
public:
    Node00189770 *next; /* 0x0 */
    Node00189770 *prev; /* 0x4 */
    u8 pad8[0x10 - 0x8];
    s32 key; /* 0x10 */
    virtual void init(); /* vptr 0x14, slot +8 */
};

typedef struct Self00189770 {
    u8 pad0[0x2A4];
    Node00189770 *list; /* 0x2A4 */
} Self00189770;

extern "C" {
extern u8 D_00470528[];
extern void *MemStackNew_14e230(s32 size, void *heap);
Node00189770 *ObjRefListAddUnique_189770(Self00189770 *self, s32 key, void *heap);
}

static inline Node00189770 *find(Self00189770 *self, s32 key)
{
    Node00189770 *c;

    for (c = self->list; c != 0; c = c->next) {
        if (c->key == key) {
            return c;
        }
    }
    return 0;
}

Node00189770 *ObjRefListAddUnique_189770(Self00189770 *self, s32 key, void *heap)
{
    Node00189770 *n;
    Node00189770 *t;

    if (find(self, key) != 0) {
        return 0;
    }
    n = (Node00189770 *)MemStackNew_14e230(0x18, heap);
    if (n != 0) {
        *(void **)((u8 *)n + 0x14) = D_00470528;
        n->init();
    }
    if (n == 0) {
        return 0;
    }
    n->key = key;
    if (self->list == 0) {
        self->list = n;
    } else {
        t = self->list;
        while (t != 0) {
            if (t->next == 0) {
                break;
            }
            t = t->next;
        }
        t->next = n;
        if (n != 0) {
            n->prev = t;
        }
    }
    return n;
}
