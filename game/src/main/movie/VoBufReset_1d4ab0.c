/* rgp:protos */
#define RGP_SELF_VoBufReset_1d4ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001d4ab0 {
    u8 pad000[0xC];
    s32 m0C;         /* +0xC */
    s32 m10;         /* +0x10 */
} Obj_FUN_001d4ab0;

s32 VoBufReset_1d4ab0(Obj_FUN_001d4ab0 *o)
{
    o->m0C = 0;
    o->m10 = 0;
    return 0;
}
