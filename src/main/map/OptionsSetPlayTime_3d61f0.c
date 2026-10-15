#include "types.h"

struct T3D61F0 { u8 pad000[0x8]; s64 f8; };

extern s64 U64ToDouble_100370(s32);

void OptionsSetPlayTime_3d61f0(struct T3D61F0 *p, s32 b)
{
    p->f8 = U64ToDouble_100370(b);
}
