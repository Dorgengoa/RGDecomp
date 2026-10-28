/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupUnderCursor_4ffa90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FFA90 -- 188 bytes / 47 words, 4 branches, 5 calls.
 * Resolve the cursor's world position (0x2DC, 0x2E0) to a grid cell, walk the
 * cell's group and part, report "part is at least stage 4" through the
 * optional out-byte and return the cell's group id.
 *
 * * The axis pair is the recorded `factory_FactoryPartLiftAtPos_501ed0` order: the column
 *   helper `00503F60` consumes 0x2DC and the row helper `00503F00` consumes
 *   0x2E0, and only the FIRST result needs a callee-saved register.
 * * `daddu $6, $2, $0` in the `005037F0` delay slot is the row index used
 *   straight out of `$2`, so it is NOT a named local.
 * * Each of the three null guards is `bnel <past> / b <epilogue>` with
 *   `addiu $2, $0, -0x1` in the branch delay slot: three separate
 *   `return -1;` statements, not a `||` join.
 * * `slti $2, $2, 0x4` + `xori $2, $2, 0x1` into a GENERAL register is the
 *   non-strict compare `t->f25 >= 4` -- the boolean is stored with `sb`.
 * * `lh $2, 0x0($16)` appears twice, once in the `beql` likely slot: one
 *   `return c->f00;` after the guarded store.
 */

typedef struct Cell {
    s16 f00;
    s16 f02;
    u16 f04;
} Cell;                                         /* 6 */

typedef struct Part {
    u8 pad00[0x25];
    s8 f25;
} Part;

typedef struct Group {
    u8 pad00[0x4];
} Group;

typedef struct Grid {
    u8  pad000[0x2DC];
    f32 f2DC;
    f32 f2E0;
} Grid;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryPartGroupUnderCursor_4ffa90(Grid *o, s8 *out)
{
    Cell  *c;
    Group *g;
    Part  *p;
    s32    cx;

    cx = factory_FactoryGridColFromX_503f60(o, o->f2DC);
    c = ((Cell *)factory_FactoryGridCellAt_5037f0(o, cx, factory_FactoryGridRowFromZ_503f00(o, o->f2E0)));
    if (c == 0) {
        return -1;
    }
    g = ((Group *)factory_FactoryPartGroupFindById_504080(o, c->f00));
    if (g == 0) {
        return -1;
    }
    p = ((Part *)factory_FactoryPartGroupGetObj_4fea80(g, c->f02));
    if (p == 0) {
        return -1;
    }
    if (out != 0) {
        *out = p->f25 >= 4;
    }
    return c->f00;
}
