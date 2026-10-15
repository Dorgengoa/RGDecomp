#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003a80e0 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s16 m04;         /* +0x4 */
    s16 m06;         /* +0x6 */
    s16 m08;         /* +0x8 */
} Obj_FUN_003a80e0;

void AiAllySuggestRecReset_3a80e0(Obj_FUN_003a80e0 *o)
{
    o->m00 = -1;
    o->m02 = -1;
    o->m04 = -1;
    o->m06 = -1;
    o->m08 = -1;
}
