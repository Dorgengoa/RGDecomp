#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002d5660 {
    s32 m00;         /* +0x0 */
    u8 pad004[0x3C];
    s16 m40;         /* +0x40 */
    s16 m42;         /* +0x42 */
} Obj_FUN_002d5660;

void GuardWaveEffectReset_2d5660(Obj_FUN_002d5660 *o)
{
    o->m00 = 0;
    o->m40 = -1;
    o->m42 = -1;
}
