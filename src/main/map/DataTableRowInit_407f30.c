#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00407f30 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s32 m04;         /* +0x4 */
} Obj_FUN_00407f30;

void DataTableRowInit_407f30(Obj_FUN_00407f30 *o)
{
    o->m00 = -1;
    o->m02 = 0;
    o->m04 = 0;
}
