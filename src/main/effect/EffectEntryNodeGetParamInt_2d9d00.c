#include "types.h"

struct Node {
    struct Node *next;
};

struct Obj {
    u8 pad00[0x8];
    s32 m08;
};

struct Ent {
    struct Obj *obj;
};

struct Iter {
    struct Node *head;
    struct Node *cur;
    s32 done;
};

struct P5 {
    u8 pad00[0x10];
    s32 m10;
};

extern void EffectInstanceGetParamInt_2dd660(struct Obj *o, s32 idx, s32 arg);

void EffectEntryNodeGetParamInt_2d9d00(struct Iter *it, struct P5 *p5, s32 idx, s32 arg)
{
    struct Node *c;
    struct Ent *e;
    struct Obj *o;

    if (it->cur == 0) {
        it->cur = it->head;
        it->done = 0;
    }
    for (;;) {
        c = it->cur;
        if (c == 0) {
            e = 0;
        } else {
            e = (struct Ent *)((u8 *)c + 0x10);
            it->cur = c->next;
            if (it->cur == 0) {
                it->done = 1;
            }
        }
        if (e == 0) {
            break;
        }
        o = e->obj;
        if (o != 0) {
            s32 t = *(volatile s32 *)&o->m08;
            if (p5->m10 == t) {
                if (idx >= 0 && idx < 0x10) {
                    EffectInstanceGetParamInt_2dd660(o, idx, arg);
                    break;
                }
            }
        }
    }
    it->cur = 0;
    it->done = 0;
}
