/* rgp:protos */
#define RGP_SELF_PadVibrationTick_1837a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00481230;
/*rgp*/

void PadVibrationTick_1837a0(void)
{
    void *p;

    p = D_00481230;
    if (p != 0) {
        PadUpdateVibration_184250(p, 1);
    }
}
