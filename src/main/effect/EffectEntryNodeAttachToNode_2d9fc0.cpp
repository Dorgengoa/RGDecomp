#include "types.h"
#pragma opt_propagation off

struct Item {
    u8 pad0[4];
    s32 m4;
    u8 pad8[0x20];
    s8 m28;
};

class ObjB {
public:
    u8 pad0[8];
    s32 m8;
    u8 padc[0x190 - 0xc];
};

class Obj : public ObjB {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void *v4();
};

struct Node {
    Node *next;
    u8 pad4[0xc];
    Obj *data;
};

struct List {
    Node *head;
    Node *cur;
    s32 end;
    void Begin() {
        if (cur == 0) {
            cur = head;
            end = 0;
        }
    }
    Obj **Next() {
        Obj **p;
        if (cur == 0) {
            return 0;
        }
        p = &cur->data;
        cur = cur->next;
        if (cur == 0) {
            end = 1;
        }
        return p;
    }
    void Stop() {
        cur = 0;
        end = 0;
    }
};

struct Key {
    u8 pad0[0x10];
    s32 m10;
};

extern "C" Item *ModelGetRootFrame_1511a0(void *);
extern "C" void FrameSetDirty_14a5e0(Item *);

extern "C" void EffectEntryNodeAttachToNode_2d9fc0(List *l, Key *k, s32 v)
{
    Obj **pp;
    Obj *o;
    void *h;
    Item *it;
    s32 id;

    l->Begin();
    for (;;) {
        pp = l->Next();
        if (pp == 0) break;
        o = *pp;
        if (o == 0) continue;
        id = o->m8;
        if (k->m10 != id) continue;
        h = o->v4();
        if (h != 0) {
            if (v != 0) {
                it = ModelGetRootFrame_1511a0(h);
                it->m28 = 1;
                it->m4 = v;
                FrameSetDirty_14a5e0(it);
            } else {
                it = ModelGetRootFrame_1511a0(h);
                if (it->m28 != 0) {
                    it->m4 = 0;
                }
            }
        }
        break;
    }
    l->Stop();
}
