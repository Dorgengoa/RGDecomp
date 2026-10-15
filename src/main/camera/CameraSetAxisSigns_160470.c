#include "types.h"

/* Latch a float pair into an integer pair. Both conversions are the R5900
   cvt.w.s, which TRUNCATES -- see the SplinePathStep_256970 note for why that
   matters wherever the result feeds an index. */

typedef struct Latch254 {
    u8 pad000[0x254];
    s32 a;             /* +0x254 */
    s32 b;             /* +0x258 */
} Latch254;

void CameraSetAxisSigns_160470(Latch254 *o, f32 x, f32 y)
{
    o->a = (s32)x;
    o->b = (s32)y;
}
