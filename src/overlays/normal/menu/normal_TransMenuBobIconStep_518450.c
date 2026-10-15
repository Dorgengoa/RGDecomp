#include "types.h"
/* normal 0x00518450 -- shop totals, sell side; twin of 0x00518420. */
extern void normal_TransMenuBobIconPlace_518480(void);
extern void normal_TransMenuBobTimerTick_518540(s32 a, s32 b, s32 c);
extern void normal_TransMenuBobIconStep_518450(s32 a, s32 b, s32 c);
void normal_TransMenuBobIconStep_518450(s32 a, s32 b, s32 c)
{
    normal_TransMenuBobTimerTick_518540(a, b, c);
    normal_TransMenuBobIconPlace_518480();
}
