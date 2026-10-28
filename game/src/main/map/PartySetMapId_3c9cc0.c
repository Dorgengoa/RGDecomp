/* rgp:protos */
#define RGP_SELF_PartySetMapId_3c9cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003c9cc0 {
    u8 pad000[0x30];
    s16 m30;         /* +0x30 */
} Obj_FUN_003c9cc0;

s32 PartySetMapId_3c9cc0(Obj_FUN_003c9cc0 *o, s32 p1)
{
    o->m30 = p1;
    return 1;
}
