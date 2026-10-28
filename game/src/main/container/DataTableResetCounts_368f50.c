/* rgp:protos */
#define RGP_SELF_DataTableResetCounts_368f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00368f50 {
    u8 pad000[0x7C];
    s16 m7C;         /* +0x7C */
    s16 m7E;         /* +0x7E */
    u8 pad080[0x2];
    s16 m82;         /* +0x82 */
    s32 m84;         /* +0x84 */
} Obj_FUN_00368f50;

void DataTableResetCounts_368f50(Obj_FUN_00368f50 *o)
{
    o->m7C = 0;
    o->m7E = -1;
    o->m82 = 0;
    o->m84 = 0;
}
