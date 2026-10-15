#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002a4e40 {
    u8 pad000[0x14];
    s32 m14;         /* +0x14 */
} Obj_FUN_002a4e40;

s32 MenuSetMode_2a4e40(Obj_FUN_002a4e40 *o, s32 p1)
{
    o->m14 = p1;
    return 1;
}
