/* rgp:protos */
#define RGP_SELF_MemStackClearCursor_14d360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0014d360 {
    u8 pad000[0x20];
    s32 m20;         /* +0x20 */
    u8 pad024[0x8];
    s32 m2C;         /* +0x2C */
    s32 m30;         /* +0x30 */
    u8 pad034[0x8];
    s32 m3C;         /* +0x3C */
} Obj_FUN_0014d360;

void MemStackClearCursor_14d360(Obj_FUN_0014d360 *o)
{
    o->m2C = 0;
    o->m30 = -1;
    o->m3C = 0;
    o->m20 = 0;
}
