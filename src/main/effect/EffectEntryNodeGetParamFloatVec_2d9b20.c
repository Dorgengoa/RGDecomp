#include "types.h"

typedef struct Node Node;
typedef struct Elem Elem;

struct Elem { u8 pad0[8]; s32 f08; };
struct Node { Node *next; u8 pad04[0xC]; Elem *f10; };

typedef struct It { Node *first; Node *cur; s32 done; } It;
typedef struct A { u8 pad0[0x10]; s32 f10; } A;

extern void EffectInstanceGetParamFloatVec_2dd5f0(Elem *e, s32 b, s32 c);

void EffectEntryNodeGetParamFloatVec_2d9b20(It *it, A *a, s32 b, s32 c)
{
    Node *t;
    Elem **pp;
    Elem *x;
    s32 v;

    if (it->cur == 0) { it->cur = it->first; it->done = 0; }
    for (;;) {
        t = it->cur;
        if (t == 0) {
            pp = 0;
        } else {
            pp = &t->f10;
            it->cur = t->next;
            if (it->cur == 0) it->done = 1;
        }
        if (pp == 0) break;
        x = *pp;
        if (x == 0) continue;
        v = *(volatile s32*)&x->f08;
        if (a->f10 != v) continue;
        EffectInstanceGetParamFloatVec_2dd5f0(x, b, c);
        break;
    }
    it->cur = 0;
    it->done = 0;
}
