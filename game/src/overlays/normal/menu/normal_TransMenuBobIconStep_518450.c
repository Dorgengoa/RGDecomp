/* rgp:protos */
#define RGP_SELF_normal_TransMenuBobIconStep_518450 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518450 -- shop totals, sell side; twin of 0x00518420. */
/*rgp*/
/*rgp*/
extern void normal_TransMenuBobIconStep_518450(s32 a, s32 b, s32 c);
void normal_TransMenuBobIconStep_518450(s32 a, s32 b, s32 c)
{
    normal_TransMenuBobTimerTick_518540();
    normal_TransMenuBobIconPlace_518480();
}
