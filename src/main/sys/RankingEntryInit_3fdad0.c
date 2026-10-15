#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003fdad0 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    s16 m0C;         /* +0xC */
    s16 m0E;         /* +0xE */
    s16 m10;         /* +0x10 */
} Obj_FUN_003fdad0;

void RankingEntryInit_3fdad0(Obj_FUN_003fdad0 *o)
{
    o->m00 = 0;
    o->m04 = -1;
    o->m08 = -1;
    o->m0C = -1;
    o->m0E = -1;
    o->m10 = 0;
}
