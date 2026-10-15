#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_002fb8d0 {
    u8 pad000[0xCA];
    s16 mCA;         /* +0xCA */
} Obj_FUN_002fb8d0;

s32 NpcObjSetUnloadState_2fb8d0(Obj_FUN_002fb8d0 *o)
{
    o->mCA = 6;
    return 1;
}
