#include "types.h"
typedef struct I19F1D0 { u8 pad000[0x34]; s32 m34; s32 m38; s32 m3C; } I19F1D0;
s32 EffDefCmdEmitterObjectEnd_19f1d0(s32 a, s32 b, I19F1D0 **c)
{
    I19F1D0 *q;

    q = *c;
    q->m34 = 0;
    q->m38 = 0;
    q->m3C = 0;
    return 1;
}
