#include "types.h"
/* insect 0x004F7A60 -- 7 instructions.  A five-word clear that returns the
 * object it cleared; the store order in retail is 0x00 0x08 0x04 0x10 0x0C,
 * which is the scheduler pairing the stores, not the source order. */

typedef struct Node {
    s32 m00;                        /* +0x00 */
    s32 m04;                        /* +0x04 */
    s32 m08;                        /* +0x08 */
    s32 m0C;                        /* +0x0C */
    s32 m10;                        /* +0x10 */
} Node;

Node *insect_ModelObjShadowFrameMapCtor_4f7a60(Node *n)
{
    n->m00 = 0;
    n->m08 = 0;
    n->m04 = 0;
    n->m10 = 0;
    n->m0C = 0;
    return n;
}
