#include "types.h"

/* factory.bin overlay, 0x004FD260 -- walk a zero-terminated list of part ids
 * and stamp one byte-wide field on every node the search finds.
 * 100 bytes, 25 instructions, 3 branches, 1 call.
 *
 * * THIRD TWIN of `factory_FactoryPartObjSetNodesVisible_4fd110` / `factory_FactoryPartObjSetNodes2Visible_4fd1b0`: the same
 *   walker, the list at 0x48 instead of 0x44 / 0x4C, and `func_1907C0` on the
 *   sub-tree at `+0x114` of `o->f20` instead of `func_195040` on `o->f20`.
 * * The `p == 0` guard is `004FD1B0`'s, so the outer shape is `if (p == 0)
 *   return;` and then a single `while (*p != 0)`.
 * * `p++` appears in the `beql`'s delay slot AND after the body -- the
 *   likely-branch duplication, not two increments.
 * * `andi $16, $6, 0xFF` in the `b`'s delay slot is a `u8` third parameter
 *   widened once and hoisted out of the loop; the field itself is a word.
 * * `lw $2, 0x20($18)` sits in the loop-back branch's delay slot, so
 *   `o->f20` is RE-READ every iteration -- the handle is not a local.
 */

typedef struct Root {
    u8  pad000[0x114];
    s32 f114;
} Root;

typedef struct Node {
    u8  pad00[0x44];
    s32 f44;
} Node;

typedef struct Slot {
    u8    pad00[0x20];
    Root *f20;
} Slot;

typedef struct Def {
    u8   pad00[0x48];
    s32 *f48;
} Def;

extern Node *func_1907C0(void *h, s32 id);

void factory_FactoryPartObjSetFuncFlag_4fd260(Slot *o, Def *d, u8 v)
{
    s32  *p;
    Node *nd;

    p = d->f48;
    if (p == 0) {
        return;
    }
    while (*p != 0) {
        nd = func_1907C0(&o->f20->f114, *p);
        if (nd != 0) {
            nd->f44 = v;
        }
        p++;
    }
}
