/* rgp:protos */
#define RGP_SELF_EffectEntryReleaseNodesByKey_2da1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same list-iterator drive as EffectEntryNodeGetParamInt_2d9d00, but the match is on two halfword
   keys and the callback does not end the walk (retail branches back to the
   loop head after the jal). */

typedef struct Node {
    struct Node *next;      /* 0x0 */
    u8 pad4[0xC];
    void *elem;             /* 0x10 */
} Node;

typedef struct Iter {
    Node *head;             /* 0x0 */
    Node *cur;              /* 0x4 */
    s32 done;               /* 0x8 */
} Iter;

typedef struct Elem {
    s16 f0;                 /* 0x0 */
    s16 f2;                 /* 0x2 */
    s16 f4;                 /* 0x4 */
} Elem;

/*rgp*/

void EffectEntryReleaseNodesByKey_2da1d0(Iter *it, s32 b, s16 c)
{
    Node *cur;
    Elem **slot;
    Elem *e;

    if (c == -1) {
        return;
    }
    if (it->cur == 0) {
        it->cur = it->head;
        it->done = 0;
    }
    for (;;) {
        cur = it->cur;
        if (cur == 0) {
            slot = 0;
        } else {
            slot = (Elem **)&cur->elem;
            cur = cur->next;
            it->cur = cur;
            if (cur == 0) {
                it->done = 1;
            }
        }
        if (slot == 0) {
            break;
        }
        e = *slot;
        if (e == 0) {
            continue;
        }
        if (c == e->f2 && b == e->f4) {
            /* e is the second argument: that is why it lands in $5 and is
               not coalesced into slot's register. */
            EffectEntryReleaseNode_2da6c0(it, e, 0, 0);
        }
    }
    it->cur = 0;
    it->done = 0;
}
