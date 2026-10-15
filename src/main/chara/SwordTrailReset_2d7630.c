#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002d7630 {
    s16 m00;         /* +0x0 */
    u8 pad002[0x2];
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    u8 pad00C[0x4];
    s32 m10;         /* +0x10 */
    u8 pad014[0x18];
    s32 m2C;         /* +0x2C */
} Obj_FUN_002d7630;

void SwordTrailReset_2d7630(Obj_FUN_002d7630 *o)
{
    o->m04 = 0;
    o->m08 = 0;
    o->m10 = 0;
    o->m2C = 0x3F800000;
    o->m00 = 0;
}
