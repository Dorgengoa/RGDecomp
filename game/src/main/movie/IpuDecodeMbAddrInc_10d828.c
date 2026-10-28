#include "types.h"

extern void IpuSyncIfBusy_10de98(void);
extern void IpuWaitCmd_10db08(void);
extern void IpuShowBits_10dd70(void);
extern void IpuSkipBitsThunk_10de00(void);
extern void MpegReportErrorFmt_115ae8(void);

asm void IpuDecodeMbAddrInc_10d828(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    lui        $21, 0x45;
    sd         $19, 0x30($29);
    lui        $20, (0x30000000 >> 16);
    sd         $18, 0x20($29);
    addiu      $19, $0, 0x20;
    sd         $17, 0x10($29);
    daddu      $18, $0, $0;
    sd         $31, 0x60($29);
    daddu      $17, $4, $0;
    sd         $16, 0x0($29);
    nop;
  L0010D860:
    jal        IpuSyncIfBusy_10de98;
    daddu     $4, $17, $0;
    lui        $2, (0x10002000 >> 16);
    daddu      $4, $17, $0;
    ori        $2, $2, (0x10002000 & 0xFFFF);
    sw         $20, 0x0($2);
    sw         $20, 0x82C($17);
    jal        IpuWaitCmd_10db08;
    sw        $0, 0x828($17);
    daddu      $6, $2, $0;
    lui        $3, (0x10002030 >> 16);
    lui        $2, (0x10002020 >> 16);
    ori        $3, $3, (0x10002030 & 0xFFFF);
    ori        $2, $2, (0x10002020 & 0xFFFF);
    lw         $5, 0x0($2);
    ld         $4, 0x0($3);
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
    bgez       $4, L0010D8C4;
    sw        $2, 0x848($17);
    andi       $2, $5, 0x1F;
    subu       $2, $19, $2;
    andi       $2, $2, 0x1F;
    b          L0010D8C8;
    sw        $2, 0x84C($17);
  L0010D8C4:
    sw         $19, 0x84C($17);
  L0010D8C8:
    andi       $2, $6, 0xFFFF;
    dsll32     $3, $6, 0;
    dsra32     $3, $3, 0;
    sll        $2, $2, 16;
    sltiu      $3, $3, 0x1;
    sra        $16, $2, 16;
    addiu      $2, $0, 0x22;
    beq        $16, $2, L0010D948;
    sw        $3, 0x12C($17);
    sltiu      $2, $16, 0x23;
    beqz       $2, L0010D908;
    addiu     $2, $0, 0x23;
    beqz       $16, L0010D91C;
    daddu     $4, $17, $0;
    b          L0010D970;
    addu      $18, $18, $16;
  L0010D908:
    bnel       $16, $2, L0010D970;
    addu      $18, $18, $16;
    addiu      $2, $0, 0x1;
    b          L0010D974;
    addiu     $18, $18, 0x21;
  L0010D91C:
    jal        IpuShowBits_10dd70;
    addiu     $5, $0, 0xB;
    daddu      $3, $2, $0;
    lw         $2, 0x858($17);
    beqz       $2, L0010D950;
    addiu     $2, $0, 0xF;
    bne        $3, $2, L0010D954;
    addiu     $5, $21, 0x61C0;
    daddu      $4, $17, $0;
    jal        IpuSkipBitsThunk_10de00;
    addiu     $5, $0, 0xB;
  L0010D948:
    b          L0010D974;
    addiu     $2, $0, 0x1;
  L0010D950:
    addiu      $5, $21, 0x61C0;
  L0010D954:
    daddu      $6, $16, $0;
    jal        MpegReportErrorFmt_115ae8;
    daddu     $4, $17, $0;
    addiu      $3, $0, 0x1;
    addiu      $2, $0, 0x1;
    b          L0010D97C;
    sw        $3, 0x12C($17);
  L0010D970:
    daddu      $2, $0, $0;
  L0010D974:
    bnez       $2, L0010D860;
    daddu     $2, $18, $0;
  L0010D97C:
    ld         $31, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}

