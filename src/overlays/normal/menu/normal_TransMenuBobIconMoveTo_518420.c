#include "types.h"
/* normal 0x00518420 -- shop totals, buy side: the three arguments pass STRAIGHT
 * THROUGH (there is no argument setup at all before the first call). */
extern void normal_TransMenuBobIconPlace_518480(void);
extern void normal_TransMenuBobIconSetPos_518560(s32 a, s32 b, s32 c);
extern void normal_TransMenuBobIconMoveTo_518420(s32 a, s32 b, s32 c);
void normal_TransMenuBobIconMoveTo_518420(s32 a, s32 b, s32 c)
{
    normal_TransMenuBobIconSetPos_518560(a, b, c);
    normal_TransMenuBobIconPlace_518480();
}
