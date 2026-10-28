/* rgp:protos */
#define RGP_SELF_ScreenFadeSetOverlayMaybe_1cf540 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001cf540 {
    u8 pad000[0x59B0];
    s32 m59B0;         /* +0x59B0 */
    s32 m59B4;         /* +0x59B4 */
    s32 m59B8;         /* +0x59B8 */
} Obj_FUN_001cf540;

void ScreenFadeSetOverlayMaybe_1cf540(Obj_FUN_001cf540 *o, s32 p0, s32 p1, s32 p2)
{
    o->m59B0 = p0;
    o->m59B4 = p1;
    o->m59B8 = p2;
}
