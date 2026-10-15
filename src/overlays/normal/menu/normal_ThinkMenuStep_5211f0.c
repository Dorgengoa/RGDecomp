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

extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  normal_ThinkMenuResPoll_5217e0(void);
extern void *func_15DE40(void);
extern void  func_157CA0(void *p, s32 id, f32 t);
extern void  func_2913A0(void *w);
extern void  func_28ED70(void *w);

void normal_ThinkMenuStep_5211f0(void)
{
    void *p;

    if (D_0048493C != 0) {
        if (D_00484940 == 1 && D_00480788 == 1) {
            D_0048493C = 2;
            D_00480788 = 0;
            func_28EDE0(&D_00484928, 0x7531, 1);
        }
        normal_ThinkMenuResPoll_5217e0();
        p = func_15DE40();
        if (p != 0) {
            func_157CA0(p, 0x32E, 2.5f);
        }
        func_2913A0(D_00484920);
        func_2913A0(D_00484920);
        func_28ED70(&D_00484928);
    }
}
