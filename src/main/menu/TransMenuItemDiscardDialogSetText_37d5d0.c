#include "types.h"

typedef struct {
    s32 m0;
    s32 m4;
    s32 m8;
    s32 mC;
    u8 pad10[0xB0 - 0x10];
} Prm37d5d0;

extern void memset(void *, s32, s32);
extern void MsgFormatParamsCtor_28aa00(Prm37d5d0 *);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void MsgFormat_28a9a0(void *, s32, Prm37d5d0 *, s32);
extern void UiSetTextString_28f510(s32, s32, void *, s32);
extern s32 D_00484710;
extern s32 D_00484770;
extern u8 D_004E9260[0x400];

s32 TransMenuItemDiscardDialogSetText_37d5d0(s32 arg0, s32 arg1)
{
    Prm37d5d0 p;

    memset(D_004E9260, 0, 0x20);
    MsgFormatParamsCtor_28aa00(&p);
    p.mC = arg0;
    p.m0 = arg1;
    MsgFormat_28a9a0(D_004E9260, MsgTableLookup_28aa30(D_00484770, 0x3F4), &p, 1);
    UiSetTextString_28f510(D_00484710, 0x7620, D_004E9260, 0);
    UiSetTextString_28f510(D_00484710, 0x7620, (void *)MsgTableLookup_28aa30(D_00484770, 0x3F5), 1);
    UiSetTextString_28f510(D_00484710, 0x7620, (void *)MsgTableLookup_28aa30(D_00484770, 0x3F6), 2);
    UiSetTextString_28f510(D_00484710, 0x7620, (void *)MsgTableLookup_28aa30(D_00484770, 0x3F7), 3);
    return 1;
}
