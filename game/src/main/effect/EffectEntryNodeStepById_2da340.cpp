#pragma opt_propagation off
#include "types.h"

class Obj {
public:
    s16 type;
    s16 pad2;
    s32 unk4;
    s32 key;
    u8 padC[0x190 - 0xC];
    VC_VPTR_MEMBER;
    void v1() { VCM0(void, 0xC); }
};

struct Node {
    Node *next;
    u8 pad4[0xC];
    Obj *data;
};

struct List {
    Node *head;
    Node *cur;
    s32 end;
};

extern "C" void EffectNodeStepScript_2dad50(List *, Obj *);

static inline Obj **next(List *l)
{
    Obj **r;
    Node *n = l->cur;
    Node *nx;
    if (n == 0) {
        r = 0;
    } else {
        r = &n->data;
        nx = n->next;
        l->cur = nx;
        if (nx == 0) {
            l->end = 1;
        }
    }
    return r;
}

extern "C" void EffectEntryNodeStepById_2da340(List *arg0, u8 *arg1)
{
    Obj **e;
    Obj *x;
    s32 t;
    s32 k;

    if (arg0->cur == 0) {
        arg0->cur = arg0->head;
        arg0->end = 0;
    }
    for (;;) {
        e = next(arg0);
        if (e == 0) {
            break;
        }
        x = *e;
        if(x != 0) {
        t=x->key; k=*(s32*)(arg1+0x10);
        if(k==t) {
            if (x->type == 1) {
                goto call;
            }
            if (x->type != 2) {
                goto skip;
            }
        call:
            EffectNodeStepScript_2dad50(arg0, x);
        skip:
            (*e)->v1();
            break;
        }
    }
    }
    arg0->cur = 0;
    arg0->end = 0;
}
