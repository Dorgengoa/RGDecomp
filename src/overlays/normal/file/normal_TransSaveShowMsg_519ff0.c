#include "types.h"
/* normal 0x00519FF0 -- leaf tail call, gp handle in slot two. */

extern void *D_00484714;          /* gp - 0xA5C */

extern void func_376B60(s32 a, void *b, s32 c, s32 d);

void normal_TransSaveShowMsg_519ff0(s32 a)
{
    func_376B60(a, D_00484714, 0, -1);
}
