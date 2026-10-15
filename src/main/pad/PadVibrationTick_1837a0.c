#include "types.h"

extern void *D_00481230;
extern void PadUpdateVibration_184250(void *, s32);

void PadVibrationTick_1837a0(void)
{
    void *p;

    p = D_00481230;
    if (p != 0) {
        PadUpdateVibration_184250(p, 1);
    }
}
