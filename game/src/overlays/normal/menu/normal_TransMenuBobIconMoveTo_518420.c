/* rgp:protos */
#define RGP_SELF_normal_TransMenuBobIconMoveTo_518420 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518420 -- shop totals, buy side: the three arguments pass STRAIGHT
 * THROUGH (there is no argument setup at all before the first call). */
/*rgp*/
/*rgp*/
extern void normal_TransMenuBobIconMoveTo_518420(s32 a, s32 b, s32 c);
void normal_TransMenuBobIconMoveTo_518420(s32 a, s32 b, s32 c)
{
    normal_TransMenuBobIconSetPos_518560(a, b, c);
    normal_TransMenuBobIconPlace_518480();
}
