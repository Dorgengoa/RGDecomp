#include "types.h"

extern u8    D_00527EE0[0x10];
extern u8    D_00527F10[0x10];

extern void *D_004846E8;   /* gp - 0xA88 */
extern s32   D_00484700;   /* gp - 0xA70 */
extern s16   D_00484750;   /* gp - 0xA20 */
extern void *D_0048478C;   /* gp - 0x9E4 */
extern s8    D_00484798;   /* gp - 0x9D8 */

extern void func_178310(void *p, s32 n);
extern void func_206230(void);
extern void func_206240(void);
extern void func_28B160(void *p, s32 n);
extern void func_28EA90(void *w, s32 id, s32 a);
extern void func_28EDE0(void *w, s32 id, s32 a);
extern void func_2907A0(void *w, u16 id, f32 t);
extern void func_290F60(void *w, u16 id, s32 a, s32 b);
extern void func_291110(void *w, u16 id, s32 a, s32 b);
extern void normal_TransMenuPickIconCopy_515950(s32 a);
extern void normal_TransMenuTopRowsSlideOut_515b20(s32 a);
extern void normal_TransMenuOpenState_515f10(void *p, s32 a);
extern s32  normal_TransMenuSubResPoll_517d40(void);
extern s32 normal_TransMenuSubResRequest_518040(s32 a);

s32 normal_TransMenuQuickOpenState_515da0(void *a, s32 b)
{
    s32 i;

    if (b != 0) {
        normal_TransMenuOpenState_515f10(a, 1);
        func_28EA90(D_00527EE0, 0x10, 0);
        D_00484798 = 0;
    }
    switch (D_00484798) {
    case 0:
        if (D_00484750 != 0) {
            func_28B160(D_0048478C, 9);
            func_206230();
            func_206240();
            normal_TransMenuSubResRequest_518040(0);
            normal_TransMenuTopRowsSlideOut_515b20(1);
            func_291110(D_004846E8, 0x7531, 1, 1);
            func_2907A0(D_004846E8, 0x7531, 1.0f);
            func_2907A0(D_004846E8, 0x75D1, 0.0f);
            normal_TransMenuPickIconCopy_515950(0);
            func_290F60(D_004846E8, 0x7553, 0x30, 0xF);
            for (i = 0; i < 4; i++) {
                func_2907A0(D_004846E8, i + 0x754F, 0.0f);
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
        func_178310(D_00527F10, 0x14);
        func_28EDE0(&D_00484700, 5, 1);
        break;
    }
    return 1;
}
