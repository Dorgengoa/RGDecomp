/* rgp:protos */
#define RGP_SELF_EntryListStepChildCursor_323390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00323390 {
    u8 pad000[0x1C];
    s16 m1C;         /* +0x1C */
} Obj_FUN_00323390;

void EntryListStepChildCursor_323390(Obj_FUN_00323390 *o)
{
    o->m1C = (o->m1C + 1);
}
