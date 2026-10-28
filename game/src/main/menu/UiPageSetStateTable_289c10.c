/* rgp:protos */
#define RGP_SELF_UiPageSetStateTable_289c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00289c10 {
    u8 pad000[0x28];
    s16 m28;         /* +0x28 */
    u8 pad02A[0x2];
    s32 m2C;         /* +0x2C */
    s32 m30;         /* +0x30 */
} Obj_FUN_00289c10;

s32 UiPageSetStateTable_289c10(Obj_FUN_00289c10 *o, s32 p1)
{
    o->m2C = 0;
    o->m30 = 0;
    o->m28 = 0;
    o->m30 = p1;
    return 1;
}
