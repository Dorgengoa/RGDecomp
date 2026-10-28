/* rgp:protos */
#define RGP_SELF_CharaIsGroundReadyMaybe_210850 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
extern u8 D_0045B080[0x400];
extern f32 D_0047D280;

s32 CharaIsGroundReadyMaybe_210850(void *arg0)
{
    s16 temp_3;
    u16 var_16;
    s32 r;
    f32 x;
    f32 y;
    f32 f;

    if (!(*(s32 *)((u8 *)arg0 + 0x3D8) & 4)) {
        return 0;
    }
    f = CharaGetHeightAboveGround_238380((void *)arg0);
    x = *(f32 *)D_0045B080;
    y = D_0047D280;
    if (!(f <= y * x)) {
        return 0;
    }
    temp_3 = *(s16 *)((u8 *)arg0 + 0xA2E);
    var_16 = 1;
    if ((temp_3 != 2) && (temp_3 != 3)) {
        var_16 = 0;
    }
    r = ((unsigned char)IsInBattle_288420());
    return (r & 0xFF) == (var_16 & 0xFF);
    return 0;
}
