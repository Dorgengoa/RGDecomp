/* rgp:protos */
#define RGP_SELF_AiCmdFindCtxListId_2c50a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern u8 D_004DB920[0x400];
extern s32 D_004DB974[0x100];

s32 AiCmdFindCtxListId_2c50a0(s64 * arg0) {
    s32 temp_16;
    s32 temp_2;
    s32 var_6;
    s32 t;

    temp_2 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    temp_16 = (s32)arg0;
    for (var_6 = 0; var_6 < D_004DB974[0]; var_6++) {
        t = *(s32 *)(D_004DB920 + (var_6 * 4) + 0x14);
        if (t == temp_2) {
            ScriptSlotStoreIntRef_2cc900(temp_16, 1);
            return 1;
        }
    }
    ScriptSlotStoreIntRef_2cc900(temp_16, 0);
    return 1;
}
