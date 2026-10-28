/* rgp:protos */
#define RGP_SELF_SaveDataClearError_3e6350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_003e6350 {
    u8 pad000[0x5C];
    s32 m5C;         /* +0x5C */
    s32 m60;         /* +0x60 */
    s32 m64;         /* +0x64 */
} Obj_FUN_003e6350;

void SaveDataClearError_3e6350(Obj_FUN_003e6350 *o)
{
    o->m5C = 0;
    o->m60 = 0;
    o->m64 = 0;
}
