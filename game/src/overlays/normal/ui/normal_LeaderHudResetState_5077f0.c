/* rgp:protos */
#define RGP_SELF_normal_LeaderHudResetState_5077f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005077F0 -- tear down the 0x14-byte record at normal_D_00527C20.  The
 * record is OVERLAY data reached absolutely, so it must be declared as an
 * incomplete array to stay OUT of small data. */
extern s32   normal_D_00527C20[];
extern void *D_00484560;          /* gp - 0xC10 */
extern s32   D_0048457C;          /* gp - 0xBF4 */
extern void memset(void *p, s32 v, s32 n);
/*rgp*/
extern s32 normal_LeaderHudResetState_5077f0(void *p, s32 b);
s32 normal_LeaderHudResetState_5077f0(void *p, s32 b)
{
    if (b != 0) {
        memset(normal_D_00527C20, 0, 0x14);
        normal_D_00527C20[0] = -1;
        StateMachineSetState_28ede0(D_00484560, 0x59DB, 0);
        D_0048457C = 0;
    }
    return 1;
}
