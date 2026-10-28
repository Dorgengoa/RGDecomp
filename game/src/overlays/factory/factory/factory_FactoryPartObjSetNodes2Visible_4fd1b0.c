/* rgp:protos */
#define RGP_SELF_factory_FactoryPartObjSetNodes2Visible_4fd1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FD1B0 -- walk a zero-terminated list of part ids
 * and set or clear one render flag on each part's node.
 * 164 bytes, 44 instructions, 6 conditional branches, 2 calls.
 *
 * * TWIN of `factory_FactoryPartObjSetNodesVisible_4fd110` at ratio 0.952 -- the same walker over the
 * list at 0x4C instead of 0x44, and wrapped in a null test on the list itself,
 * which is the only structural difference.
 * Found by ranking the OPEN population against ITSELF.
 *
 * * BOTH loops fall into the SAME `lw $5, 0x0($16)` test block, which is why the
 * "on" arm ends in an early `return` rather than an `else`: the `beqz $6` at the
 * top branches straight to the second loop's test.
 *
 * * `p++` appears in the `beql`'s delay slot AND after the body -- the
 * likely-branch duplication `f_ds.py` tags, not two increments.
 */

typedef struct Node {
    u8  pad00[0x3C];
    s32 f3C;
} Node;

typedef struct Slot {
    u8    pad00[0x20];
    void *f20;
} Slot;

typedef struct Def {
    u8   pad00[0x4C];
    s32 *f4C;
} Def;

/*rgp*/

void factory_FactoryPartObjSetNodes2Visible_4fd1b0(Slot *o, Def *d, s32 off)
{
    s32  *p;
    Node *nd;

    p = d->f4C;
    if (p == 0) {
        return;
    }
    if (off != 0) {
        while (*p != 0) {
            nd = ((Node *)NodeObjFindChildByName_195040(o->f20, *p));
            if (nd != 0) {
                nd->f3C = nd->f3C & ~1;
            }
            p++;
        }
        return;
    }
    while (*p != 0) {
        nd = ((Node *)NodeObjFindChildByName_195040(o->f20, *p));
        if (nd != 0) {
            nd->f3C = nd->f3C | 1;
        }
        p++;
    }
}
