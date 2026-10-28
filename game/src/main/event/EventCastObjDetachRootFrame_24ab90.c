/* rgp:protos */
#define RGP_SELF_EventCastObjDetachRootFrame_24ab90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x8];
    s32 type;
    u8 padC[0x10];
    s32 unk1C;
} Pay0024AB90;

typedef struct Node0024AB90 {
    struct Node0024AB90 *next;
    u8 pad4[8];
    s32 key;
    Pay0024AB90 data;
} Node0024AB90;

typedef struct {
    Node0024AB90 *head;
    Node0024AB90 *cur;
    s32 done;
} Iter0024AB90;

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x20];
    s8 unk28;
} Obj0024AB90;

/*rgp*/
/*rgp*/
/*rgp*/

void EventCastObjDetachRootFrame_24ab90(Iter0024AB90 *arg0, s32 arg1)
{
    s32 ctx;
    s32 r;
    Node0024AB90 *n;
    Pay0024AB90 *p;
    s32 key;
    Obj0024AB90 *o;
    s32 h;
    s32 t;

    ctx = GetCurrentScene_1f5be0();
    if (arg0->cur != NULL) {
        r = -1;
    } else {
        arg0->cur = arg0->head;
        arg0->done = 0;
        r = 0;
    }
    if (r != 0) {
        p = NULL;
    } else {
        goto nxt;
    top:
        if (arg1 == key) {
            goto done;
        }
    nxt:
        n = arg0->cur;
        if (n == NULL) {
            p = NULL;
        } else {
            key = n->key;
            p = &n->data;
            arg0->cur = n->next;
            if (arg0->cur == NULL) {
                arg0->done = 1;
            }
        }
        if (p != NULL) {
            goto top;
        }
    done:
        arg0->cur = NULL;
        arg0->done = 0;
    }
    if (p == NULL) {
        return;
    }
    o = NULL;
    switch (p->type) {
    case 1:
    case 2:
    case 3:
    case 6:
    case 7:
        if ((h = ((s32)ObjRecGetLiveObject_1c4a90(ctx, p->unk1C))) != 0) {
            o = ((Obj0024AB90 *)ModelGetRootFrame_1511a0(h));
        }
        break;
    }
    if (o != NULL && o->unk28 != 0) {
        o->unk4 = 0;
    }
}
