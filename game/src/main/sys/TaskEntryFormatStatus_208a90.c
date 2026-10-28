/* rgp:protos */
#define RGP_SELF_TaskEntryFormatStatus_208a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 Sprintf_1343b8(s32 arg0, void *arg1, s64 arg2, s64 arg3, s32 arg4);
/*rgp*/
/*rgp*/
extern u8 D_0045C608[0x100];

s32 TaskEntryFormatStatus_208a90(s32 pad0, s32 arg1) {
    s32 *temp_2;
    s32 v1;
    s64 v2;

    temp_2 = ((s32 *)TaskEntryOfDebugItem_208c00((void *)pad0));
    if (temp_2 == NULL) {
        return 0;
    }
    v2 = (s8)(((unsigned char)TaskTestFlag_1f57a0(temp_2, 1)) ? 0x2A : 0x20);
    v1 = ((unsigned char)TaskTestFlag_1f57a0(temp_2, 0)) ? 0x2A : 0x20;
    return ((int (*)())Sprintf_1343b8)(arg1, D_0045C608, (int)((s8)v1), (int)((s8)v2), *temp_2);
}
