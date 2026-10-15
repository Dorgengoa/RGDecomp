#pragma divbyzerocheck on
#include "types.h"

extern void *UiEntryListFindByTag_28ea40(s32 arg0, s32 arg1);
extern const struct { s32 v; s32 pad[3]; } D_004659F0;
extern s32 D_00482364;
extern void *D_00482374;

void MenuGridGetCursor_2abb30(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 val;
    void *temp;

    if (arg0 != 0) {
        val = *(s32 *)((u8 *)D_00482374 + 0x30);
        *arg1 = val % D_004659F0.v;
        *arg2 = val / D_004659F0.v;
    } else {
        temp = UiEntryListFindByTag_28ea40(D_00482364, 3);
        *arg1 = *(s16 *)((u8 *)temp + 0x14);
        *arg2 = *(s16 *)((u8 *)temp + 0x16);
    }
}
