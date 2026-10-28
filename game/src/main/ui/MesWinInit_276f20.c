/* rgp:protos */
#define RGP_SELF_MesWinInit_276f20 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED -- MesWinSetOpenRate_277550 takes an F32 (retail `mtc1 $zero,$f12`) plus the
   const+.sdata lever on D_0047D53C. */
/* main s22: 2 WRONG ACCESS WIDTH(s) corrected from retail's own
   opcode (same registers + offset, different opcode -- a type defect no
   colouring lever can reach).  7 -> improved; still parked. */
/* PARK: same length as retail, 7 bad words after 1 round. Not re-tried. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D53C __attribute__((section(".sdata")));
extern f32 D_0047D5D0;

void MesWinInit_276f20(void *arg0)
{
    TextStyleInit_26c610((void *)arg0);
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
