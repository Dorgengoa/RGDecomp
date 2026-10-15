#include "types.h"

typedef unsigned __int128 u128;

struct V4f {
    f32 x, y, z, w;
};

struct Inner {
    u128 a;
    u128 b;
    s32 c;
    f32 d;
    s32 e;
    s32 : 32;
    V4f f;
    V4f g;
    s32 h0;
    s32 h1;
    s32 h2;
    s32 h3;
    s32 h4;
    s32 h5;
};

class Node {
public:
    Node *next;
    Node *prev;
    u8 pad8[8];
    Inner in;
    virtual void v08();
};

typedef struct {
    u8 pad0[0x200];
    Node *head;
} Obj001ACA70;

extern "C" {
Node *MemStackNew_14e230(s32, s32);
void OutlineParamsInit_16b8b0(Inner *);
extern u8 D_00470F30[0x400];
}

extern "C" void ModelObjCopyOutlineList_1aca70(Obj001ACA70 *arg0, Obj001ACA70 *arg1, s32 arg2)
{
    Node *src;
    Node *n;
    Node *p;
    Node *t;
    Inner *si;

    if (arg2 == 0) {
        arg1->head = arg0->head;
        return;
    }
    arg1->head = 0;
    src = arg0->head;
    while (src != 0) {
        si = &src->in;
        n = MemStackNew_14e230(0x90, arg2);
        if (n != 0) {
            *(void **)((u8 *)n + 0x80) = D_00470F30;
            OutlineParamsInit_16b8b0(&n->in);
            n->v08();
        }
        if (n == 0) {
            return;
        }
        n->in = *si;
        if (arg1->head == 0) {
            arg1->head = n;
        } else {
            p = arg1->head;
            while (p != 0) {
                if (p->next == 0) {
                    break;
                }
                p = p->next;
            }
            p->next = n;
            if (n != 0) {
                n->prev = p;
            }
        }
        src = src->next;
    }
}
