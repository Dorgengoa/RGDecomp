/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltHasRoom_500d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00500D30 -- 72 bytes / 18 words, 2 branches, 0 calls.
 * Sum the 0x06 field over the part list at `0x2AC` and report whether the total
 * is under 300.
 *
 * Sub-family B of lane fy04 with `factory_FUN_004FFA30`.
 *
 * * NO `dsll32/dsra32` here, so the accumulator is a plain s32 -- the twin's
 *   per-add `(s16)` cast is the one difference in the loop.
 * * `slti $2, $5, 0x12C` after the loop is the whole tail: `return sum < 300;`
 *   -- the comparison IS the return value, not an `if`.
 * * The `addiu $4,$4,1` scheduled between the `lh` and the `addu` is the
 *   scheduler filling the load-use gap, not a source reordering.
 * ** THE RESIDUE WAS DECLARATION ORDER and it was the WHOLE residue.  With `i`
 *   declared before `sum` the two land in the wrong registers ($5/$4 instead of
 *   $4/$5) and four words read as bad; declaring `sum` first fixes all four.
 *   mwcc assigns REGISTER-resident locals in FORWARD declaration order here --
 *   the reverse-order rule in [[factory-list-ranking]] is about STACK locals
 *   and does not transfer.  A 32-cell sweep (build/fy04v/v_500d30.py) closes
 *   the other axis: the 24 declaration orders collapse to exactly four objects
 *   (0/4/7/9 bad) and every one of the nine BODY/TAIL spellings tried
 *   (`while`, `p++` in the body, `sum = sum + ..`, `p++->f06`, `i` initialised
 *   outside the `for`, `sum = 0` before the `n` read, `300 > sum`, an explicit
 *   `if`, an `s16 n`) compiles to the byte-identical baseline object -- twelve
 *   inert cells, so the loop spelling is unobservable here.
 */

typedef struct Part {
    u8  pad00[0x6];
    s16 f06;
    u8  pad08[0x4];
} Part;

typedef struct Obj {
    u8    pad000[0x2AC];
    Part *parts;
    s16   nparts;
} Obj;

s32 factory_FactoryBeltHasRoom_500d30(Obj *o)
{
    Part *p;
    s32   n;
    s32   sum;
    s32   i;

    p = o->parts;
    if (p == 0) {
        return 0;
    }
    n = o->nparts;
    sum = 0;
    for (i = 0; i < n; i++, p++) {
        sum += p->f06;
    }
    return sum < 300;
}
