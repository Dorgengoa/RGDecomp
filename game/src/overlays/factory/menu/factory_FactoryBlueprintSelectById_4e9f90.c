/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintSelectById_4e9f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004E9F90 -- find the inventory record whose id matches
 * the key and hand it to the dialog page; do nothing if the list has no match.
 * 144 bytes, 36 instructions, 4 conditional branches, 4 calls.
 *
 * * `beql $5, $0` + `addiu $5, $5, 0x88` is a NULL-guarded displacement on the
 * list handle -- the sub-object at +0x88 -- written as an explicit `if`, never
 * a ternary ([[factory-*]] and the 0x004EFE90 note).
 *
 * * The search is the `while ((e = next(&it)) != 0)` form with the `break`:
 * retail enters the loop through `b` into the CONDITION, and the `bnel`
 * carrying `addiu $4, $29, 0x38` is the iterator argument re-formed for the
 * next call.
 */

typedef struct Ent {
    s16 f00;
} Ent;

typedef struct Iter {
    u8 pad00[0x8];
} Iter;

typedef struct Sub {
    u8    pad00[0xC];
    void *f0C;
} Sub;

typedef struct Mid {
    u8   pad00[0xA4];
    Sub *fA4;
} Mid;

typedef struct Root {
    u8   pad00[0x8];
    Mid *f08;
} Root;

extern void *D_00484A48;                        /* _gp - 0x728 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintSelectById_4e9f90(s32 key)
{
    Iter  it __attribute__((aligned(16)));
    void *p;
    Ent  *e;
    Ent  *found;

    p = ((Root *)GetGameData_1fede0())->f08->fA4->f0C;
    if (p != 0) {
        p = (u8 *)p + 0x88;
    }
    IterInit_370170(&it, p, 0, 0);
    found = 0;
    while ((e = ((Ent *)IterNext_370040(&it))) != 0) {
        if (e->f00 == key) {
            found = e;
            break;
        }
    }
    if (found != 0) {
        factory_FactoryBlueprintSelect_4fafe0(D_00484A48, found);
    }
}
