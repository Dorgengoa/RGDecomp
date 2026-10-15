#include "types.h"

typedef struct Str {
    s32 f0;
    u8 pad[0xAC];
} Str;

extern s32 UiEntryListSelectByTag_28ea90(void *, s32, s32);
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void *UiGetWidgetSprite_28fe10(void *, s32, s32);
extern void UiLayoutFrameRectsMaybe_28bbb0(void *, s32, s32);
extern void UiSetTextPos_28f5d0(void *, s32, s32, s32, s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSetTextString_28f510(void *, s32, void *, s32);
extern void MsgFormatParamsCtor_28aa00(Str *);
extern void MsgFormat_28a9a0(void *, s32, Str *, s32);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);
extern void StreamPlayMwv_207340(s32, s32, f32);
extern s32 MenuGridCursorInput_28e170(void *, void *, s32, s32);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern f32 D_0047D5D0;
extern f32 D_0047D7C8;
extern u8 D_00483470[8];
extern s32 D_0048347C;
extern s32 D_00483494;
extern u8 D_004834A0[8];
extern s16 D_004834C0;
extern u8 D_004B2570[0x40];
extern u8 D_004E9550[0x20];
extern u8 D_004E9570[0x40];

s32 SeventhMysteryQuizResult_394380(s32 pad0, s32 arg1)
{
    Str sp10;
    void *p;
    s32 r;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_004E9570, 0x7532, 0);
        UiFadeWidgetAlpha_290690(D_004E9550, 5, 0.0f, D_0047D7C8, -1.0f);
        UiFadeWidgetAlpha_290690(D_004E9550, 0xB, 0.0f, D_0047D7C8, -1.0f);
        p = UiGetWidgetSprite_28fe10(D_004E9550, 0xA, 0);
        if (p == 0) {
            return 0;
        }
        UiLayoutFrameRectsMaybe_28bbb0(p, 0xC8, 0x28);
        UiSetTextPos_28f5d0(D_004E9550, 0xA, 0x3C, 0xB, 0);
        UiSetTextString_28f510(D_004E9550, 0xA, (void *)MsgTableLookup_28aa30(D_0048347C, 0x38E), 0);
        MsgFormatParamsCtor_28aa00(&sp10);
        sp10.f0 = D_00483494;
        MsgFormat_28a9a0(D_004834A0, MsgTableLookup_28aa30(D_0048347C, 0x38F), &sp10, 1);
        UiSetTextPos_28f5d0(D_004E9550, 0xA, 0x78, 0xB, 1);
        UiSetTextString_28f510(D_004E9550, 0xA, D_004834A0, 1);
        UiSetWidgetsVisibleById_291110(D_004E9550, 0xA, 1, 1);
        UiSetWidgetPos_290f60(D_004E9550, 0xA, 0x9C, 0xB8);
        UiFadeWidgetAlpha_290690(D_004E9550, 0xA, 1.0f, D_0047D5D0, 0.0f);
        UiFadeWidgetAlpha_290690(D_004E9550, 0xA, 1.0f, D_0047D5D0, 0.0f);
        D_004834C0 = 0xB4;
        if (D_00483494 == 7) {
            StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0xF, 0.0f);
            StreamPlayMwv_207340(0x328, 0, 1.0f);
            D_004834C0 = 0;
        }
    } else if (D_004834C0 < 0xC8) {
        D_004834C0 += 1;
    } else if (D_004834C0 == 0xC8) {
        r = MenuGridCursorInput_28e170(D_004E9570, D_004B2570, 0, 0);
        if (r == 1 || r == 2) {
            if (D_00483494 == 7) {
                StateMachineSetState_28ede0(D_00483470, 0x7538, 0);
            } else {
                StateMachineSetState_28ede0(D_00483470, 0x7539, 0);
            }
        }
    }
    return 1;
}
