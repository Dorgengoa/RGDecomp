/* rgp:protos */
#define RGP_SELF_FieldHudMissionBannerShowMaybe_204110 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern void func_4F23E0(void *, s32);

s32 FieldHudMissionBannerShowMaybe_204110(s32 a4)
{
    return (func_4F23E0(D_00527020, a4), (s32)0);
}
