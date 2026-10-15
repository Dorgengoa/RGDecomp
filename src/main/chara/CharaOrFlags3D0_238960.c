#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00238960 {
    u8 pad000[0x3D0];
    s64 m3D0;         /* +0x3D0 */
} Obj_FUN_00238960;

void CharaOrFlags3D0_238960(Obj_FUN_00238960 *o, s64 p1)
{
    o->m3D0 = (o->m3D0 | p1);
}
