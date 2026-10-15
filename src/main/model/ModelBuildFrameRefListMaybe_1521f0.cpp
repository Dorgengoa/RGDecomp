#include "types.h"

typedef struct Sub {
    s32 m0;
    s32 m4;
    s32 m8;
    s32 mC;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
} Sub;

struct Node {
    Node *next;
    Node *prev;
    u8 pad8[8];
    Sub sub;
    virtual void init();
};


typedef struct {
    u8 pad0[0x44];
    Node *head;
} Obj;

typedef struct {
    u8 pad0[0xC];
    s32 mC;
} Ent;

typedef void (*VFn)(Node *);

extern "C" {
Node *MemStackNew_14e230(s32, s32);
Ent *ArrayGetChecked_14c7f0(s32, s32);
s32 ModelResGetFrameCount_14c850(s32);
Node *MemStackNew_14e230(s32, s32);
extern void *D_0046FFD0[];
}

extern "C" s32 ModelBuildFrameRefListMaybe_1521f0(Obj *arg0, s32 arg1, s32 arg2)
{
    s32 i;
    s32 n;
    Ent *e;
    Node *p;
    Node *v;
    Sub *q;

    if (arg1 == 0) {
        return 0;
    }
    n = ModelResGetFrameCount_14c850(arg1);
    for (i = 0; i < n; i++) {
        e = ArrayGetChecked_14c7f0(arg1, i);
        if (e == 0) {
            continue;
        }
        if (e->mC < 0) {
            continue;
        }
        p = MemStackNew_14e230(0x34, arg2);
        if (p != 0) {
            *(void ***)((u8 *)p + 0x30) = D_0046FFD0;
            p->init();
        }
        if (p == 0) {
            q = 0;
        } else {
            v = arg0->head;
            if (v != 0) {
                while (v != 0) {
                    if (v->next == 0) {
                        break;
                    }
                    v = v->next;
                }
                v->next = p;
                if (p != 0) {
                    p->prev = v;
                }
            } else {
                arg0->head = p;
            }
            q = &p->sub;
            if (q != 0) {
                q->m0 = 0;
                q->m8 = -1;
                q->m4 = -1;
                q->mC = 0;
                q->m10 = 0;
                q->m14 = 0;
                q->m18 = 0;
                q->m1C = 0;
            }
        }

        if (q == 0) {
            break;
        }
        q->m4 = i;
        q->m8 = e->mC;
    }
    return 1;
}
