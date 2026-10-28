/* rgp:protos */
#define RGP_SELF_normal_TransMenuQuickOpenState_515da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8    normal_D_00527EE0[0x10];
extern u8    normal_D_00527F10[0x10];

extern void *D_004846E8;   /* gp - 0xA88 */
extern s32   D_00484700;   /* gp - 0xA70 */
extern s16   D_00484750;   /* gp - 0xA20 */
extern void *D_0048478C;   /* gp - 0x9E4 */
extern s8    D_00484798;   /* gp - 0x9D8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransMenuQuickOpenState_515da0(void *a, s32 b)
{
    s32 i;

    if (b != 0) {
        normal_TransMenuOpenState_515f10(a, 1);
        UiEntryListSelectByTag_28ea90(normal_D_00527EE0, 0x10, 0);
        D_00484798 = 0;
    }
    switch (D_00484798) {
    case 0:
        if (D_00484750 != 0) {
            LoadHandleArrayReset_28b160(D_0048478C, 9);
            MenuTranstempRelease_206230();
            MenuTranstempInit_206240();
            normal_TransMenuSubResRequest_518040(0);
            normal_TransMenuTopRowsSlideOut_515b20(1);
            UiSetWidgetsVisibleById_291110(D_004846E8, 0x7531, 1, 1);
            UiSetWidgetAlpha_2907a0(D_004846E8, 0x7531, 1.0f);
            UiSetWidgetAlpha_2907a0(D_004846E8, 0x75D1, 0.0f);
            normal_TransMenuPickIconCopy_515950(0);
            UiSetWidgetPos_290f60(D_004846E8, 0x7553, 0x30, 0xF);
            for (i = 0; i < 4; i++) {
                UiSetWidgetAlpha_2907a0(D_004846E8, i + 0x754F, 0.0f);
            }
            D_00484798 = D_00484798 + 1;
        }
        break;
    case 1:
        if (normal_TransMenuSubResPoll_517d40() != 0) {
            D_00484798 = D_00484798 + 1;
        }
        break;
    case 2:
        ScreenFadeBlockFadeIn_178310(normal_D_00527F10, 0x14);
        StateMachineSetState_28ede0(&D_00484700, 5, 1);
        break;
    }
    return 1;
}
