#include "types.h"

/* factory.bin overlay, 0x00501ED0 -- world (x, y) to a grid cell test: map each
 * coordinate through its own axis helper, then run the placement test.
 * 88 bytes, 24 instructions, 0 conditional branches, 3 calls.
 *
 * * `$f13` is parked in the callee-saved `$f20` across the FIRST call, so the
 * two float parameters are consumed in declaration order: `x` by the column
 * helper `00503F60` and `y` by the row helper `00503F00`.
 */

typedef struct Grid {
    u8 pad000[0x2A0];
} Grid;

extern s32 factory_FactoryGridRowFromZ_503f00(Grid *o, f32 v);
extern s32 factory_FactoryGridColFromX_503f60(Grid *o, f32 v);
extern s32 factory_FactoryPartLiftAt_501f30(Grid *o, s32 x, s32 y);

s32 factory_FactoryPartLiftAtPos_501ed0(Grid *o, f32 x, f32 y)
{
    s32 cx;
    s32 cy;

    cx = factory_FactoryGridColFromX_503f60(o, x);
    cy = factory_FactoryGridRowFromZ_503f00(o, y);
    return factory_FactoryPartLiftAt_501f30(o, cx, cy);
}
