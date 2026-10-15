#include "types.h"

extern void *GetGameData_1fede0(void);
extern s32 GetFactoryObj_367f30(void);
extern void func_503050(s32, s32, s32);
extern void func_503CD0(s32, s32, s32);
extern void func_503D00(s32, s32, s32);
extern void func_503D30(s32);

void FactorySetupPoolsAndLoadLayout_367a30(void)
{
    s32 temp_2;

    temp_2 = GetFactoryObj_367f30();
    if (temp_2 != 0) {
        func_503D00(temp_2, 0x13, 0x300);
        func_503D00(temp_2, 0x14, 0x300);
        func_503D00(temp_2, 0x15, 0x80);
        func_503D00(temp_2, 0x16, 0x40);
        func_503D00(temp_2, 0x17, 0x40);
        func_503D00(temp_2, 0x18, 0x40);
        func_503CD0(temp_2, 0, 3);
        func_503CD0(temp_2, 1, 2);
        func_503CD0(temp_2, 2, 3);
        func_503CD0(temp_2, 3, 3);
        func_503CD0(temp_2, 4, 3);
        func_503CD0(temp_2, 5, 3);
        func_503CD0(temp_2, 6, 3);
        func_503CD0(temp_2, 7, 1);
        func_503CD0(temp_2, 8, 1);
        func_503CD0(temp_2, 9, 1);
        func_503CD0(temp_2, 0xA, 4);
        func_503CD0(temp_2, 0xB, 3);
        func_503CD0(temp_2, 0xC, 1);
        func_503CD0(temp_2, 0xD, 4);
        func_503CD0(temp_2, 0xE, 1);
        func_503CD0(temp_2, 0xF, 0x28);
        func_503CD0(temp_2, 0x10, 0x1E);
        func_503CD0(temp_2, 0x11, 0xA);
        func_503D30(temp_2);
        func_503050(temp_2, *(s32 *)((u8 *)GetGameData_1fede0() + 0x10) + 0xAA0, 0xC00);
    }
}
