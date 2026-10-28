/* rgp:protos */
#define RGP_SELF_MesWinSetLastGlyphPos_272320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00272320 {
    u8 pad000[0x7C];
    s32 m7C;         /* +0x7C */
    s32 m80;         /* +0x80 */
} Obj_FUN_00272320;

void MesWinSetLastGlyphPos_272320(Obj_FUN_00272320 *o, s32 p0, s32 p1)
{
    o->m7C = p0;
    o->m80 = p1;
}
