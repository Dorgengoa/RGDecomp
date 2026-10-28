/* rgp:protos */
#define RGP_SELF_TimeOfDayPhaseWeights_18d630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern f32 D_0047E06C;
extern f32 D_0047E070;
extern f32 D_0047E074;
extern f32 D_0047E078;
extern f32 D_0047E07C;

void TimeOfDayPhaseWeights_18d630(s32 arg0, f32 *arg1)
{
    f32 t;
    f32 v;
    f32 d;
    s32 i;
    s32 r;
    s32 next;

    t = TimeOfDayGetHour_18d920(arg0);
    v = 0.0f;
    for (i = 0; i < 4; i++) {
        ((s32 *)arg1)[i] = 0;
    }
    r = TimeOfDayPhase_18d890(arg0);
    next = (r + 1) % 4;
    switch (r) {
    case 3:
        d = D_0047E074 - D_0047E06C;
        if (!(t <= d)) {
            v = (t - d) / D_0047E06C;
        }
        break;
    case 0:
        d = D_0047E078 - D_0047E06C;
        if (!(t <= d)) {
            v = (t - d) / D_0047E06C;
        }
        break;
    case 1:
        d = D_0047E07C - D_0047E06C;
        if (!(t <= d)) {
            v = (t - d) / D_0047E06C;
        }
        break;
    case 2:
        if (t < D_0047E070) {
            d = D_0047E070 - D_0047E06C;
            if (!(t <= d)) {
                v = (t - d) / D_0047E06C;
            }
        }
        break;
    }
    arg1[r] = 1.0f - v;
    arg1[next] = v;
}
