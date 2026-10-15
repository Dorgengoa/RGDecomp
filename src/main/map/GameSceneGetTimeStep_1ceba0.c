#include "types.h"

/* The product of two adjacent floats deep in a large object. */

typedef struct Scaled5E08 {
    u8 pad000[0x5E08];
    f32 a;             /* +0x5E08 */
    f32 b;             /* +0x5E0C */
} Scaled5E08;

f32 GameSceneGetTimeStep_1ceba0(Scaled5E08 *o)
{
    return o->b * o->a;
}
