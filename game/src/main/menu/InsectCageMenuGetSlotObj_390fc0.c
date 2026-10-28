/* rgp:protos */
#define RGP_SELF_InsectCageMenuGetSlotObj_390fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004E94A0[5];

s32 InsectCageMenuGetSlotObj_390fc0(s32 i)
{
    if (i < 0 || i >= 5) return 0;
    return D_004E94A0[i];
}
