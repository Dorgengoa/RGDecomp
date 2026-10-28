/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuGridState_520ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00520CA0 */

typedef struct Sel { u8 pad00[0x14]; s16 f14; s16 f16; } Sel;
typedef struct Cur { u8 pad00[0x10]; s16 f10; s16 f12; } Cur;
typedef struct Act { u8 pad00[0x18]; void *f18; } Act;
typedef struct Cfg { u8 pad00[0x11]; s8 f11; } Cfg;

extern u8        normal_D_00528030[];
extern u8        normal_D_00528060[];
extern s16 normal_D_00526090[];
extern u8  D_004B2570[];

extern s16   D_00480798[4];       /* gp - 0x49D8, declared short to stay in small data */
extern s32   D_00484948;          /* gp - 0x828  */
extern s32   D_00484928;          /* gp - 0x848  */
extern Cfg  *D_00484934;          /* gp - 0x83C  */
extern void *D_00484920;          /* gp - 0x850  */
extern s32   D_0048494C;          /* gp - 0x824  */
extern s32   D_00484950;          /* gp - 0x820  */

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

s32 normal_ThinkMenuGridState_520ca0(void *a, s32 b)
{
    s16 b2[8] __attribute__((aligned(16)));
    s16 b1[16] __attribute__((aligned(16)));
    const s16 *src1;
    s16 *dst1;
    const s16 *src2;
    s16 *dst2;
    s32 i;
    Sel *sel;
    Cur *cur;
    Act *act;
    s32 st;

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(normal_D_00528030, 0x7531, 0);
        sel = ((Sel *)UiEntryListFindByTag_28ea40(normal_D_00528030, 0x7531));
        src1 = normal_D_00526090;
        dst1 = b1;
        for (i = 9; i > 0; i--) {
            *dst1 = *src1;
            src1++;
            dst1++;
        }
        src2 = D_00480798;
        dst2 = b2;
        for (i = 5; i > 0; i--) {
            *dst2 = *src2;
            src2++;
            dst2++;
        }
        UiSelFrameSetRect_28db40(normal_D_00528060, 0x753B, b1[sel->f14], b2[sel->f16],
                    0x2A, 0x30, 0x46, 0x4B);
    }
    normal_ThinkMenuPromptScrollStep_521660(GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0()));
    if (D_00484948 == 0) {
        StateMachineSetState_28ede0(&D_00484928, 0x7533, 1);
    }
    st = MenuGridCursorInput_28e170(normal_D_00528030, D_004B2570, 6, 0);
    cur = ((Cur *)UiEntryListGetCurrentData_28ec60(normal_D_00528030));
    if (st == 1) {
        act = ((Act *)GetGameData_1fede0());
        if (((s32)InvFindByCategoryIndex_3c86e0(act->f18, 0, D_00484934->f11, cur->f10, cur->f12, 0)) != 0) {
            UiFadeWidgetAlpha_290690(D_00484920, 0x7544, 0.0f, -0.1f, -1.0f);
            StateMachineSetState_28ede0(&D_00484928, 0x7534, 0);
        }
    } else if (st == 2) {
        D_00484948 = 1;
        D_0048494C = -1;
        D_00484950 = -1;
        StateMachineSetState_28ede0(&D_00484928, 0x7533, 1);
    }
    return 1;
}
