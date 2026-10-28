/* rgp:protos */
#define RGP_SELF_normal_TransMenuBobTimerGet_518550 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518550 -- gp float getter. */

extern f32 D_00484790;   /* gp - 0x9E0 */

f32 normal_TransMenuBobTimerGet_518550(void)
{
    return D_00484790;
}
