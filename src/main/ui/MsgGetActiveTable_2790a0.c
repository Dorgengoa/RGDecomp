#include "types.h"

extern s32 SysGetCurMode_1c39a0(void);
extern s32 D_00484180;
extern s32 D_00481BBC;

s32 MsgGetActiveTable_2790a0(void)
{
    s32 t;

    t = SysGetCurMode_1c39a0();
    if (t == 1) {
        return D_00484180;
    }
    if (t == 0) {
        return D_00481BBC;
    }
    return 0;
}
