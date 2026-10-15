#include "types.h"

extern f32 D_0047E070, D_0047E074, D_0047E078, D_0047E07C;
extern f32 TimeOfDayGetHour_18d920(void);

s32 TimeOfDayPhase_18d890(void)
{
    f32 r;
    s32 v;

    r = TimeOfDayGetHour_18d920();
    v = 2;
    if (r >= D_0047E070) {
        if (r < D_0047E074) {
            v = 3;
        }
    }
    if (r >= D_0047E074) {
        if (r < D_0047E078) {
            v = 0;
        }
    }
    if (r >= D_0047E078) {
        if (r < D_0047E07C) {
            v = 1;
        }
    }
    return v;
}
