#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003761d0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    s32 m0C;         /* +0xC */
    s32 m10;         /* +0x10 */
    s32 m14;         /* +0x14 */
    s32 m18;         /* +0x18 */
} Obj_FUN_003761d0;

void McCardInfoClear_3761d0(Obj_FUN_003761d0 *o)
{
    o->m00 = 0;
    o->m04 = 0;
    o->m08 = 0;
    o->m0C = 0;
    o->m10 = 0;
    o->m14 = 0;
    o->m18 = 0;
}
