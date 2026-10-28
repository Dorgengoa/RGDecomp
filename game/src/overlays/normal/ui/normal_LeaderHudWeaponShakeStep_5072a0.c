/* rgp:protos */
#define RGP_SELF_normal_LeaderHudWeaponShakeStep_5072a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005072A0 -- the shop camera's shake decay.  normal_D_00527C20[0] is the
 * armed flag (negative = idle), normal_D_00527C2C[0] the tick, normal_D_00527C2E[0] the limit and
 * normal_D_00527C30[0] the amplitude, which decays by 0.2f each step.  The offset sign
 * cycles on `tick % 4`: 0 -> -A, 1 -> -A/2.8, 2 -> -A/8. */

extern s32 normal_D_00527C20[4];
extern s32 normal_D_00527C24[4];
extern s32 normal_D_00527C28[4];
extern s16 normal_D_00527C2C[8];
extern s16 normal_D_00527C2E[8];
extern f32 normal_D_00527C30[4];

extern void *D_00484564;          /* gp - 0xC0C  */
extern f32   D_0047D538;          /* gp - 0x7C38 */
extern f32   D_0047D518;          /* gp - 0x7C58 */

/*rgp*/

s32 normal_LeaderHudWeaponShakeStep_5072a0(void)
{
    s32 n;
    s32 r;
    s32 t;

    if (normal_D_00527C20[0] >= 0) {
        n = 0;
        r = normal_D_00527C2C[0] % 4;
        if (r == 0) {
            n = (s32)(-normal_D_00527C30[0]);
        } else if (r == 1) {
            n = (s32)(-normal_D_00527C30[0] / D_0047D538);
        } else if (r == 2) {
            n = (s32)(-normal_D_00527C30[0] / 8.0f);
        }
        normal_D_00527C30[0] = normal_D_00527C30[0] - D_0047D518;
        UiSetWidgetPos_290f60(D_00484564, 2, normal_D_00527C24[0], normal_D_00527C28[0] + n);
        t = normal_D_00527C2C[0] + 1;
        normal_D_00527C2C[0] = t;
        if (normal_D_00527C2E[0] < (s16)t) {
            UiSetWidgetPos_290f60(D_00484564, 2, normal_D_00527C24[0], normal_D_00527C28[0]);
            normal_D_00527C20[0] = -1;
        }
    }
    return 0;
}
