#include "types.h"

typedef unsigned __int128 u128;

typedef struct Hdr {
    u8 pad0[4];
    s16 m4;
    s16 m6;
    u8 pad8[8];
    s32 m10;
    u8 pad14[0xC];
    u8 m20[0x10];
    s32 m30;
    u8 pad34[0xC];
    u8 m40[0x10];
    u8 m50[0x10];
} Hdr;

extern u128 Md5DigestQword_369050(void *, s32);
extern void SaveDataSetError_3e6340(s32, s32, s32, s32);
extern s32 memcmp(void *, void *, s32);
extern s32 D_004658D8[0x400];
extern s32 D_004658E0[0x400];
extern s32 D_004658F0[0x400];
extern s32 D_004658F8[0x400];

s32 SaveHeaderValidate_3e5100(s32 arg0, Hdr *arg1, s32 arg2, s32 arg3)
{
    u128 sp80;
    u128 sp70;
    s32 n1;
    s32 n2;

    if (arg1 == NULL) {
        return 0;
    }
    n1 = arg1->m30;
    if (n1 <= 0 || D_004658F0[0] < n1) {
        SaveDataSetError_3e6340(arg0, 7, n1, 0);
        return 0;
    }
    n2 = arg1->m10;
    if (n2 <= 0 || D_004658F8[0] < n2) {
        SaveDataSetError_3e6340(arg0, 8, n2, 0);
        return 0;
    }
    if (arg1->m4 != D_004658D8[0]) {
        SaveDataSetError_3e6340(arg0, 9, arg1->m4, 0);
        return 0;
    }
    if (arg1->m6 != D_004658E0[0]) {
        SaveDataSetError_3e6340(arg0, 10, arg1->m6, 0);
    }
    if (arg2 != 0) {
        sp80 = Md5DigestQword_369050(arg1->m50, n1);
        if (memcmp(arg1->m40, &sp80, 0x10) != 0) {
            SaveDataSetError_3e6340(arg0, 0xB, 0, 0);
            return 0;
        }
    }
    if (arg3 != 0) {
        sp70 = Md5DigestQword_369050(arg1->m50, n2);
        if (memcmp(arg1->m20, &sp70, 0x10) != 0) {
            SaveDataSetError_3e6340(arg0, 0xC, 0, 0);
            return 0;
        }
    }
    return 1;
}
