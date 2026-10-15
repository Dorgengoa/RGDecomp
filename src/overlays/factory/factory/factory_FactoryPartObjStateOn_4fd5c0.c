#include "types.h"

/* factory.bin overlay, 0x004FD5C0 -- commit one pending slot change: show the
 * node, run the three per-kind updates with the "on" flag, reset the node's
 * transform scale and latch the new state.  220 bytes, 56 instructions.
 *
 * ★ TWIN of `factory_FactoryPartObjStateOff_4fd9a0` at ratio 0.946 -- the same function with the
 * three updates taking 0 instead of 1 and the node flag cleared instead of set.
 * `factory_FactoryPartObjStatePlace_4fdf10` is the third member of the family.  All three were
 * found by ranking the OPEN population against ITSELF.
 *
 * ★ The `beql`'s delay slot holds `sb $0, 0x27($16)`, which is the FIRST
 * instruction of the merge block -- the likely-branch duplication `f_ds.py`
 * tags.  So `o->f27 = 0` and `o->f28 = 0` are OUTSIDE the `if`, and the body's
 * own `o->f28 = 0` is a separate statement that happens to repeat.
 *
 * ★ The 0x10-byte clear is a BYTE loop with a redundant null test on the
 * pointer and an unfilled latch -- the same idiom `factory_FactoryPartGroupBuildObjs_4fead0`
 * carries.  The counter must be UNSIGNED: an `s32` gives `bgtz`, retail has
 * `bnez`.
 *
 * * `nd = o->f20` is a NAMED LOCAL, not `o->f20` spelled at the call: retail
 * hoists the `lw` ABOVE the clear loop, and spelling the field at the call site
 * leaves it below -- 15 bad words at the right length, a pure one-word shift.
 * Three of four probe spellings that name it are exact; the one that does not is
 * the only failure.
 */

typedef struct Node {
    u8  pad00[0x32];
    s16 f32;
} Node;

typedef struct Slot {
    u8    pad00[0x20];
    Node *f20;
    s8    f24;
    s8    f25;
    u8    pad26[0x1];
    s8    f27;
    s16   f28;
} Slot;

typedef struct Src {
    u8  pad00[0x20];
    u8  f20;
    u8  pad21[0x3];
    s32 f24;
} Src;

extern void factory_FactoryPartObjSetNodesVisible_4fd110(Slot *o, s32 id, u8 a);
extern void factory_FactoryPartObjSetNodes2Visible_4fd1b0(Slot *o, s32 id, s32 on);
extern void factory_FactoryPartObjSetFuncFlag_4fd260(Slot *o, s32 id, s32 on);
extern void factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(Slot *o, s32 id, s32 on);
extern void func_1865B0(Node *nd, f32 *v);

void factory_FactoryPartObjStateOn_4fd5c0(Slot *o, Src *s)
{
    f32   v[4];
    Node *nd;
    s8   *p;
    u32   n;

    o->f20->f32 = 1;
    factory_FactoryPartObjSetNodesVisible_4fd110(o, s->f24, s->f20);
    if (o->f24 != o->f25) {
        factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(o, s->f24, 1);
        factory_FactoryPartObjSetFuncFlag_4fd260(o, s->f24, 1);
        factory_FactoryPartObjSetNodes2Visible_4fd1b0(o, s->f24, 1);
        nd = o->f20;
        p = (s8 *)v;
        n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        v[0] = 1.0f;
        v[1] = 1.0f;
        v[2] = 1.0f;
        func_1865B0(nd, v);
        o->f24 = o->f25;
        o->f28 = 0;
    }
    o->f27 = 0;
    o->f28 = 0;
}
