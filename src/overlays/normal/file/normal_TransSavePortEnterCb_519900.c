#include "types.h"
/* normal 0x00519900 -- scene teardown. */
typedef struct Obj { u8 pad00[0x12]; s16 f12; } Obj;

extern u8    D_00484804;
extern void *D_004847D8;
extern void  func_37B460(s32 a);
extern void  normal_TransSavePortSelectDraw_519e80(s32 a);
extern void  normal_TransSaveHighlightOption_519e70(s32 a);
extern void  func_37B800(s32 a);
extern void  normal_TransSaveShowMsg_519ff0(s32 a);
extern void  normal_TransSavePortCursorBob_5187c0(s32 a, s32 b, s32 c);
extern void  func_376B10(s32 a);
extern void  func_28EB10(void *a, s32 b);
extern void *func_28EC30(void *a, s32 b);
extern void  func_3777A0(void *a, s32 b, s32 c);

s32 normal_TransSavePortEnterCb_519900(Obj *p)
{
    D_00484804 = 0;
    func_37B460(0x75A2);
    normal_TransSavePortSelectDraw_519e80(-1);
    normal_TransSaveHighlightOption_519e70(-1);
    func_37B800(-1);
    normal_TransSaveShowMsg_519ff0(0x18);
    normal_TransSavePortCursorBob_5187c0(p->f12, 1, 1);
    func_376B10(0);
    func_28EB10(D_004847D8, 4);
    func_3777A0(func_28EC30(D_004847D8, 4), 0x75A1, 0);
    return 1;
}
