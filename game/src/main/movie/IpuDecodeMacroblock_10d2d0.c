#include "types.h"

extern void IpuSyncIfBusy_10de98(void);
extern void IpuWaitCmd_10db08(void);
extern void MpegReportError_115a90(void);
extern void IpuGetBits_10dc88(void);
extern void MpegDecodeMotionVectorsMaybe_10d130(void);
extern void IpuDecodeMotionVectorMaybe_10cd08(void);
extern void IpuSkipBitsThunk_10de00(void);
extern void DmaIpuFromStart_10efb8(void);

asm void IpuDecodeMacroblock_10d2d0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xD0;
    lui        $11, (0x10002010 >> 16);
    sd         $22, 0x90($29);
    ori        $11, $11, (0x10002010 & 0xFFFF);
    sd         $21, 0x80($29);
    lui        $2, (0xF8FFFFFF >> 16);
    sd         $19, 0x60($29);
    ori        $2, $2, (0xF8FFFFFF & 0xFFFF);
    sd         $17, 0x40($29);
    daddu      $19, $5, $0;
    sd         $16, 0x30($29);
    daddu      $21, $6, $0;
    sd         $31, 0xC0($29);
    daddu      $16, $4, $0;
    sd         $30, 0xB0($29);
    daddu      $17, $8, $0;
    sd         $23, 0xA0($29);
    daddu      $22, $10, $0;
    sd         $20, 0x70($29);
    sd         $18, 0x50($29);
    lw         $4, 0x160($16);
    lw         $3, 0x0($11);
    sll        $4, $4, 24;
    and        $3, $3, $2;
    or         $3, $3, $4;
    sw         $3, 0x0($11);
    daddu      $4, $16, $0;
    sw         $7, 0x20($29);
    jal        IpuSyncIfBusy_10de98;
    sw        $9, 0x24($29);
    lui        $2, (0x10002000 >> 16);
    lui        $3, (0x34000000 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    lui        $5, (0x30000000 >> 16);
    sw         $3, 0x0($2);
    daddu      $4, $16, $0;
    sw         $0, 0x828($16);
    jal        IpuWaitCmd_10db08;
    sw        $5, 0x82C($16);
    daddu      $6, $2, $0;
    lui        $3, (0x10002030 >> 16);
    lui        $2, (0x10002020 >> 16);
    ori        $3, $3, (0x10002030 & 0xFFFF);
    ori        $2, $2, (0x10002020 & 0xFFFF);
    lw         $5, 0x0($2);
    ld         $4, 0x0($3);
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
    bgez       $4, L0010D3A8;
    sw        $2, 0x848($16);
    andi       $2, $5, 0x1F;
    negu       $2, $2;
    b          L0010D3AC;
    andi      $2, $2, 0x1F;
  L0010D3A8:
    addiu      $2, $0, 0x20;
  L0010D3AC:
    sw         $2, 0x84C($16);
    andi       $2, $6, 0xFFFF;
    dsll32     $3, $6, 0;
    dsra32     $3, $3, 0;
    sltiu      $3, $3, 0x1;
    sll        $2, $2, 16;
    sra        $4, $2, 16;
    sw         $3, 0x12C($16);
    bnez       $4, L0010D3F4;
    sw        $4, 0x0($19);
    lui        $5, 0x45;
    daddu      $4, $16, $0;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x61A0;
    addiu      $3, $0, 0x1;
    daddu      $2, $0, $0;
    b          L0010D7F8;
    sw        $3, 0x12C($16);
  L0010D3F4:
    andi       $2, $4, 0xC;
    beqz       $2, L0010D434;
    addiu     $2, $0, 0x3;
    lw         $3, 0x184($16);
    bnel       $3, $2, L0010D424;
    daddu     $4, $16, $0;
    lw         $2, 0x18C($16);
    beqz       $2, L0010D420;
    addiu     $2, $0, 0x2;
    b          L0010D460;
    sw        $2, 0x0($21);
  L0010D420:
    daddu      $4, $16, $0;
  L0010D424:
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x2;
    b          L0010D460;
    sw        $2, 0x0($21);
  L0010D434:
    andi       $2, $4, 0x1;
    beql       $2, $0, L0010D464;
    lw        $6, 0x184($16);
    lw         $2, 0x190($16);
    beqz       $2, L0010D460;
    addiu     $3, $0, 0x1;
    lw         $2, 0x184($16);
    addiu      $4, $0, 0x2;
    xori       $2, $2, 0x3;
    movz       $3, $4, $2;
    sw         $3, 0x0($21);
  L0010D460:
    lw         $6, 0x184($16);
  L0010D464:
    addiu      $2, $0, 0x3;
    bne        $6, $2, L0010D48C;
    lw        $5, 0x0($21);
    addiu      $18, $0, 0x1;
    addiu      $2, $0, 0x2;
    xori       $3, $5, 0x1;
    xori       $4, $5, 0x2;
    movz       $18, $2, $3;
    b          L0010D4A0;
    sltiu     $20, $4, 0x1;
  L0010D48C:
    addiu      $3, $0, 0x2;
    addiu      $18, $0, 0x1;
    daddu      $20, $0, $0;
    xori       $2, $5, 0x2;
    movz       $18, $3, $2;
  L0010D4A0:
    xori       $2, $5, 0x3;
    daddu      $23, $0, $0;
    bnez       $20, L0010D4B8;
    sltiu     $30, $2, 0x1;
    xori       $2, $6, 0x3;
    sltiu      $23, $2, 0x1;
  L0010D4B8:
    addiu      $2, $0, 0x3;
    bne        $6, $2, L0010D4F4;
    daddu     $2, $0, $0;
    lw         $2, 0x18C($16);
    bnez       $2, L0010D4F4;
    daddu     $2, $0, $0;
    lw         $2, 0x0($19);
    andi       $2, $2, 0x3;
    beqz       $2, L0010D4F0;
    daddu     $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    b          L0010D4F8;
    lw        $3, 0x20($29);
  L0010D4F0:
    daddu      $2, $0, $0;
  L0010D4F4:
    lw         $3, 0x20($29);
  L0010D4F8:
    sw         $2, 0x0($3);
    lw         $3, 0x0($19);
    andi       $2, $3, 0x10;
    beqz       $2, L0010D51C;
    daddu     $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x5;
    sw         $2, 0x1C4($16);
    lw         $3, 0x0($19);
  L0010D51C:
    andi       $2, $3, 0x8;
    bnel       $2, $0, L0010D544;
    lw        $2, 0x858($16);
    andi       $2, $3, 0x1;
    beql       $2, $0, L0010D5B4;
    lw        $3, 0x12C($16);
    lw         $2, 0x190($16);
    beql       $2, $0, L0010D5B4;
    lw        $3, 0x12C($16);
    lw         $2, 0x858($16);
  L0010D544:
    beqz       $2, L0010D58C;
    daddu     $4, $16, $0;
    lw         $2, 0x178($16);
    lw         $11, 0x174($16);
    daddu      $5, $17, $0;
    addiu      $2, $2, -0x1;
    lw         $7, 0x24($29);
    sw         $30, 0x8($29);
    addiu      $11, $11, -0x1;
    sw         $2, 0x0($29);
    daddu      $6, $22, $0;
    sw         $23, 0x10($29);
    daddu      $8, $0, $0;
    daddu      $9, $18, $0;
    jal        MpegDecodeMotionVectorsMaybe_10d130;
    daddu     $10, $20, $0;
    b          L0010D5B4;
    lw        $3, 0x12C($16);
  L0010D58C:
    lw         $7, 0x168($16);
    lw         $11, 0x164($16);
    daddu      $5, $17, $0;
    addiu      $7, $7, -0x1;
    daddu      $6, $22, $0;
    daddu      $9, $0, $0;
    daddu      $8, $7, $0;
    jal        IpuDecodeMotionVectorMaybe_10cd08;
    daddu     $10, $0, $0;
    lw         $3, 0x12C($16);
  L0010D5B4:
    bnez       $3, L0010D7F8;
    daddu     $2, $0, $0;
    lw         $2, 0x0($19);
    andi       $2, $2, 0x4;
    beqz       $2, L0010D640;
    nop;
    lw         $2, 0x858($16);
    beqz       $2, L0010D618;
    daddu     $6, $22, $0;
    lw         $2, 0x180($16);
    lw         $11, 0x17C($16);
    daddu      $9, $18, $0;
    addiu      $2, $2, -0x1;
    lw         $7, 0x24($29);
    sw         $23, 0x10($29);
    daddu      $10, $20, $0;
    sw         $2, 0x0($29);
    addiu      $11, $11, -0x1;
    sw         $0, 0x8($29);
    daddu      $4, $16, $0;
    daddu      $5, $17, $0;
    jal        MpegDecodeMotionVectorsMaybe_10d130;
    addiu     $8, $0, 0x1;
    b          L0010D640;
    lw        $3, 0x12C($16);
  L0010D618:
    lw         $7, 0x170($16);
    lw         $11, 0x16C($16);
    daddu      $4, $16, $0;
    addiu      $7, $7, -0x1;
    addiu      $5, $17, 0x8;
    daddu      $9, $0, $0;
    daddu      $8, $7, $0;
    jal        IpuDecodeMotionVectorMaybe_10cd08;
    daddu     $10, $0, $0;
    lw         $3, 0x12C($16);
  L0010D640:
    bnez       $3, L0010D7F8;
    daddu     $2, $0, $0;
    lw         $3, 0x0($19);
    andi       $2, $3, 0x1;
    beqz       $2, L0010D674;
    andi      $2, $3, 0x3;
    lw         $2, 0x190($16);
    beqz       $2, L0010D670;
    daddu     $4, $16, $0;
    jal        IpuSkipBitsThunk_10de00;
    addiu     $5, $0, 0x1;
    lw         $3, 0x0($19);
  L0010D670:
    andi       $2, $3, 0x3;
  L0010D674:
    beqz       $2, L0010D718;
    addiu     $3, $0, 0x140;
    lw         $2, 0x820($16);
    addiu      $5, $0, 0x300;
    mult       $4, $2, $3;
    addu       $2, $4, $16;
    jal        DmaIpuFromStart_10efb8;
    lw        $4, 0x5A4($2);
    jal        IpuSyncIfBusy_10de98;
    daddu     $4, $16, $0;
    lw         $2, 0x20($29);
    lui        $7, (0x20000000 >> 16);
    lw         $4, 0x1C0($16);
    lui        $6, (0x10002000 >> 16);
    lw         $5, 0x0($2);
    ori        $6, $6, (0x10002000 & 0xFFFF);
    lw         $2, 0x0($19);
    sll        $4, $4, 26;
    lw         $3, 0x1C4($16);
    sll        $5, $5, 25;
    andi       $2, $2, 0x1;
    or         $5, $5, $4;
    sll        $2, $2, 27;
    sll        $3, $3, 16;
    or         $2, $2, $5;
    or         $3, $3, $7;
    or         $2, $2, $3;
    lui        $3, (0xF0000000 >> 16);
    sw         $2, 0x0($6);
    and        $5, $2, $3;
    beq        $5, $7, L0010D708;
    sw        $5, 0x82C($16);
    lui        $2, (0x30000000 >> 16);
    beq        $5, $2, L0010D708;
    lui       $2, (0x40000000 >> 16);
    bne        $5, $2, L0010D710;
    addiu     $2, $0, 0x1;
  L0010D708:
    b          L0010D72C;
    sw        $0, 0x828($16);
  L0010D710:
    b          L0010D72C;
    sw        $2, 0x828($16);
  L0010D718:
    lw         $2, 0x820($16);
    addiu      $4, $0, 0x1;
    mult       $5, $2, $3;
    addu       $2, $5, $16;
    sw         $4, 0x6DC($2);
  L0010D72C:
    lw         $2, 0x12C($16);
    beqz       $2, L0010D740;
    sw        $0, 0x1C0($16);
    b          L0010D7F8;
    daddu     $2, $0, $0;
  L0010D740:
    lw         $2, 0x0($19);
    andi       $2, $2, 0x1;
    bnel       $2, $0, L0010D76C;
    lw        $2, 0x190($16);
    addiu      $3, $0, 0x1;
    sw         $3, 0x1C0($16);
    lw         $2, 0x0($19);
    andi       $2, $2, 0x1;
    beql       $2, $0, L0010D798;
    lw        $4, 0x160($16);
    lw         $2, 0x190($16);
  L0010D76C:
    bnel       $2, $0, L0010D798;
    lw        $4, 0x160($16);
    sw         $0, 0x14($17);
    sw         $0, 0x10($17);
    sw         $0, 0x4($17);
    sw         $0, 0x0($17);
    sw         $0, 0x1C($17);
    sw         $0, 0x18($17);
    sw         $0, 0xC($17);
    sw         $0, 0x8($17);
    lw         $4, 0x160($16);
  L0010D798:
    addiu      $2, $0, 0x2;
    bne        $4, $2, L0010D7F8;
    addiu     $2, $0, 0x1;
    lw         $2, 0x0($19);
    andi       $2, $2, 0x9;
    bnez       $2, L0010D7F8;
    addiu     $2, $0, 0x1;
    sw         $0, 0x0($17);
    addiu      $3, $0, 0x3;
    sw         $0, 0x14($17);
    sw         $0, 0x10($17);
    sw         $0, 0x4($17);
    lw         $2, 0x184($16);
    bne        $2, $3, L0010D7DC;
    addiu     $3, $0, 0x1;
    b          L0010D7F4;
    sw        $4, 0x0($21);
  L0010D7DC:
    sw         $3, 0x0($21);
    lw         $3, 0x24($29);
    lw         $2, 0x184($16);
    xori       $2, $2, 0x2;
    sltiu      $2, $2, 0x1;
    sw         $2, 0x0($3);
  L0010D7F4:
    addiu      $2, $0, 0x1;
  L0010D7F8:
    ld         $31, 0xC0($29);
    ld         $30, 0xB0($29);
    ld         $23, 0xA0($29);
    ld         $22, 0x90($29);
    ld         $21, 0x80($29);
    ld         $20, 0x70($29);
    ld         $19, 0x60($29);
    ld         $18, 0x50($29);
    ld         $17, 0x40($29);
    ld         $16, 0x30($29);
    jr         $31;
    addiu     $29, $29, 0xD0;
}

