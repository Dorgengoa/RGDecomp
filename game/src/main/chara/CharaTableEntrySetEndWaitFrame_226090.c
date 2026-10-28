/* rgp:protos */
#define RGP_SELF_CharaTableEntrySetEndWaitFrame_226090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00226090 {
    u8 pad000[0x3A];
    s16 m3A;         /* +0x3A */
    s32 m3C;         /* +0x3C */
    s32 m40;         /* +0x40 */
} Obj_FUN_00226090;

void CharaTableEntrySetEndWaitFrame_226090(Obj_FUN_00226090 *o, s32 p1, s32 p2)
{
    o->m3A = 1;
    o->m3C = p1;
    o->m40 = p2;
}
