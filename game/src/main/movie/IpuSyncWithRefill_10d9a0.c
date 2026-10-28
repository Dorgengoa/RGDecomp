#include "types.h"

extern void MpegInvokeNodataCallback_1113b8(void);
extern void IpuStopDmaAndReset_115928(void);

asm void IpuSyncWithRefill_10d9a0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    lui        $2, (0x10002010 >> 16);
    sd         $16, 0x0($29);
    ori        $2, $2, (0x10002010 & 0xFFFF);
    sd         $31, 0x90($29);
    lui        $5, (0x80004000 >> 16);
    sd         $30, 0x80($29);
    ori        $5, $5, (0x80004000 & 0xFFFF);
    sd         $23, 0x70($29);
    daddu      $16, $4, $0;
    sd         $22, 0x60($29);
    daddu      $6, $0, $0;
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    lw         $3, 0x0($2);
    lui        $2, (0x80000000 >> 16);
    and        $3, $3, $5;
    bnel       $3, $2, L0010DAD8;
    sw        $0, 0x82C($16);
    lui        $20, (0x10002020 >> 16);
    lui        $19, (0x1000B420 >> 16);
    lui        $18, (0x10002010 >> 16);
    lui        $17, (0x80004000 >> 16);
    ori        $20, $20, (0x10002020 & 0xFFFF);
    lui        $30, (0x20000000 >> 16);
    lui        $23, (0x30000000 >> 16);
    lui        $22, (0x40000000 >> 16);
    ori        $19, $19, (0x1000B420 & 0xFFFF);
    ori        $18, $18, (0x10002010 & 0xFFFF);
    ori        $17, $17, (0x80004000 & 0xFFFF);
    lui        $21, (0x80000000 >> 16);
  L0010DA28:
    lw         $4, 0x0($20);
    lui        $7, (0x30000 >> 16);
    lw         $5, 0x82C($16);
    andi       $3, $4, 0xFF00;
    and        $2, $4, $7;
    srl        $2, $2, 9;
    srl        $3, $3, 1;
    addu       $3, $3, $2;
    andi       $4, $4, 0x7F;
    beq        $5, $30, L0010DA64;
    subu      $2, $3, $4;
    beql       $5, $23, L0010DA68;
    sltiu     $2, $2, 0x20;
    bnel       $5, $22, L0010DA94;
    daddu     $2, $6, $0;
  L0010DA64:
    sltiu      $2, $2, 0x20;
  L0010DA68:
    beqz       $2, L0010DA94;
    daddu     $2, $6, $0;
    lw         $2, 0x0($19);
    bnez       $2, L0010DA94;
    daddu     $2, $6, $0;
    jal        MpegInvokeNodataCallback_1113b8;
    lw        $4, 0x868($16);
    lw         $3, 0x878($16);
    bnez       $3, L0010DAB4;
    daddu     $6, $0, $0;
    daddu      $2, $6, $0;
  L0010DA94:
    slti       $2, $2, 0x1389;
    bnez       $2, L0010DAC4;
    addiu     $6, $6, 0x1;
    jal        MpegInvokeNodataCallback_1113b8;
    lw        $4, 0x868($16);
    lw         $3, 0x878($16);
    beqz       $3, L0010DAC4;
    daddu     $6, $0, $0;
  L0010DAB4:
    jal        IpuStopDmaAndReset_115928;
    nop;
    b          L0010DAD8;
    sw        $0, 0x82C($16);
  L0010DAC4:
    lw         $2, 0x0($18);
    and        $2, $2, $17;
    beq        $2, $21, L0010DA28;
    nop;
    sw         $0, 0x82C($16);
  L0010DAD8:
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

