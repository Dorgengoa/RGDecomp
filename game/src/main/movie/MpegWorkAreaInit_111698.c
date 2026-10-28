/* rgp:protos */
#define RGP_SELF_MpegWorkAreaInit_111698 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00111698 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    s32 m0C;         /* +0xC */
} Obj_FUN_00111698;

void MpegWorkAreaInit_111698(Obj_FUN_00111698 *o, s32 p0, s32 p1)
{
    o->m0C = p0;
    o->m04 = p1;
    o->m00 = p0;
    o->m08 = p0;
}
