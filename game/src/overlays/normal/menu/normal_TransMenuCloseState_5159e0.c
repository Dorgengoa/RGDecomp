/* rgp:protos */
#define RGP_SELF_normal_TransMenuCloseState_5159e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005159E0 -- the party-menu per-frame poll.  $4 is never read (the
 * f(void*, s32) handler family); the guard is on the second argument. */

typedef struct Act {
    u8  pad000[0x518];
    f32 f518;
} Act;

extern void *D_004846E8;          /* gp - 0xA88 */
extern s16   D_004806C8;          /* gp - 0x4AA8 */
extern s16   D_0048479C;          /* gp - 0x9D4 */
extern s8    D_00484748;          /* gp - 0xA28 */
extern s8    D_0048472C;          /* gp - 0xA44 */
extern f32   D_0047DA08;          /* gp - 0x7768 */
extern f32   D_0047DA14;          /* gp - 0x775C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransMenuCloseState_5159e0(void *a, s32 b)
{
    Act *p;
    f32 t;
    s32 x;
    s32 y;

    p = ((Act *)GetMinimapMgr_201a70());
    if (b != 0) {
        if (p != 0) {
            MinimapMgrFadeOutStart_321e60(p, 15.0f);
        }
        UiFadeWidgetAlpha_290690(D_004846E8, 0x75D1, 0.0f, D_0047DA08, -1.0f);
        D_004806C8 = 2;
        D_0048479C = 0;
        normal_TransMenuTopRowsSlideOut_515b20(0);
        UiFadeWidgetAlpha_290690(D_004846E8, 0x7556, 0.0f, D_0047DA14, -1.0f);
    }
    t = 0.0f;
    if (p != 0) {
        t = p->f518;
    }
    UiGetWidgetPos_2910a0(D_004846E8, 0x753B, &x, &y);
    if (x < -0x49) {
        if (t <= 0.0f && D_0048479C == 0) {
            normal_TransMenuHeaderFadeOut_515cd0();
            D_0048479C = 1;
        }
    }
    if (UiGetWidgetAlpha_290770(D_004846E8, 0x7532) <= 0.0f) {
        D_00484748 = 0;
        D_0048472C = 1;
    }
    return 1;
}
