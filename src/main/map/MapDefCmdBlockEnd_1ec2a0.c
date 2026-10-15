#include "types.h"
extern void *MapAreaDefGetRecTable_1dcf20(s32 arg0);
extern void *MapBlockGetInfo_1e00b0(void *arg0);
extern s32 MapDataIsGenericMap_1e7ac0(void *arg0);
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;
extern s16 D_00481908;
extern s16 D_0048190C;
s32 MapDefCmdBlockEnd_1ec2a0(s32 arg0, s32 arg1) {
    u8 *temp_2;
    u8 *temp_4;
    u8 *temp_17;
    u8 *temp_16;
    s32 v;

    if (arg1 != 0) {
        return 0;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    temp_2 = (u8 *)MapAreaDefGetRecTable_1dcf20(D_004818FC);
    temp_4 = *(u8 **)(temp_2 + 0x44);
    if (temp_4 == NULL || *(s16 *)(temp_2 + 0x3A) <= D_00481904) {
        return 1;
    }
    temp_17 = temp_4 + D_00481904 * 0xCC;
    if (!(MapDataIsGenericMap_1e7ac0(temp_17) & 0xFF)) {
        v = *(s32 *)(temp_17 + 0x2C) & ~1;
    } else {
        v = *(s32 *)(temp_17 + 0x2C) | 1;
    }
    *(s32 *)(temp_17 + 0x2C) = v;
    temp_16 = (u8 *)MapBlockGetInfo_1e00b0(temp_17);
    *(s8 *)(temp_16 + 0x11) = D_00481908;
    D_00481908 = 0;
    D_0048190C = 0;
    D_00481904 += 1;
    return 1;
}
