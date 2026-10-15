#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00376120 {
    u8 m00;         /* +0x0 */
    u8 m01;         /* +0x1 */
} Obj_FUN_00376120;

void SaveSlotEntrySetBroken_376120(Obj_FUN_00376120 *o)
{
    o->m00 = 1;
    o->m01 = 1;
}
