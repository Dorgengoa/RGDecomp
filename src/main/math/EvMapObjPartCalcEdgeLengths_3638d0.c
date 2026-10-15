#include "types.h"

typedef unsigned __int128 u128;

typedef union Vec4 {
    u128 q;
    f32 f[4];
    s32 i[4];
} Vec4;

extern void VecSub_13be40(Vec4 *, void *, void *);
extern f32 VecLength_13d4a0(Vec4 *);

void EvMapObjPartCalcEdgeLengths_3638d0(u8 *o)
{
    Vec4 v;

    VecSub_13be40(&v, o + 0xD0, o + 0xC0);
    *(f32 *)(o + 0x120) = VecLength_13d4a0(&v);
    VecSub_13be40(&v, o + 0xE0, o + 0xD0);
    *(f32 *)(o + 0x124) = VecLength_13d4a0(&v);
    VecSub_13be40(&v, o + 0xC0, o + 0xE0);
    *(f32 *)(o + 0x128) = VecLength_13d4a0(&v);
}
