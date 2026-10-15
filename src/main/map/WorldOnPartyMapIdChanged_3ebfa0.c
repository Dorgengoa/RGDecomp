#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003ebfa0 {
    u8 pad000[0x2C];
    u8 m2C;         /* +0x2C */
} Obj_FUN_003ebfa0;

s32 WorldOnPartyMapIdChanged_3ebfa0(Obj_FUN_003ebfa0 *o)
{
    return (((o->m2C & 1) != 0) ^ 1);
}
