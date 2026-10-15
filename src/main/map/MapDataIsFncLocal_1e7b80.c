#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001e7b80 {
    u8 pad000[0x25];
    u8 m25;         /* +0x25 */
} Obj_FUN_001e7b80;

s32 MapDataIsFncLocal_1e7b80(Obj_FUN_001e7b80 *o)
{
    return (o->m25 & 2);
}
