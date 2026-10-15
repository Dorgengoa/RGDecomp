#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002f9cc0 {
    u8 pad000[0xD0];
    s32 mD0;         /* +0xD0 */
} Obj_FUN_002f9cc0;

s32 EvObjFlagBit30Clear_2f9cc0(Obj_FUN_002f9cc0 *o)
{
    return (((o->mD0 & 0x40000000) != 0) ^ 1);
}
