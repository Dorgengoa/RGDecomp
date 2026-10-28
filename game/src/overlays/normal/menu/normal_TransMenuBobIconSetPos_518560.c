/* rgp:protos */
#define RGP_SELF_normal_TransMenuBobIconSetPos_518560 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518560 -- publishes the shop's three pending totals. */
extern s32 D_004806D8;            /* gp - 0x4A98 */
extern s32 D_004806DC;            /* gp - 0x4A94 */
extern s32 D_004806E0;            /* gp - 0x4A90 */
extern void normal_TransMenuBobIconSetPos_518560(s32 a, s32 b, s32 c);
void normal_TransMenuBobIconSetPos_518560(s32 a, s32 b, s32 c)
{
    D_004806D8 = a;
    D_004806DC = b;
    D_004806E0 = c;
}
