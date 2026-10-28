/* rgp:protos */
#define RGP_SELF_insect_InsectCmdMenuCount_4efc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFC10 -- 56 bytes, 14 instructions, no calls.  A list-length
 * walk starting at the SECOND node; the three `nop`s inside the loop are
 * mwcc's own load-latency padding, not an alignment artefact. */

typedef struct Node {
    u8           pad00[0x4];
    struct Node *m4;                /* +0x04 */
} Node;

s32 insect_InsectCmdMenuCount_4efc10(Node *n)
{
    s32 c;

    c = 0;
    n = n->m4;
    if (n == 0) {
        return c;
    }
    do {
        n = n->m4;
        c++;
    } while (n != 0);
    return c;
}
