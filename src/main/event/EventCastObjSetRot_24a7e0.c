#include "types.h"

typedef struct Ent {
    u8 p0[8];
    s32 f8;
    u8 p0C[0x1C - 0xC];
    s32 f1C;
} Ent;

typedef struct Node {
    struct Node *next;
    u8 p4[8];
    s32 key;
    Ent data;
} Node;

typedef struct Iter {
    Node *head;
    Node *cur;
    s32 flag;
} Iter;

extern s32 GetCurrentScene_1f5be0(void);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern void ModelSetRot_151080(s32, s32);

void EventCastObjSetRot_24a7e0(Iter *self, s32 key, s32 a2)
{
    s32 x;
    Node *cur;
    Node *nx;
    Ent *e;
    s32 k;
    s32 st;
    s32 t;
    s32 r;

    x = GetCurrentScene_1f5be0();
    if (self->cur != 0) {
        st = -1;
    } else {
        self->cur = self->head;
        self->flag = 0;
        st = 0;
    }
    if (st != 0) {
        e = 0;
    } else {
        goto body;
    top:
        if (key == k) {
            goto reset;
        }
    body:
        cur = self->cur;
        if (cur == 0) {
            e = 0;
        } else {
            k = cur->key;
            e = &cur->data;
            nx = cur->next;
            self->cur = nx;
            if (nx == 0) {
                self->flag = 1;
            }
        }
        if (e != 0) {
            goto top;
        }
    reset:
        self->cur = 0;
        self->flag = 0;
    }
    if (e != 0) {
        t = e->f8;
        switch (t) {
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
            if ((r = ObjRecGetLiveObject_1c4a90(x, e->f1C)) != 0) {
                ModelSetRot_151080(r, a2);
            }
            break;
        }
    }
}
