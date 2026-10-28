/* rgp:protos */
#define RGP_SELF_TwoTableViewGetCount_4138c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- the ONE-WORD-SHORT bucket, one-off.
   Two guarded accumulations into a single result initialised in the first
   branch's delay slot.  The struct is a STAND-IN: offsets and access widths
   are read off the listing. */

typedef struct Node {
    u8  pad[0x7C];
    s16 h;
} Node;

typedef struct Obj {
    u8    pad[8];
    Node *a;
    Node *b;
} Obj;

s32 TwoTableViewGetCount_4138c0(Obj *p)
{
    s32 n = 0;

    if (p->a) {
        n += p->a->h;
    }
    if (p->b) {
        n += p->b->h;
    }
    return n;
}
