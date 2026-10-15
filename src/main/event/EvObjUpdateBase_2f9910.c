#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002f9910 {
    u8 pad000[0xD0];
    s32 mD0;         /* +0xD0 */
} Obj_FUN_002f9910;

void EvObjUpdateBase_2f9910(Obj_FUN_002f9910 *o)
{
    o->mD0 = (o->mD0 & -0x101);
}
