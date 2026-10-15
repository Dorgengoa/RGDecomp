#include "types.h"

struct N1A9CE0 {
    N1A9CE0 *next;
    void *data;
};

class V1A9CE0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual s32 count();
};

struct O1A9CE0 {
    u8 pad0[0x4];
    N1A9CE0 *unk4;
    u8 pad8[0x4];
    N1A9CE0 *unkC;
    N1A9CE0 *unk10;
};

extern "C" void *MemStackNew_14e230(s32 arg0, s32 arg1);

static inline N1A9CE0 *NewNode(s32 heap)
{
    N1A9CE0 *n = (N1A9CE0 *)MemStackNew_14e230(8, heap);
    if (n != 0) {
        n->next = 0;
    }
    return n;
}

static inline void Append(N1A9CE0 **head, N1A9CE0 *n)
{
    N1A9CE0 *p = *head;
    N1A9CE0 *t;

    if (p == 0) {
        *head = n;
        return;
    }
    while (p != 0) {
        if (p->next == 0) {
            break;
        }
        p = p->next;
    }
    p->next = n;
}

extern "C" void EffObjAddChannel_1a9ce0(O1A9CE0 *arg0, s32 arg1, V1A9CE0 *arg2)
{
    N1A9CE0 *n;
    s32 c;

    if (arg2 == 0) {
        return;
    }
    n = NewNode(arg1);
    if (n == 0) {
        return;
    }
    n->data = arg2;
    Append(&arg0->unk4, n);
    c = arg2->count();
    if (c <= 0) {
        return;
    }
    n = NewNode(arg1);
    if (n == 0) {
        return;
    }
    n->data = arg2;
    if (c == 1) {
        Append(&arg0->unkC, n);
    } else {
        Append(&arg0->unk10, n);
    }
}
