/* rgp:protos */
#define RGP_SELF_Base58DecodeBlock_42f200 1
#include "port/game_protos.h"
#line 1
/*
Decompilation failure in function Base58DecodeBlock_42f200:

Function Base58DecodeBlock_42f200 contains no instructions. Maybe it is rodatavoid */
/* s49m: MATCH */
#include "types.h"

/*rgp*/

s32 Base58DecodeBlock_42f200(s8 *arg0, s64 *arg1)
{
    s64 sum;
    u64 mul;
    s32 i;
    s32 v;

    sum = 0;
    mul = 1;
    for (i = 0; i < 11; i++) {
        v = Base58CharIndex_42f380(arg0[i]);
        if (v < 0) {
            return 0;
        }
        sum += v * mul;
        mul *= 58;
    }
    *arg1 = sum;
    return 1;
}
