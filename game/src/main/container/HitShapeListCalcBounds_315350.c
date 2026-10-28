/* rgp:protos */
#define RGP_SELF_HitShapeListCalcBounds_315350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The PRE-LOOP call keeps the incoming $4 (nothing rewrites it between entry
   and the jal), so its first argument is the function's own first parameter,
   not the stack temporary the loop body uses; the loop therefore starts at 1.
   MEASURED (q12 sweep, 7+7 arms):
     - the loop must be a `for` whose INIT is `i = 1`; that init is what fills
       the entry `b`'s delay slot.  A `while` with `i = 1` as a preceding
       statement duplicates the `slt` into that slot instead, one word too
       many -- and source ASSIGNMENT order (i before p or p before i) is INERT
       there (two decl-order cells only, sha1 6bd60e82 / 6e0b4827).
     - DECLARATION ORDER is the live axis: `n; p; i;` (i declared LAST takes
       the LOWER callee-saved register, $17).  `n; i; p;` misses by 7 words.
     - both increments go in the BODY, i before p; `p; n; i;` and the comma
       form are INERT with it (one object, sha1 93838be3).
   The temporary is at 0x50 in a 0x70 frame => 0x20 bytes. */
typedef struct Tmp00315350 { u8 b[0x20]; } Tmp00315350;
typedef struct Ent00315350 { u8 b[0x30]; } Ent00315350;
typedef struct Src00315350 { u8 pad00[0x14]; s32 m14; Ent00315350 *m18; } Src00315350;
/*rgp*/
/*rgp*/
void HitShapeListCalcBounds_315350(void *a, Src00315350 *b)
{
    Tmp00315350 tmp __attribute__((aligned(16)));
    s32 n;
    Ent00315350 *p;
    s32 i;
    n = b->m14;
    if (n != 0) {
        p = b->m18;
        HitShapeCalcBounds_315140(a, p);
        for (i = 1; i < n; ) {
            HitShapeCalcBounds_315140(&tmp, p);
            BBoxUnion_13dea0(a, &tmp);
            i++;
            p++;
        }
    }
}
