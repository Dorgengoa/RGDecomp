/* rgp:protos */
#define RGP_SELF_factory_FactoryBeltCommitPreview_500400 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3

#include "types.h"

/* factory.bin overlay, 0x00500400 -- 72 bytes / 18 words, 2 branches, 0 calls
 * of its own: the trailing `factory_FactoryBeltRebuildTiles_500b00(o)` is a TAIL JUMP (`j`), so
 * the unit has NO stack frame at all.
 *
 * ** TWIN of `factory_FUN_005005D0` (96 B): the SAME guard, the SAME walk and
 *    the SAME pragma.  The only difference is the tail -- 005005D0 `return 1;`s
 *    after the call, which blocks the tail jump and forces the 0x10 frame plus
 *    the `sd $31`.  One source under two ids apart from that.
 *
 * ** `#pragma optimization_level 3` is the whole residue.  At -O4 the unit is
 *    RIGHT LENGTH with FIVE bad words, and all five are a pure $2/$3 rename in
 *    the loop body: -O4 puts the list base in $2 and the 12*i product in $3
 *    (`lw $2,0x2AC / addu $3,$3,$5 / sll $3,$3,2 / addu $3,$2,$3`, and
 *    `sll $3,$5,1` in the branch-likely slot), retail puts the base in $3 and
 *    the product in $2.  Fourteen source spellings were swept in one round trip
 *    -- a named base local, a named address local, a named index local, a named
 *    value temp, `(o->parts + i)->`, the `(u8 *)` cast form, the guard on a
 *    local, a `while` loop, `o->nparts > i`, three declaration orders -- and
 *    ELEVEN of them produced the byte-IDENTICAL object (sha1 b82fe896), i.e.
 *    the source axis is a measured null here.  `optimization_level 3` matches;
 *    so does `#pragma opt_propagation off`, and the two emit the SAME object
 *    (ee75e44b), which names the -O4 pass responsible as copy propagation.
 *
 * * The part list at `0x2AC` / count `0x2B0` / 0xC stride is the fy04 family's
 *   (`factory_FUN_00503E50`, `factory_FUN_004FFA30`).  `sll,1 / addu / sll,2 /
 *   addu` is the 12-byte stride strength reduction, i.e. `&o->parts[i]`.
 * * The base is RE-LOADED inside the loop while the guard has its own load, and
 *   the count is re-read at every test, so neither is a named local: the source
 *   subscripts `o->parts` and compares `o->nparts` in place.
 * * `lh 0x8` -> `sh 0x6` is an INTERLEAVED load/store pair, i.e. ONE assignment
 *   statement, and the two subscripts CSE to one address.
 */

typedef struct Part {
    u8  pad00[0x6];
    s16 f06;
    s16 f08;
    u8  pad0A[0x2];
} Part;                                         /* 0xC */

typedef struct Obj {
    u8    pad000[0x2AC];
    Part *parts;
    s16   nparts;
} Obj;

/*rgp*/

void factory_FactoryBeltCommitPreview_500400(Obj *o)
{
    s32 i;

    if (o->parts != 0) {
        for (i = 0; i < o->nparts; i++) {
            o->parts[i].f06 = o->parts[i].f08;
        }
    }
    factory_FactoryBeltRebuildTiles_500b00(o);
}
