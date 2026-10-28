/* rgp:protos */
#define RGP_SELF_BitArraySetReturnOld_384360 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
s32 BitArraySetReturnOld_384360(u8 *arr, s32 bitIdx, s32 set)
{
    s32 byteIdx;
    s32 r;
    s32 old;
    u8 mask;
    s32 ret;
    u8 *p;

    byteIdx = bitIdx / 8;
    r = bitIdx % 8;
    p = arr + byteIdx;
    mask = 1 << r;
    old = *p;
    ret = (mask & old) != 0;
    if (set != 0) {
        *p = (u8)(old | mask);
    } else {
        *p = (u8)(old & (u8)~mask);
    }
    return ret;
}
