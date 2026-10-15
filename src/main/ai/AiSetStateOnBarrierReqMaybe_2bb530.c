#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002bb530 {
    u8 pad000[0xAC];
    s16 mAC;         /* +0xAC */
} Obj_FUN_002bb530;

void AiSetStateOnBarrierReqMaybe_2bb530(Obj_FUN_002bb530 *o)
{
    o->mAC = 0x276;
}
