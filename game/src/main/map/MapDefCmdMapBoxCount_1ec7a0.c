/* rgp:protos */
#define RGP_SELF_MapDefCmdMapBoxCount_1ec7a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004818F8;
extern s32 D_004818FC;

s32 MapDefCmdMapBoxCount_1ec7a0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_2_2;
    void *temp_16;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    {
        temp_16 = MapAreaDefGetRecTable_1dcf20(D_004818FC);
        temp_2 = ScriptArgGetInt_1ecbe0(arg0);
        temp_2_2 = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0((temp_2 * 0x50) + 0x10, D_004818F8)), 0, 0, 0x50, temp_2));
        *(s32 *)((u8 *)temp_16 + 0x4C) = temp_2_2;
        if (temp_2_2 != 0) {
            *(s16 *)((u8 *)temp_16 + 0x3E) = temp_2;
        }
    }
    return 1;
}
