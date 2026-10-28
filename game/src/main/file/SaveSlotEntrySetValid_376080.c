/* rgp:protos */
#define RGP_SELF_SaveSlotEntrySetValid_376080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00376080 {
    u8 m00;         /* +0x0 */
    u8 m01;         /* +0x1 */
} Obj_FUN_00376080;

void SaveSlotEntrySetValid_376080(Obj_FUN_00376080 *o)
{
    o->m00 = 1;
    o->m01 = 0;
}
