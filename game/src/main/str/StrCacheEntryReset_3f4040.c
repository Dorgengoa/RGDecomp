/* rgp:protos */
#define RGP_SELF_StrCacheEntryReset_3f4040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003f4040 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
} Obj_FUN_003f4040;

void StrCacheEntryReset_3f4040(Obj_FUN_003f4040 *o)
{
    o->m00 = -1;
    o->m04 = -1;
    o->m02 = -1;
    o->m08 = 0;
}
