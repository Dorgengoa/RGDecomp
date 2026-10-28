/* rgp:protos */
#define RGP_SELF_MapIdListEntryInit_1e5fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_001e5fa0 {
    s16 m00;         /* +0x0 */
    s16 m02;         /* +0x2 */
    s32 m04;         /* +0x4 */
} Obj_FUN_001e5fa0;

void MapIdListEntryInit_1e5fa0(Obj_FUN_001e5fa0 *o)
{
    o->m00 = -1;
    o->m02 = 0;
    o->m04 = 0;
}
