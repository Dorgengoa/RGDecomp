/* rgp:protos */
#define RGP_SELF_ScreenMarkerSetFlag_31bf70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
void ScreenMarkerSetFlag_31bf70(u8 *base, s32 i, u8 v)
{
    if (i >= 0x20) i = 0x1F;
    *(u8 *)(i + (s32)base + 0x80) = v;
}
