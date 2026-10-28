/* rgp:protos */
#define RGP_SELF_InsectCageMsgEntryReset_3848d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_003848d0 {
    u8 pad000[0x80];
    s16 m80;         /* +0x80 */
    u8 m82;         /* +0x82 */
    u8 pad083[0x81];
    s32 m104;         /* +0x104 */
} Obj_FUN_003848d0;

void InsectCageMsgEntryReset_3848d0(Obj_FUN_003848d0 *o)
{
    o->m80 = -1;
    o->m82 = 0;
    o->m104 = 0;
}
