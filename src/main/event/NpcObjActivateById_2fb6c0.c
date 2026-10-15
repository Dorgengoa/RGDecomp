#include "types.h"

extern u8 *NpcObjFindById_2fb420(u8 *, s32);

void NpcObjActivateById_2fb6c0(u8 *p, s32 n)
{
    u8 *r;

    r = NpcObjFindById_2fb420(p, n);
    if (r != 0) {
        *(s16 *)(r + 0xCC) = 1;
        *(f32 *)(r + 0xC0) = *(f32 *)(r + 0xB4);
        *(s16 *)(p + 0x224) = n;
    }
}
