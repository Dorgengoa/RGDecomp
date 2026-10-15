#include "types.h"

extern void MesWinSetCharSpeed_277630(void *);
extern void MesWinSetInstant_277610(void *, s32);
extern void MesWinSetFlush_2775f0(void *, s32);

void MesWinSetTextSpeed_277580(void *p, f32 v)
{
    f32 z;

    z = 0.0f;
    if (v != z) {
        MesWinSetCharSpeed_277630(p);
        MesWinSetInstant_277610(p, 0);
        MesWinSetFlush_2775f0(p, 0);
    } else {
        MesWinSetInstant_277610(p, 1);
    }
}
