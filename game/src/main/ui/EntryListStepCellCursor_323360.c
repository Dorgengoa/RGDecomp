/* rgp:protos */
#define RGP_SELF_EntryListStepCellCursor_323360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00323360 {
    u8 pad000[0x1E];
    s16 m1E;         /* +0x1E */
} Obj_FUN_00323360;

void EntryListStepCellCursor_323360(Obj_FUN_00323360 *o)
{
    o->m1E = (o->m1E + 1);
}
