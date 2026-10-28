/* rgp:protos */
#define RGP_SELF_MemStackResetCursor_14d7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0014d7f0 {
    u8 pad000[0x28];
    s32 m28;         /* +0x28 */
    s32 m2C;         /* +0x2C */
    s32 m30;         /* +0x30 */
    s32 m34;         /* +0x34 */
    u8 pad038[0x4];
    s32 m3C;         /* +0x3C */
} Obj_FUN_0014d7f0;

void MemStackResetCursor_14d7f0(Obj_FUN_0014d7f0 *o)
{
    o->m28 = 0;
    o->m2C = 0;
    o->m34 = 0;
    o->m30 = -1;
    o->m3C = 0;
}
