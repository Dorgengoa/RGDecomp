#include "types.h"

struct T272330 { u8 pad000[0x1D74]; s16 f1D74[1]; };

void MesWinAddLineWidthUnchecked_272330(struct T272330 *p, s32 i, s32 d)
{
    p->f1D74[i] += (s16)d;
}
