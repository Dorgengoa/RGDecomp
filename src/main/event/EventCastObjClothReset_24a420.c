#include "types.h"

typedef struct Node {
    struct Node *next;
    u8 pad4[8];
    s32 key;
    u8 ent[0x20];
} Node;

typedef struct {
    Node *head;
    Node *cur;
    s32 done;
} Iter;

extern void ModelObjSetDynClothActive_1ad390(void *, s32, s32);
extern void *ObjRecGetLiveObject_1c4a90(s32, s32, void *);
extern s32 GetCurrentScene_1f5be0(void);

void EventCastObjClothReset_24a420(Iter *it, s32 key, s32 val, s32 idx)
{
    s32 ctx;
    s32 r;
    u8 *ent;
    s32 k;
    Node *n;
    Node *nx;
    s32 t;
    void *obj;

    ctx = GetCurrentScene_1f5be0();
    if (it->cur != NULL) {
        r = -1;
    } else {
        it->cur = it->head;
        it->done = 0;
        r = 0;
    }
    if (r != 0) {
        ent = NULL;
    } else {
        goto next;
    loop:
        if (key == k) {
            goto found;
        }
    next:
            n = it->cur;
            if (n != NULL) {
                goto have;
            }
            ent = NULL;
            goto chk;
        have:
            k = n->key;
            ent = n->ent;
            n = n->next;
            it->cur = n;
            if (n == NULL) {
                it->done = 1;
            }
        chk:
        if (ent != NULL) {
            goto loop;
        }
    found:
        it->cur = NULL;
        it->done = 0;
    }
    if (ent != NULL) {
        t = *(s32 *)(ent + 8);
        switch (t) {
        case 1: case 2: case 3: case 6: case 7:
            break;
        default:
            return;
        }
        if ((obj = ObjRecGetLiveObject_1c4a90(ctx, *(s32 *)(ent + 0x1C), ent)) != NULL) {
            *(s32 *)((u8 *)obj + 0x464) = val + 1;
            *(s8 *)((u8 *)obj + 0x468) = idx;
        }
    }
}
