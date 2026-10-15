#include "types.h"

/* title.bin overlay, 0x004EEB60 -- tail call into main with a gp-relative argument */

extern s32 D_00484174;
extern void func_376B60(s32 a, s32 b, s32 c, s32 d);

void title_TitleLoadShowMsg_4eeb60(s32 a)
{
    func_376B60(a, D_00484174, 0, -1);
}
