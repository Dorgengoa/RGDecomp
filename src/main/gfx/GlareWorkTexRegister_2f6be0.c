#include "types.h"

extern void DrawEnvGetHeight_1451d0(s32);
extern void DrawEnvGetWidth_1451e0(s32);
extern void NameTableAddEntry_159b70(s32, s32, void *, s32, s32, s32, s32, s32, s64, s64);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetDrawCtx_15de80(void);
extern u8 D_00461D28[0x400];
extern u8 D_00461D38[0x400];

void GlareWorkTexRegister_2f6be0(void)
{
    s32 a;
    s32 b;

    a = GetDrawCtx_15de80();
    b = GetDrawCtxNameTable_15de40();
    DrawEnvGetWidth_1451e0(a);
    DrawEnvGetHeight_1451d0(a);
    NameTableAddEntry_159b70(b, 0x323, &(*(u8 *)D_00461D28), 0, 0xC0, 0xC0, 0x20, 0, 0, 0);
    NameTableAddEntry_159b70(b, 0x323, &(*(u8 *)D_00461D38), 0, 0xC0, 0xC0, 0x20, 0, 0, 0);
}
