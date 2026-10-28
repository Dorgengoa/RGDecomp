/* rgp:protos */
#define RGP_SELF_FieldHudMissionBannerHideMaybe_204100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern void func_4F2350(void *);

s32 FieldHudMissionBannerHideMaybe_204100(void)
{
    return (func_4F2350(D_00527020), (s32)0);
}
