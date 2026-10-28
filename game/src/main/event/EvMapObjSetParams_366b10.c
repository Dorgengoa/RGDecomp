/* rgp:protos */
#define RGP_SELF_EvMapObjSetParams_366b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_00366b10 {
    u8 pad000[0x324];
    f32 m324;         /* +0x324 */
    f32 m328;         /* +0x328 */
    s16 m32C;         /* +0x32C */
    s16 m32E;         /* +0x32E */
} Obj_FUN_00366b10;

void EvMapObjSetParams_366b10(Obj_FUN_00366b10 *o, s16 p0, s16 p1, f32 f0, f32 f1)
{
    o->m324 = f0;
    o->m328 = f1;
    o->m32C = p0;
    o->m32E = p1;
}
