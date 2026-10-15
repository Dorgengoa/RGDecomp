#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002bbc10 {
    u8 pad000[0xB8];
    s32 mB8;         /* +0xB8 */
} Obj_FUN_002bbc10;

void AiReqMoveToPoint_2bbc10(Obj_FUN_002bbc10 *o)
{
    o->mB8 = (o->mB8 | 0x20);
}
