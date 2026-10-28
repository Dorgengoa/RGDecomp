/* rgp:protos */
#define RGP_SELF_EvCmdBgmPlayNow_244c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct E8 { u8 b[8]; };
/*rgp*/
/*rgp*/
s32 EvCmdBgmPlayNow_244c90(struct E8 *p0, s32 p1)
{
    s32 r0;
    s32 flag;
    if (p1 <= 2) {
        goto body;
    }
    return 0;
body:
    flag = 1;
    r0 = ScriptGetInt_2490f0(p0++);
    if (p1 >= 2) {
        flag = ScriptGetInt_2490f0(p0);
    }
    BgmPlayNowMaybe_207530(r0, flag != 0);
    return 1;
}
