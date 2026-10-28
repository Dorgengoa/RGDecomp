/* rgp:protos */
#define RGP_SELF_SaveMgrInit_37bc60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004831D0;
extern s32 D_004831D8;
extern s8 D_004831F0;
extern s32 D_004831F8;
/*rgp*/

void SaveMgrInit_37bc60(s32 arg0, s32 arg1)
{
    s32 temp_2;
    s32 var_16;

    temp_2 = ((s32)GetGameData_1fede0());
    if (temp_2 != 0) {
        SlotRecordRingCreate_3e5420(temp_2, arg1, 0x32);
        var_16 = 0;
        do {
            SlotRecordRingPush_3e4f90(temp_2, var_16, 1);
            var_16 += 1;
        } while (var_16 < 0x32);
    }
    D_004831D0 = arg0;
    if (arg0 == 0 || arg1 == 0) {
        return;
    }
    SaveSysInit_375ef0(arg0, arg1);
    SaveMcInitStatus_375ea0();
    SaveSetMode_375a10(D_004831D0, 0);
    D_004831D8 = MemStackAllocQw_14d950(arg1, 0x40);
    D_004831F8 = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0(0x310, arg1)), (const void *) SaveSlotTextBufCtor_37bd60, 0, 0x100, 3));
    D_004831F0 = 0;
}
