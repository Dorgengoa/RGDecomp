#include "types.h"
typedef unsigned __int128 u128;

s32 MeshPktWriteOffsetMaybe_14ab30(s32 p0, u32 *p1, u128 *p2)
{
    *(u128 *)p1 = 0;
    p1[0] = 0x60000001;
    p1[2] = 0x1000101;
    p1[3] = 0x6C010058;
    *(u128 *)((u8 *)p1 + 0x10) = *p2;
    return 2;
}
