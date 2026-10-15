#include "types.h"
typedef unsigned __int128 u128;
void VecAdd_13be20(void *a, void *b, void *c);
void CameraSetAtOffset_177410(u8 *p, u128 *src)
{
    *(u128 *)(p + 0xD0) = *src;
    VecAdd_13be20(p + 0xE0, p + 0xD0, p + 0x120);
}
