#include "types.h"

extern void MpegInvokeNodataCallback_1113b8(void);
extern void IpuStopDmaAndReset_115928(void);

asm void IpuWaitCmd_10db08(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    lui        $2, (0x10002000 >> 16);
    sd         $16, 0x0($29);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    sd         $31, 0x90($29);
    daddu      $16, $4, $0;
    sd         $30, 0x80($29);
    daddu      $6, $0, $0;
    sd         $23, 0x70($29);
    sd         $22, 0x60($29);
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    ld         $17, 0x0($2);
    bgezl      $17, L0010DC54;
    sw        $0, 0x82C($16);
    lui        $2, (0x10002010 >> 16);
    ori        $2, $2, (0x10002010 & 0xFFFF);
    lw         $3, 0x0($2);
    andi       $3, $3, 0x4000;
    bnel       $3, $0, L0010DC54;
    sw        $0, 0x82C($16);
    lui        $21, (0x10002020 >> 16);
    lui        $20, (0x1000B420 >> 16);
    lui        $19, (0x10002000 >> 16);
    lui        $18, (0x10002010 >> 16);
    ori        $21, $21, (0x10002020 & 0xFFFF);
    lui        $30, (0x20000000 >> 16);
    lui        $23, (0x30000000 >> 16);
    lui        $22, (0x40000000 >> 16);
    ori        $20, $20, (0x1000B420 & 0xFFFF);
    ori        $19, $19, (0x10002000 & 0xFFFF);
    ori        $18, $18, (0x10002010 & 0xFFFF);
    nop;
  L0010DB98:
    lw         $4, 0x0($21);
    lui        $7, (0x30000 >> 16);
    lw         $5, 0x82C($16);
    andi       $3, $4, 0xFF00;
    and        $2, $4, $7;
    srl        $2, $2, 9;
    srl        $3, $3, 1;
    addu       $3, $3, $2;
    andi       $4, $4, 0x7F;
    beq        $5, $30, L0010DBD4;
    subu      $2, $3, $4;
    beql       $5, $23, L0010DBD8;
    sltiu     $2, $2, 0x20;
    bnel       $5, $22, L0010DC04;
    daddu     $2, $6, $0;
  L0010DBD4:
    sltiu      $2, $2, 0x20;
  L0010DBD8:
    beqz       $2, L0010DC04;
    daddu     $2, $6, $0;
    lw         $2, 0x0($20);
    bnez       $2, L0010DC04;
    daddu     $2, $6, $0;
    jal        MpegInvokeNodataCallback_1113b8;
    lw        $4, 0x868($16);
    lw         $3, 0x878($16);
    bnez       $3, L0010DC24;
    daddu     $6, $0, $0;
    daddu      $2, $6, $0;
  L0010DC04:
    slti       $2, $2, 0x1F5;
    bnez       $2, L0010DC34;
    addiu     $6, $6, 0x1;
    jal        MpegInvokeNodataCallback_1113b8;
    lw        $4, 0x868($16);
    lw         $3, 0x878($16);
    beqz       $3, L0010DC34;
    daddu     $6, $0, $0;
  L0010DC24:
    jal        IpuStopDmaAndReset_115928;
    nop;
    b          L0010DC54;
    sw        $0, 0x82C($16);
  L0010DC34:
    ld         $17, 0x0($19);
    bgezl      $17, L0010DC54;
    sw        $0, 0x82C($16);
    lw         $2, 0x0($18);
    andi       $2, $2, 0x4000;
    beqz       $2, L0010DB98;
    nop;
    sw         $0, 0x82C($16);
  L0010DC54:
    daddu      $2, $17, $0;
    ld         $31, 0x90($29);
    ld         $30, 0x80($29);
    ld         $23, 0x70($29);
    ld         $22, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0xA0;
}

