/* rgp:protos */
#define RGP_SELF_CharaFlagWordTest_214820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00214820 {
    u8 pad000[0xA54];
    s32 mA54;         /* +0xA54 */
} Obj_FUN_00214820;

u8 CharaFlagWordTest_214820(Obj_FUN_00214820 *o, s32 p1)
{
    u8 set;

    set = (o->mA54 & p1) != 0;
    return set;
}
