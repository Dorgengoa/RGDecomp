/* rgp:protos */
#define RGP_SELF_ScreenFadeSetOverlayZoomMaybe_1cf530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Field setter.  The assignments are in the order the reference stores
   them: mwcc emits a run of independent stores in source order and sinks
   the last into the `jr` delay slot, so the order is readable off the
   listing rather than guessed. */

typedef struct Obj_FUN_001cf530 {
    u8 pad000[0x59BC];
    f32 m59BC;         /* +0x59BC */
    f32 m59C0;         /* +0x59C0 */
    f32 m59C4;         /* +0x59C4 */
} Obj_FUN_001cf530;

void ScreenFadeSetOverlayZoomMaybe_1cf530(Obj_FUN_001cf530 *o, f32 f0, f32 f1, f32 f2)
{
    o->m59BC = f0;
    o->m59C0 = f1;
    o->m59C4 = f2;
}
