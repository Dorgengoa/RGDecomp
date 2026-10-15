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

extern void  factory_FactoryBlueprintSelect_4fafe0(void *page, Ent *item);
extern Root *func_1FEDE0(void);
extern void  func_370170(Iter *it, void *p);
extern Ent  *func_370040(Iter *it);

void factory_FactoryBlueprintSelectById_4e9f90(s32 key)
{
    Iter  it;
    void *p;
    Ent  *e;
    Ent  *found;

    p = func_1FEDE0()->f08->fA4->f0C;
    if (p != 0) {
        p = (u8 *)p + 0x88;
    }
    func_370170(&it, p);
    found = 0;
    while ((e = func_370040(&it)) != 0) {
        if (e->f00 == key) {
            found = e;
            break;
        }
    }
    if (found != 0) {
        factory_FactoryBlueprintSelect_4fafe0(D_00484A48, found);
    }
}
