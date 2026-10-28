/* rgp:protos */
#define RGP_SELF_MesWinSetTextSpeed_277580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void MesWinSetTextSpeed_277580(void *p, f32 v)
{
    f32 z;

    z = 0.0f;
    if (v != z) {
        MesWinSetCharSpeed_277630(p, (float)v);
        MesWinSetInstant_277610(p, 0);
        MesWinSetFlush_2775f0(p, 0);
    } else {
        MesWinSetInstant_277610(p, 1);
    }
}
