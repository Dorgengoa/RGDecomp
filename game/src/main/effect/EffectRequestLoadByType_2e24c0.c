/* rgp:protos */
#define RGP_SELF_EffectRequestLoadByType_2e24c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void EffectRequestLoadByType_2e24c0(void *arg0, s32 arg1, s32 arg2, s32 type, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8)
{
    switch (type) {
    case 1:
        EffectResRequestEfp_2e21a0(arg0, arg1, arg2, arg5, arg6, arg8);
        return;
    case 2:
        EffectRequestLoadChrChecked_2e1bf0(arg0, arg1, arg2, arg4, arg5, arg6, arg7, arg8);
        return;
    case 3:
        EffectRequestLoadImgChecked_2e1a40(arg0, arg1, arg2, arg4, arg5, arg6, arg7, arg8);
        return;
    default:
        *(u16 *)((u8 *)arg0 + 0x0) = 0;
        *(s32 *)((u8 *)arg0 + 0x4) = -1;
        *(s32 *)((u8 *)arg0 + 0x8) = 0;
        *(s32 *)((u8 *)arg0 + 0xC) = -1;
        return;
    }
}
