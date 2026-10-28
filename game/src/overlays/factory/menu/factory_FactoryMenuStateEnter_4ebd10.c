/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuStateEnter_4ebd10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Scene {
    u8    pad00[0x64];
    void *f64;
    u8    pad68[0x4];
    void *f6C;
} Scene;

extern s32    D_00480828;                       /* _gp - 0x4948 */
extern u8     D_00480800;                       /* _gp - 0x4970 */
extern Scene *D_00484A44;                       /* _gp - 0x72C  */
extern s32    D_00484A8C;                       /* _gp - 0x6E4  */
extern s32    D_00484A90;                       /* _gp - 0x6E0  */
extern u8     D_00484A94;                       /* _gp - 0x6DC  */
extern f32    D_0047D510;                       /* _gp - 0x7C60 */
extern f32    D_0047D520;                       /* _gp - 0x7C50 */

typedef struct Owner {
    u8    pad00[0x8];
    void *f8;
} Owner;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryMenuStateEnter_4ebd10(s32 unused, s32 start)
{
    s32 x;
    s32 y;
    Owner *o;

    if (start != 0) {
        D_00480828 = -1;
        D_00480800 = 1;
    }
    o = ((Owner *)GetGameData_1fede0());
    if (o == 0) {
        return 1;
    }
    switch (D_00480828) {
    case -1:
        if (WorldDataMgrNoRequestPending_3eef10(o->f8) != 0) {
            UiSetWidgetPos_290f60(D_00484A44->f64, 1, -0x30, -0xF);
            UiMoveWidgetUniform_290f50(D_00484A44->f64, 1, -1, -1, D_0047D510, 0);
            UiFadeWidgetAlpha_290690(D_00484A44->f64, 1, 1.0f, D_0047D520, 0.0f);
            factory_FactoryMenuReset_4f10f0(D_00484A44);
            D_00480828 = 0;
            D_00484A94 = 0;
            D_00484A8C = 0;
            D_00484A90 = 0;
        }
        break;
    case 0:
        UiGetWidgetPos_2910a0(D_00484A44->f64, 1, &x, &y);
        if (x == -1 && y == -1) {
            factory_FactoryMenuRowsSlideIn_4eb3c0();
            D_00480828 = 1;
        }
        /* fallthrough */
    case 1:
        UiGetWidgetPos_2910a0(D_00484A44->f64, 0xA, &x, &y);
        if (x == 0 && y == 0) {
            StateMachineSetState_28ede0(D_00484A44->f6C, 0x88CC, 0);
            D_00480828 = -1;
        }
        break;
    }
    return 1;
}
