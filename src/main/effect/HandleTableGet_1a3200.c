#include "types.h"

/* Handle-table lookup: validate a {index, generation} handle against a table
   and return the record it names, or NULL.  Head of a 4-member byte-identical
   clone group (120 B each) with HandleTableGet_1a3200 / HandleTableGet_1a3580 / HandleTableGet_1a3b20.

   Two spellings here are MEASURED, not guessed:

   * the null test is the bool round trip `((x != 0) ^ 1) != 0`, which is what
     emits `sltu`+`xori 1` with no `andi` narrow -- see
     [[levers.d/mwcc-cpp-bool-narrowing]]; it reaches this in plain C.
   * the two guards are ONE `||`.  As two separate `if`s the unit is 29 words
     against retail's 30 ([[levers.d/normal-guard-pair-or]]), and the bounds
     compare lands in a GPR instead of retail's `$at` ([[at-compare-class]]:
     the branch-taken condition is not a bare `<`).
   * `(g = k.h.gen)` on the RIGHT of the compare is what colours the three
     temps retail's way (gen `$v0`, tag chain `$v1`, index shift `$a1`).  The
     schedule is identical either way -- only the colouring moves -- and the
     same assignment on the LEFT is 6 words bad.  Creation order, per
     [[levers.d/mwcc-vreg-creation-source-position]].  Nine other spellings of
     the compare are ONE object (build/s26/a1d50c, 12 arms). */

typedef union Handle {
    u32 all;
    struct { u16 idx; u16 gen; } h;
} Handle;

typedef struct Rec { u8 b[0x10]; } Rec;

typedef struct Table {
    u8    pad000[0x4];
    u32   count;
    Rec  *recs;
    u8    pad00C[0x8];
    u32  *tags;
} Table;

Rec *HandleTableGet_1a3200(Table *t, Handle h)
{
    Handle k = h;
    u16 g;

    if (((k.all != 0) ^ 1) != 0) {
        return NULL;
    }
    if (k.h.idx >= t->count || t->tags[k.h.idx] != (g = k.h.gen)) {
        return NULL;
    }
    return &t->recs[k.h.idx];
}
