#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00384590 {
    s32 m00;         /* +0x0 */
    u8 m04;         /* +0x4 */
    u8 m05;         /* +0x5 */
} Obj_FUN_00384590;

void MenuObjSoundInit_384590(Obj_FUN_00384590 *o)
{
    o->m00 = -1;
    o->m04 = 0;
    o->m05 = 0;
}
