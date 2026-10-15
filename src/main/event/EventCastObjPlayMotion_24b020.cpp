#include "types.h"
#undef NULL
#define NULL 0

struct Node {
    Node *next;
    s32 m4;
    s32 m8;
    s32 key;
    u8 data[1];
};

struct Rec {
    u8 pad0[8];
    s32 type;
    u8 padC[0x10];
    s32 m1C;
};

struct List {
    Node *head;
    Node *cur;
    s32 done;

    s32 begin() {
        if (cur != NULL) {
            return -1;
        }
        cur = head;
        done = 0;
        return 0;
    }
    Rec *next(s32 *key) {
        Node *n = cur;
        Rec *p;
        if (n == NULL) {
            return NULL;
        }
        *key = n->key;
        p = (Rec *)n->data;
        cur = n->next;
        if (cur == NULL) {
            done = 1;
        }
        return p;
    }
    void end() {
        cur = NULL;
        done = 0;
    }
};

extern "C" {
void MotionListResetAll_171e00(s32 arg0);
void ModelObjPlayMotionByName_1867a0(s32 arg0, s32 arg1, s32 arg2);
void ObjRecSetFlag2_1c3e80(s32 arg0, s32 arg1, s32 arg2);
s32 ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
s32 GetCurrentScene_1f5be0(void);
}

extern "C" void EventCastObjPlayMotion_24b020(List *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 ctx;
    Rec *p;
    s32 key;
    s32 obj;

    ctx = GetCurrentScene_1f5be0();
    if (arg0->begin() != 0) {
        p = NULL;
    } else {
        while ((p = arg0->next(&key)) != NULL) {
            if (arg1 == key) {
                break;
            }
        }
        arg0->end();
    }
    if (p == NULL) {
        return;
    }
    switch (p->type) {
    case 1:
    case 2:
    case 3:
    case 6:
    case 7:
        obj = ObjRecGetLiveObject_1c4a90(ctx, p->m1C);
        if (obj != 0) {
            MotionListResetAll_171e00(obj + 0x1F0);
            ModelObjPlayMotionByName_1867a0(obj, arg2, arg3);
            ObjRecSetFlag2_1c3e80(ctx, 1, p->m1C);
        }
        break;
    }
}
