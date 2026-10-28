#include "types.h"

class Node00189890 {
public:
    Node00189890 *next; /* 0x0 */
    Node00189890 *prev; /* 0x4 */
    u8 pad8[0x10 - 0x8];
    s32 key; /* 0x10 */
    VC_VPTR_MEMBER; void init() { VCM0(void, 0x8); } /* vptr 0x14, slot +8 */
};

typedef struct Self00189890 {
    u8 pad0[0x2A0];
    Node00189890 *list; /* 0x2A0 */
} Self00189890;

extern "C" {
extern u8 D_00470518[];
extern void *MemStackNew_14e230(s32 size, void *heap);
Node00189890 *ObjRefListAddUnique_189890(Self00189890 *self, s32 key, void *heap);
}

static inline Node00189890 *find(Self00189890 *self, s32 key)
{
    Node00189890 *c;

    for (c = self->list; c != 0; c = c->next) {
        if (c->key == key) {
            return c;
        }
    }
    return 0;
}

Node00189890 *ObjRefListAddUnique_189890(Self00189890 *self, s32 key, void *heap)
{
    Node00189890 *n;
    Node00189890 *t;

    if (find(self, key) != 0) {
        return 0;
    }
    n = (Node00189890 *)MemStackNew_14e230(0x18, heap);
    if (n != 0) {
        *(void **)((u8 *)n + 0x14) = D_00470518;
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
