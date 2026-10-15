#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0031d3b0 {
    u8 pad000[0x228];
    u8 m228;         /* +0x228 */
} Obj_FUN_0031d3b0;

s32 HpGaugeSetFlags_31d3b0(Obj_FUN_0031d3b0 *o, s32 p1)
{
    o->m228 = p1;
    return 1;
}
