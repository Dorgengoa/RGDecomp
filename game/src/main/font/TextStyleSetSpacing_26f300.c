/* rgp:protos */
#define RGP_SELF_TextStyleSetSpacing_26f300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_0026f300 {
    u8 pad000[0x1A];
    s16 m1A;         /* +0x1A */
    s16 m1C;         /* +0x1C */
} Obj_FUN_0026f300;

void TextStyleSetSpacing_26f300(Obj_FUN_0026f300 *o, s16 p0, s16 p1)
{
    o->m1A = p0;
    o->m1C = p1;
}
