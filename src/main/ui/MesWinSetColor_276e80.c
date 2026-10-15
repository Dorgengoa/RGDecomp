#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00276e80 {
    u8 pad000[0x1944];
    u8 m1944;         /* +0x1944 */
    u8 m1945;         /* +0x1945 */
} Obj_FUN_00276e80;

void MesWinSetColor_276e80(Obj_FUN_00276e80 *o, s32 p1)
{
    o->m1944 = p1;
    o->m1945 = o->m1944;
}
