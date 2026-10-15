#include "types.h"

extern s32 CdDatArchiveOpen_183110(u8 *, s8 *, s32);
extern s32 D_004811CC;
extern s32 D_004811E0;
extern u8 D_00495FB0[];

void CdDatArchivesOpenOnLayer_182dc0(s32 arg0, s32 arg1) {
    s32 var_16;
    s8 *temp_5;

    if (arg0 < 0 || arg0 > 1) {
        return;
    }
    D_004811E0 = arg0;
    var_16 = 0;
    D_004811CC = 0;
    do {
        temp_5 = (s8 *)(arg1 + (var_16 << 5));
        if (*temp_5 != 0) {
            CdDatArchiveOpen_183110(D_00495FB0 + (var_16 * 0xC), temp_5, *(s32 *)((u8 *)(arg1 + (var_16 * 4)) + 0x40));
            D_004811CC += 1;
        }
        var_16 += 1;
    } while (var_16 < 2);
}
