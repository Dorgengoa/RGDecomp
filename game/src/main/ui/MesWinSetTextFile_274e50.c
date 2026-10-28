/* rgp:protos */
#define RGP_SELF_MesWinSetTextFile_274e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00274e50 {
    u8 pad000[0x1954];
    s32 m1954;         /* +0x1954 */
    s32 m1958;         /* +0x1958 */
} Obj_FUN_00274e50;

void MesWinSetTextFile_274e50(Obj_FUN_00274e50 *o, s32 p0, s32 p1)
{
    o->m1954 = p0;
    o->m1958 = p1;
}
