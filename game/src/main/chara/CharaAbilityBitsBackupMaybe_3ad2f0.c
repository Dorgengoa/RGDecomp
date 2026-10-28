/* rgp:protos */
#define RGP_SELF_CharaAbilityBitsBackupMaybe_3ad2f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003ad2f0 {
    u8 pad000[0x2E0];
    s64 m2E0;         /* +0x2E0 */
    s64 m2E8;         /* +0x2E8 */
} Obj_FUN_003ad2f0;

s32 CharaAbilityBitsBackupMaybe_3ad2f0(Obj_FUN_003ad2f0 *o)
{
    o->m2E8 = o->m2E0;
    return 1;
}
