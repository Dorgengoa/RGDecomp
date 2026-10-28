/* rgp:protos */
#define RGP_SELF_EntrySetOrigin_323c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00323c00 {
    u8 pad000[0x8];
    f32 m08;         /* +0x8 */
    f32 m0C;         /* +0xC */
} Obj_FUN_00323c00;

void EntrySetOrigin_323c00(Obj_FUN_00323c00 *o, f32 f0, f32 f1)
{
    o->m08 = f0;
    o->m0C = f1;
}
