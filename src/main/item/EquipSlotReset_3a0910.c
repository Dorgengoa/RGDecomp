#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003a0910 {
    u8 pad000[0x4];
    s32 m04;         /* +0x4 */
    s16 m08;         /* +0x8 */
    s16 m0A;         /* +0xA */
    s16 m0C;         /* +0xC */
    u8 pad00E[0x2];
    s32 m10;         /* +0x10 */
} Obj_FUN_003a0910;

void EquipSlotReset_3a0910(Obj_FUN_003a0910 *o)
{
    o->m0A = -1;
    o->m08 = -1;
    o->m04 = 0;
    o->m10 = 0;
    o->m0C = 0;
}
