/* rgp:protos */
#define RGP_SELF_ActInfoWepActResolveAlias_22ee40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A name->name lookup: every failure path returns the name it was given.
   All four guards branch the SAME way, to a single `daddu $2,$17` placed
   AFTER the loop - that is an `&&` chain around the loop with one shared
   `return name;` at the end, not four early returns. */

/*rgp*/

struct Entry {
    s8 *key;
    s8 *val;
};

struct Table {
    s32 m00;
    struct Entry *ent;
    s16 count;
};

s8 *ActInfoWepActResolveAlias_22ee40(struct Table *t, s8 *name)
{
    struct Entry *e;
    s32 i;

    if (name != 0 && *name != 0 && (e = t->ent) != 0 && t->count > 0) {
        /* BOTH increments live in the for's third clause, in that order: the
           `i++` lands in the beql's delay slot and the `e++` in the block it
           branches to.  With `e++` in the body they come out swapped. */
        for (i = 0; i < t->count; i++, e++) {
            if (((unsigned char)StrEqualNonNull_1ca6c0(name, e->key)) != 0) {
                return e->val;
            }
        }
    }
    return name;
}
