/* rgp:protos */
#define RGP_SELF_CharaEventLogKeyReset_3a6c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003a6c20 {
    s16 m00;         /* +0x0 */
    u8 m02;         /* +0x2 */
    u8 m03;         /* +0x3 */
} Obj_FUN_003a6c20;

void CharaEventLogKeyReset_3a6c20(Obj_FUN_003a6c20 *o)
{
    o->m00 = -1;
    o->m02 = 0;
    o->m03 = 0;
}
