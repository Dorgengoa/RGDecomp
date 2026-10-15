#include "types.h"
#pragma opt_common_subs off
void MemStackAlign64_14d8e0(s32);                             /* extern */
s32 MemStackPeekQw_14d9d0(s32, s32);                         /* extern */
s32 ResidentFileReadLocalizedMaybe_1c2860(s32, s32, s32 *);                  /* extern */
s32 TexGroupLoadFromBuf_202ad0(s32, s32, s32, s32, s32, s32, s32); /* extern */

s32 TexGroupLoadFromResident_202c80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp7C;
    s32 temp_2;

    if ((arg0 == 0) || (arg1 == 0)) return -1;
    MemStackAlign64_14d8e0(arg1);
    temp_2 = MemStackPeekQw_14d9d0(arg1, 1);
    if (temp_2 == 0) return -1;
    sp7C = 0;
    if (!(ResidentFileReadLocalizedMaybe_1c2860(arg0, temp_2, &sp7C) & 0xFF) || sp7C <= 0) return -1;
    return TexGroupLoadFromBuf_202ad0(temp_2, sp7C, arg1, arg2, arg3, arg4, 1);
}
