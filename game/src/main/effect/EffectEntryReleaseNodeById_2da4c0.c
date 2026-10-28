/* rgp:protos */
#define RGP_SELF_EffectEntryReleaseNodeById_2da4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node Node;
typedef struct Elem Elem;

struct Elem { u8 pad0[8]; s32 f08; };
struct Node { Node *next; u8 pad04[0xC]; Elem *f10; };

typedef struct It { Node *first; Node *cur; s32 done; } It;
typedef struct A { s32 pad0[4]; s32 f10; } A;

/*rgp*/

void EffectEntryReleaseNodeById_2da4c0(It *it, A *a, int rgp_a2, int rgp_a3)
{
    A local __attribute__((aligned(16)))=*a;
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
        v = x->f08;
        if (local.f10 != v) continue;
        EffectEntryReleaseNode_2da6c0(it, x, 0, (int)rgp_a3);
        break;
    }
    it->cur = 0;
    it->done = 0;
}
