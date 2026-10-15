#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00436930 {
    u8 pad000[0xC];
    s32 m0C;         /* +0xC */
    u8 pad010[0xD0];
    s16 mE0;         /* +0xE0 */
    s16 mE2;         /* +0xE2 */
    s16 mE4;         /* +0xE4 */
    s16 mE6;         /* +0xE6 */
} Obj_FUN_00436930;

s32 TextEntryReset_436930(Obj_FUN_00436930 *o)
{
    o->mE6 = 0;
    o->m0C = 0;
    o->mE2 = 0;
    o->mE4 = 1;
    o->mE0 = 0;
    return 0;
}
