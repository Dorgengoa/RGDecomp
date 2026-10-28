/* rgp:protos */
#define RGP_SELF_CharaMgrPoolReset_3a9370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern s32 D_004837E8;
extern s32 D_004837EC;
extern s32 D_004837F0;

typedef struct Obj_FUN_003a9370 {
    u8 pad000[0x8];
    s32 m08;         /* +0x8 */
} Obj_FUN_003a9370;

void CharaMgrPoolReset_3a9370(Obj_FUN_003a9370 *o)
{
    D_004837E8 = 0;
    D_004837EC = 0;
    D_004837F0 = 0;
    o->m08 = 0;
}
