/* main s27m: CLOSED -- MesWinSetOpenRate_277550 takes an F32 (retail `mtc1 $zero,$f12`) plus the
   const+.sdata lever on D_0047D53C. */
/* main s22: 2 WRONG ACCESS WIDTH(s) corrected from retail's own
   opcode (same registers + offset, different opcode -- a type defect no
   colouring lever can reach).  7 -> improved; still parked. */
/* PARK: same length as retail, 7 bad words after 1 round. Not re-tried. */
#include "types.h"

extern void TextStyleInit_26c610(void);
extern void TextStyleSetOutlineMode_26f160(void *arg0, s32 arg1);
extern void MesWinSetFrameType_272b30(void *arg0, s32 arg1);
extern void MesWinSetSeEnabled_272b50(void *arg0, s32 arg1);
extern void MesWinSetFixedPos_272b70(void *arg0, s32 arg1);
extern void MesWinSetTextFile_274e50(void *arg0, s32 arg1, s32 arg2);
extern void MesWinSetColor_276e80(void *arg0, s32 arg1);
extern void MesWinSetMsgData_276ea0(void *arg0, s32 arg1);
extern void MesWinClearState_277030(void *arg0);
extern void MesWinSetOpenRate_277550(void *arg0, f32 arg1);
extern void MesWinSetOpenSpeed_277570(void *arg0, f32 arg1);
extern void MesWinSetInstant_277610(void *arg0, s32 arg1);
extern void MesWinSetCharSpeed_277630(void *arg0, f32 arg1);
extern void MesWinClearRect_2776d0(void *arg0);
extern const f32 D_0047D53C __attribute__((section(".sdata")));
extern f32 D_0047D5D0;

void MesWinInit_276f20(void *arg0)
{
    TextStyleInit_26c610();
    *(s32 *)((u8 *)arg0 + 0x40) = 0x64;
    *(s32 *)((u8 *)arg0 + 0x44) = 0x32;
    *(f32 *)((u8 *)arg0 + 0x48) = 0.5f;
    *(f32 *)((u8 *)arg0 + 0x4C) = D_0047D53C;
    MesWinSetFixedPos_272b70(arg0, 0);
    MesWinSetSeEnabled_272b50(arg0, 0);
    MesWinSetFrameType_272b30(arg0, 1);
    MesWinClearRect_2776d0((u8 *)arg0 + 0x88);
    *(s32 *)((u8 *)arg0 + 0xA0) = -1;
    *(s32 *)((u8 *)arg0 + 0xA4) = -1;
    *(s32 *)((u8 *)arg0 + 0xA8) = 0;
    *(s32 *)((u8 *)arg0 + 0xAC) = 0;
    MesWinClearState_277030(arg0);
    MesWinSetCharSpeed_277630(arg0, D_0047D5D0);
    MesWinSetInstant_277610(arg0, 0);
    MesWinSetOpenSpeed_277570(arg0, D_0047D5D0);
    MesWinSetOpenRate_277550(arg0, 0.0f);
    MesWinSetColor_276e80(arg0, 1);
    *(s16 *)((u8 *)arg0 + 0x1DF8) = 0;
    MesWinSetMsgData_276ea0(arg0, 0);
    MesWinSetTextFile_274e50(arg0, 0, 0);
    TextStyleSetOutlineMode_26f160(arg0, 2);
    *(u8 *)((u8 *)arg0 + 0x1DEE) = 0;
    *(u8 *)((u8 *)arg0 + 0x1DEC) = 0;
    *(u8 *)((u8 *)arg0 + 0x1DED) = 0;
    *(s8 *)((u8 *)arg0 + 0x1C39) = -1;
}
