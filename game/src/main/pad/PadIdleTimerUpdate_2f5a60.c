/* rgp:protos */
#define RGP_SELF_PadIdleTimerUpdate_2f5a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN PadIdleTimerUpdate_2f5a60.  `sw $0, %gp_rel(D_0048277C)` is the float zero
   written as a bit pattern -- 0.0f and the integer 0 are one object.
   D_004B2570 is reached with %hi/%lo, so it is an incomplete array. */

extern u8 D_004B2570[];
extern f32 D_0048277C;

/*rgp*/
/*rgp*/
/*rgp*/

void PadIdleTimerUpdate_2f5a60(void)
{
    void *o;

    if (PadAnyInput_183e80(D_004B2570) != 0) {
        D_0048277C = 0.0f;
    } else {
        o = GetCurrentScene_1f5be0();
        D_0048277C = D_0048277C + GameSceneGetTimeStep_1ceba0(o);
    }
}
