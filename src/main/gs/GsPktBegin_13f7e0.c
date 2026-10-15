#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0013f7e0 {
    u8 pad000[0x4];
    s32 m04;         /* +0x4 */
    u8 pad008[0xE8];
    s32 mF0;         /* +0xF0 */
} Obj_FUN_0013f7e0;

void GsPktBegin_13f7e0(Obj_FUN_0013f7e0 *o)
{
    o->m04 = 1;
    o->mF0 = 0;
}
