#include "types.h"

/* MAIN FocusWorkTexRegister_2f6910 -- the 0x324 counterpart of BlurWorkTexRegister_2f67b0; four
   surfaces, 0xC0/0xC0/0x80/0x80. */

extern void *GetDrawCtxNameTable_15de40(void);
extern void *NameTableAddEntry_159b70(void *, s32, void *, s32, s32, s32, s32, s32,
                          s32, s32);
extern u8 D_00461CD8[];
extern u8 D_00461CE8[];
extern u8 D_00461CF8[];
extern u8 D_00461D08[];

void FocusWorkTexRegister_2f6910(void)
{
    void *w;

    w = GetDrawCtxNameTable_15de40();
    NameTableAddEntry_159b70(w, 0x324, D_00461CD8, 0, 0xC0, 0xC0, 0x20, 0, 0, 0);
    NameTableAddEntry_159b70(w, 0x324, D_00461CE8, 0, 0xC0, 0xC0, 0x20, 0, 0, 0);
    NameTableAddEntry_159b70(w, 0x324, D_00461CF8, 0, 0x80, 0x80, 0x20, 0, 0, 0);
    NameTableAddEntry_159b70(w, 0x324, D_00461D08, 0, 0x80, 0x80, 0x20, 0, 0, 0);
}
