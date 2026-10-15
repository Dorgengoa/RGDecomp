#include "types.h"
/* insect 0x0051DBA0 -- 52 bytes, 13 instructions.
 * $4 is never written before the call, so arg0 passes straight through. */

typedef struct Node {
    u8  pad00[0x8];
    s32 f8;                         /* +0x08 */
    u8  pad0C[0x14 - 0xC];
    s32 f14;                        /* +0x14 */
} Node;

extern s32 insect_InsectBattleEffectsRemove_51da90(void *a, s32 b, s32 c);

s32 insect_InsectBattleEffectsRemoveNode_51dba0(void *a, Node *n)
{
    if (n != 0) {
        return insect_InsectBattleEffectsRemove_51da90(a, n->f8, n->f14);
    }
    return 0;
}
