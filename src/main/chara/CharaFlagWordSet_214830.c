#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00214830 {
    u8 pad000[0xA54];
    s32 mA54;         /* +0xA54 */
} Obj_FUN_00214830;

void CharaFlagWordSet_214830(Obj_FUN_00214830 *o, s32 p1)
{
    o->mA54 = (o->mA54 | p1);
}
