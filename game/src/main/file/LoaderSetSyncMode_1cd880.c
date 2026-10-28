/* rgp:protos */
#define RGP_SELF_LoaderSetSyncMode_1cd880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001cd880 {
    u8 pad000[0xC];
    u8 m0C;         /* +0xC */
    u8 m0D;         /* +0xD */
} Obj_FUN_001cd880;

void LoaderSetSyncMode_1cd880(Obj_FUN_001cd880 *o, u8 p0, u8 p1)
{
    o->m0C = p0;
    o->m0D = p1;
}
