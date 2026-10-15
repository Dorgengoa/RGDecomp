#include "types.h"

class Node {
public:
    Node *next;
    Node *prev;
    s32 x8;
    s32 xC;
    s32 x10;
    virtual void init();
};

typedef struct {
    u8 pad0[0x53C];
    s32 unk53C;
    u8 unk540;
    u8 pad541[0x7];
    Node *unk548;
    s32 unk54C;
    s32 unk550;
} T;

extern "C" {
extern void *MemStackNew_14e230(s32, s32);
extern void EffDefLoad_19fc30(s32 *, s32, s32, u8 *);
}

extern "C" void *D_00471010[];

extern "C" s32 ModelObjExAddEffDef_1afd40(T *arg0, s32 arg1, u8 *arg2) {
    s32 sp7C;
    Node *p;
    Node *q;
    s32 *r;
    s32 heap;
    s32 v;

    if (arg0->unk53C == 0) {
        return 0;
    }
    heap = *(s32 *)(arg2 + 0x1C);
    if (heap == 0) {
        return 0;
    }
    if (arg0->unk540 != 0) {
        return 0;
    }
    v = *(s32 *)(arg2 + 0x18);
    p = (Node *)MemStackNew_14e230(0x18, heap);
    if (p != NULL) {
        *(void **)((u8 *)p + 0x14) = D_00471010;
        p->x10 = 0;
        p->init();
    }
    if (p == NULL) {
        r = 0;
    } else {
        p->xC = v;
        p->x8 = heap;
        arg0->unk54C = 0;
        arg0->unk550 = 0;
        q = arg0->unk548;
        if (q != NULL) {
            while (q != NULL) {
                if (q->next == NULL) {
                    break;
                }
                q = q->next;
            }
            q->next = p;
            if (p != NULL) {
                p->prev = q;
            }
        } else {
            arg0->unk548 = p;
        }
        r = &p->x10;
    }
    if (r == 0) {
        return 0;
    }
    EffDefLoad_19fc30(&sp7C, arg0->unk53C, arg1, arg2);
    *r = sp7C;
    return 1;
}
