#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003a6940 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s32 m04;         /* +0x4 */
} Obj_FUN_003a6940;

void CharaEventLogTimerReset_3a6940(Obj_FUN_003a6940 *o)
{
    o->m00 = -1;
    o->m02 = -1;
    o->m04 = 0;
}
