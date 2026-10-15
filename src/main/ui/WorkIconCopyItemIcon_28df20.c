#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 pad0[0x50];
    s32 unk50;
} Buf0028DF20;

Buf0028DF20 *NameTableFindByName_159fb0();
s32 GetDrawCtxNameTable_15de40();
void UiIconGetSheetPos_288720(s32, s32, s16 *, s16 *);
void *memcpy(void *, const void *, u32);
extern u8 D_004610D0[0x10];
extern u8 D_004610E0[0x10];

s32 WorkIconCopyItemIcon_28df20(s32 *arg0, s32 arg1)
{
    s16 x;
    s16 y;
    s32 ctx;
    s32 idx;
    s32 col;
    s32 row;
    Buf0028DF20 *p;
    s32 dst;
    s32 src;
    s32 i;

    ctx = GetDrawCtxNameTable_15de40();
    if (ctx == 0) {
        return 1;
    }
    idx = arg1 % 100 - 1;
    UiIconGetSheetPos_288720(arg1 / 1000, arg1 % 1000 / 100, &x, &y);
    if (idx < 0 || idx > 0x40) {
        idx = 0;
    }
    col = idx % 8;
    row = idx / 8;
    p = NameTableFindByName_159fb0(ctx, D_004610E0, -1);
    if (p == NULL) {
        return 2;
    }
    dst = (s32)((u8 *)p->unk50 + (arg0[1] << 8) + arg0[0]);
    p = NameTableFindByName_159fb0(ctx, D_004610D0, -1);
    if (p == NULL) {
        return 3;
    }
    src = p->unk50 + ((y + (row << 5)) << 10) + (x + (col << 5));
    for (i = 0; i < 0x20; i++) {
        memcpy((void *)dst, (void *)src, 0x20);
        dst += 0x100;
        src += 0x400;
    }
    return 0;
}
