/* rgp:protos */
#define RGP_SELF_UiSelFrameReset_28db70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_0028db70 {
    u8 pad000[0x4];
    s16 m04;         /* +0x4 */
    s16 m06;         /* +0x6 */
    u8 pad008[0x4];
    s16 m0C;         /* +0xC */
} Obj_FUN_0028db70;

void UiSelFrameReset_28db70(Obj_FUN_0028db70 *o)
{
    o->m04 = 0;
    o->m06 = 0;
    o->m0C = 2;
}
