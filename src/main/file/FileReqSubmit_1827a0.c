#include "types.h"

extern void FileReadChunked_180400(s32, s32, s32);
extern s32 FileSlotOpen_180710(s8 *, s32);
extern s32 FileSlotGetSize_180d50(s32, s32 *, s32);
extern void FileSlotSeek_180ed0(s32, s32, s32);
extern void FileMakeDevicePath_181980(s8 *, s8 *);
extern void strcpy(void *, s8 *);
extern void FileSlotCloseThunk_180540(s32);

extern s32 D_0047E018;
extern s32 D_004811BC;
extern s32 D_004811C0;
extern s32 D_004811E8;
extern u8 D_00495FD0[];

static inline void Clr(s8 *p, u32 n)
{
    if (p != NULL) {
        while (n != 0) {
            *p = 0;
            n--;
            p++;
        }
    }
}

s32 FileReqSubmit_1827a0(s8 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4) {
    s8 *var_3;
    s32 var_18;
    s32 var_17;
    s32 temp_2;
    u8 *var_16;
    s8 sp180[0x100];
    s8 sp80[0x100];
    s32 sp28C;

    var_18 = arg4;
    if (arg2 != NULL) {
        *arg2 = 0;
    }
    if (arg0 == NULL) {
        return 0;
    }
    if (*arg0 == 0) {
        return 0;
    }
    Clr(sp180, 0x100);
    var_16 = D_00495FD0;
    for (var_17 = 0; var_17 < 0x20; var_17++) {
        var_16 = D_00495FD0 + (((D_004811E8 + var_17) % 32) * 0x128);
        if (*(s32 *)(var_16 + 0x120) == 0) {
            break;
        }
    }
    if (var_17 == 0x20) {
        return 0;
    }
    strcpy(var_16 + 0x8C, arg0);
    FileMakeDevicePath_181980(arg0, (s8 *)(var_16 + 0xC));
    Clr(sp80, 0x100);
    FileMakeDevicePath_181980((s8 *)(var_16 + 0xC), sp80);
    temp_2 = FileSlotOpen_180710(sp80, 0);
    *(s32 *)(var_16 + 0x124) = temp_2;
    if (temp_2 < 0) {
        return 0;
    }
    if (D_0047E018 != 0) {
        D_004811E8 = (D_004811E8 + var_17 + 1) % 32;
    } else {
        D_004811E8 = 0;
    }
    *(s32 *)(var_16 + 0x4) = 0;
    *(s32 *)(var_16 + 0x8) = 0;
    *(s32 *)(var_16 + 0x10C) = arg1;
    if (var_18 < 0) {
        var_18 = FileSlotGetSize_180d50(*(s32 *)(var_16 + 0x124), &sp28C, 0) - arg3;
    }
    if (arg3 > 0) {
        FileSlotSeek_180ed0(*(s32 *)(var_16 + 0x124), arg3, 0);
    }
    *(s32 *)(var_16 + 0x110) = var_18;
    *(s32 *)(var_16 + 0x114) = var_18;
    if (arg2 != NULL) {
        *arg2 = var_18;
    }
    *(s32 *)(var_16 + 0x120) = 1;
    if ((D_004811BC != 0) || (D_004811C0 != 0)) {
        FileReadChunked_180400(*(s32 *)(var_16 + 0x124), *(s32 *)(var_16 + 0x10C), var_18);
        FileSlotCloseThunk_180540(*(s32 *)(var_16 + 0x124));
        *(s32 *)(var_16 + 0x124) = -1;
        *(s32 *)(var_16 + 0x4) = 1;
        *(s32 *)(var_16 + 0x8) = 1;
    }
    return 1;
}
