#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0034c7a0 {
    u8 pad000[0x76E];
    s16 m76E;         /* +0x76E */
    s16 m770;         /* +0x770 */
    u8 pad772[0x2E];
    s16 m7A0;         /* +0x7A0 */
} Obj_FUN_0034c7a0;

void RevelationBoardBeginCloseMaybe_34c7a0(Obj_FUN_0034c7a0 *o)
{
    o->m76E = 7;
    o->m770 = 0;
    o->m7A0 = 0;
}
