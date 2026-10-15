#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001f4890 {
    u8 pad000[0x6];
    u8 m06;         /* +0x6 */
} Obj_FUN_001f4890;

s32 CharaResRecIsReady_1f4890(Obj_FUN_001f4890 *o)
{
    return (o->m06 & 0x80);
}
