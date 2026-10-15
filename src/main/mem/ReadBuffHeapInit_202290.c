#include "types.h"

s32 MemStackReturnToOwnerMaybe_14dad0(u8 *);
s32 MemStackHeapAlloc_14db10(u8 *, s32, s32, s32);
s32 MemStackHeapFree_14dcb0(u8 *, s32);
s32 MemStackHeapReinit_14de90(u8 *);
s32 MemStackHeapInit_14dee0(u8 *, s32, s32, s32, s32);
s32 MemStackClear_14dff0(u8 *);
s32 strcpy(char *, char *);
u32 strlen(char *);
extern char D_0045C168[16];
extern u8 *D_00481B58;
extern u8 *D_00481B60;
extern u8 D_004BB8F0[0x400];

void ReadBuffHeapInit_202290(u8 *arg0) {
    s32 a;
    s32 b;
    s32 c;

    MemStackClear_14dff0(D_004BB8F0);
    D_00481B58 = 0;
    if (arg0 != 0) {
        a = *(s32 *)(arg0 + 0x2C);
        b = *(s32 *)(arg0 + 0x34) - a;
        c = *(s32 *)(arg0 + 0x28) + a * 0x10 + (b - 4 + 0xFFFD8000) * 0x10;
        D_00481B58 = (u8 *)c;
        MemStackHeapInit_14dee0(D_004BB8F0, c, 0x28000, a * 0x10, b);
        if (strlen(D_0045C168) < 0x10U) {
            strcpy((char *)D_004BB8F0, D_0045C168);
        }
        MemStackHeapReinit_14de90(D_004BB8F0);
        D_00481B58 = (u8 *)MemStackHeapAlloc_14db10(D_004BB8F0, 2, 0, 0x40);
        MemStackReturnToOwnerMaybe_14dad0(D_004BB8F0);
        MemStackHeapFree_14dcb0(D_004BB8F0, (s32)D_00481B58);
        D_00481B60 = D_00481B58 + 0x100000;
    }
}
