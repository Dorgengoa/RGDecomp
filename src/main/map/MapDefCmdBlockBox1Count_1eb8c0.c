#include "types.h"

extern s32 ConstructNewArray_100710(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 MemStackNew_14e1b0(s32 arg0, s32 arg1);
extern void *MapAreaDefGetRecTable_1dcf20(s32 arg0);
extern void *MapBlockGetInfo_1e00b0(s32 arg0);
extern s32 ScriptArgGetInt_1ecbe0(s32 arg0);
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;
extern s16 D_00481908;

s32 MapDefCmdBlockBox1Count_1eb8c0(s32 arg0, s32 arg1)
{
    s32 temp_2_3;
    s32 temp_2_2;
    u8 *temp_16;
    u8 *temp_2;

    if (arg1 != 1) {
        return 1;
    }
    if ((D_004818FC == 0) || (D_004818F8 == 0)) return 1;
    temp_2 = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    if ((*(s32 *) (temp_2 + 0x44) == 0) || (*(s16 *) (temp_2 + 0x3A) <= D_00481904)) return 1;
    D_00481908 = 0;
    temp_16 = MapBlockGetInfo_1e00b0(*(s32 *) (temp_2 + 0x44) + (D_00481904 * 0xCC));
    temp_2_2 = ScriptArgGetInt_1ecbe0(arg0);
    temp_2_3 = ConstructNewArray_100710(MemStackNew_14e1b0((temp_2_2 * 0x4C) + 0x10, D_004818F8), 0, 0, 0x4C, temp_2_2);
    *(s32 *) (temp_16 + 0x8) = temp_2_3;
    if (temp_2_3 == 0) {
        return 1;
    }
    *(s8 *) (temp_16 + 0x11) = temp_2_2;
    return 1;
}
