#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003700f0 {
    u8 pad000[0x6];
    s16 m06;         /* +0x6 */
} Obj_FUN_003700f0;

void IterReset_3700f0(Obj_FUN_003700f0 *o)
{
    o->m06 = -1;
}
