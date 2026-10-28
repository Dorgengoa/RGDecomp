/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuStep_5211f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005211F0 -- the leave path.  The `addiu $6,$0,1` is ONE constant
 * shared by both equality compares and by the third argument of func_28EDE0.
 * func_2913A0 is called twice on the SAME gp pointer, reloaded between the
 * calls. */

extern s8    D_0048493C;          /* gp - 0x834  */
extern s8    D_00484940;          /* gp - 0x830  */
extern s8    D_00480788;          /* gp - 0x49E8 */
extern s32   D_00484928;          /* gp - 0x848  */
extern void *D_00484920;          /* gp - 0x850  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_ThinkMenuStep_5211f0(void)
{
    void *p;

    if (D_0048493C != 0) {
        if (D_00484940 == 1 && D_00480788 == 1) {
            D_0048493C = 2;
            D_00480788 = 0;
            StateMachineSetState_28ede0(&D_00484928, 0x7531, 1);
        }
        normal_ThinkMenuResPoll_5217e0();
        p = GetDrawCtxNameTable_15de40();
        if (p != 0) {
            TexGroupUpdateAnim_157ca0(p, 0x32E, 2.5f);
        }
        UiUpdateWidgets_2913a0(D_00484920);
        UiUpdateWidgets_2913a0(D_00484920);
        StateMachineUpdate_28ed70(&D_00484928);
    }
}
