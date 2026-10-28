/* rgp:protos */
#define RGP_SELF_insect_InsectCmdMenuGetEntry_4efc50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFC50 -- 48 bytes, 12 instructions, no calls, 2 conditional
 * branches.  A leaf list walk: advance `n` links from `o->f4`, tolerating a
 * null anywhere along the way.  The `b .L004EFC6C` with the counter zeroed in
 * its delay slot is mwcc's pre-tested `for`; the `beql` skipping the link load
 * with the increment in ITS delay slot is the `if (p != 0)` guard.
 */

typedef struct Node {
    u8           pad00[4];
    struct Node *f4;                /* +0x4 */
} Node;

Node *insect_InsectCmdMenuGetEntry_4efc50(Node *o, s32 n)
{
    Node *p;
    s32 i;

    p = o->f4;
    for (i = 0; i < n; i++) {
        if (p != 0) {
            p = p->f4;
        }
    }
    return p;
}
