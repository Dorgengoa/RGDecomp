/* rgp:protos */
#define RGP_SELF_factory_FactoryPartCentreZ_501d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00501D70 -- the centre of a placed part along one
 * axis: take the part's extent for the current orientation, convert it to the
 * two grid bounds and average their world coordinates.
 * 168 bytes, 42 instructions, 2 conditional branches, 4 calls.
 *
 * * TWIN of `factory_FactoryPartCentreX_501e20` at ratio 1.000 -- the other axis, so the
 * two `lb` offsets swap and the two helpers become `005028C0`/`00503760`.
 *
 * * `factory_FactoryPartGroupFindById_504080` takes two parameters and the call marshals NEITHER:
 * both arrive in `$4`/`$5` as this function's own first two parameters.
 *
 * * `dsll32/dsra32 ..,24` off a plain `lb` is an `s32` local plus an explicit
 * `(s8)` cast -- the 8-bit reading of [[normal-s16-cast-sign-extension]].
 *
 * * `b` is declared FIRST: mwcc allocates stack locals in REVERSE declaration
 * order, so `b` is at 0x4E($29) and `a` at 0x4C($29).
 *
 * * The `beql`'s delay slot holds `lb $2, 0x15($2)`, which is NOT the merge's
 * first instruction, so the guard really is an if/else and not a fall-through.
 */

typedef struct Group {
    u8 pad00[0x14];
    s8 f14;
    s8 f15;
} Group;

typedef struct Obj {
    u8 pad000[0x2D0];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

f32 factory_FactoryPartCentreZ_501d70(Obj *o, s32 k, s32 flags, f32 v)
{
    f32    t;
    s16    b;
    s16    a;
    Group *g;
    s32    n;

    g = ((Group *)factory_FactoryPartGroupFindById_504080(o, k));
    if (g == 0) {
        return 0.0f;
    }
    if ((flags & 1) != 0) {
        n = g->f14;
    } else {
        n = g->f15;
    }
    factory_FactoryGridSpanZ_502810(o, &a, &b, (s8)n, v);
    t = factory_FactoryGridCellCenterZ_503730(o, b);
    return 0.5f * (t + factory_FactoryGridCellCenterZ_503730(o, a));
}
