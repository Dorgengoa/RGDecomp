/* rgp:protos */
#define RGP_SELF_SaveResultSetFromDataError_374070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 SaveResultSetFromDataError_374070(void *arg0)
{
    s32 temp_16;
    void *temp_3;
    s32 idx;

    temp_16 = *(s32 *)((u8 *)GetGameData_1fede0() + 0x5C);
    switch (temp_16) {
    case 0:
    case 10:
        break;
    case 9:
        *((s16 *)SaveMgrGetResult_375a00(arg0)) = 1;
        idx = *(s16 *)((u8 *)arg0 + 0x4EE);
        temp_3 = (u8 *)arg0 + 0x78;
        if (temp_3 != NULL) {
            SaveSlotEntrySetBadData_3760d0((u8 *)temp_3 + idx * 2);
        }
        break;
    default:
        *((s16 *)SaveMgrGetResult_375a00(arg0)) = 2;
        break;
    }
    return temp_16;
}
