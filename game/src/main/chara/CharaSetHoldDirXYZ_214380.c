/* rgp:protos */
#define RGP_SELF_CharaSetHoldDirXYZ_214380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00214380 {
    u8 pad000[0x4A0];
    f32 m4A0;         /* +0x4A0 */
    f32 m4A4;         /* +0x4A4 */
    f32 m4A8;         /* +0x4A8 */
} Obj_FUN_00214380;

void CharaSetHoldDirXYZ_214380(Obj_FUN_00214380 *o, f32 f0, f32 f1, f32 f2)
{
    o->m4A0 = f0;
    o->m4A4 = f1;
    o->m4A8 = f2;
}
