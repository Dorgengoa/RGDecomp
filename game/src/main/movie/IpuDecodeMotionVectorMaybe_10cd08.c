#include "types.h"

extern void IpuSyncIfBusy_10de98(void);
extern void IpuWaitCmd_10db08(void);
extern void IpuGetBits_10dc88(void);

asm void IpuDecodeMotionVectorMaybe_10cd08(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    sd         $17, 0x10($29);
    daddu      $17, $4, $0;
    sd         $30, 0x80($29);
    sd         $23, 0x70($29);
    daddu      $30, $6, $0;
    sd         $22, 0x60($29);
    daddu      $23, $9, $0;
    sd         $21, 0x50($29);
    daddu      $22, $10, $0;
    sd         $20, 0x40($29);
    daddu      $21, $11, $0;
    sd         $19, 0x30($29);
    daddu      $20, $8, $0;
    sd         $18, 0x20($29);
    daddu      $19, $5, $0;
    sd         $31, 0x90($29);
    daddu      $18, $7, $0;
    jal        IpuSyncIfBusy_10de98;
    sd        $16, 0x0($29);
    lui        $2, (0x10002000 >> 16);
    lui        $3, (0x38000000 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    lui        $5, (0x30000000 >> 16);
    sw         $3, 0x0($2);
    daddu      $4, $17, $0;
    sw         $0, 0x828($17);
    jal        IpuWaitCmd_10db08;
    sw        $5, 0x82C($17);
    daddu      $6, $2, $0;
    lui        $3, (0x10002030 >> 16);
    lui        $2, (0x10002020 >> 16);
    ori        $3, $3, (0x10002030 & 0xFFFF);
    ori        $2, $2, (0x10002020 & 0xFFFF);
    lw         $5, 0x0($2);
    ld         $4, 0x0($3);
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
    bgez       $4, L0010CDB8;
    sw        $2, 0x848($17);
    andi       $2, $5, 0x1F;
    negu       $2, $2;
    b          L0010CDBC;
    andi      $2, $2, 0x1F;
  L0010CDB8:
    addiu      $2, $0, 0x20;
  L0010CDBC:
    sw         $2, 0x84C($17);
    andi       $3, $6, 0xFFFF;
    dsll32     $2, $6, 0;
    dsra32     $2, $2, 0;
    sltiu      $2, $2, 0x1;
    sll        $3, $3, 16;
    sw         $2, 0x12C($17);
    beqz       $18, L0010CDFC;
    sra       $16, $3, 16;
    beqz       $16, L0010CE00;
    daddu     $5, $0, $0;
    daddu      $4, $17, $0;
    jal        IpuGetBits_10dc88;
    daddu     $5, $18, $0;
    b          L0010CE00;
    daddu     $5, $2, $0;
  L0010CDFC:
    daddu      $5, $0, $0;
  L0010CE00:
    lw         $4, 0x0($19);
    addiu      $2, $0, 0x10;
    sllv       $6, $2, $18;
    sra        $3, $4, 1;
    blez       $16, L0010CE44;
    movn      $4, $3, $21;
    addiu      $2, $16, -0x1;
    addiu      $4, $4, 0x1;
    sllv       $2, $2, $18;
    addu       $2, $2, $5;
    addu       $4, $4, $2;
    slt        $3, $4, $6;
    bnez       $3, L0010CE78;
    sll       $2, $4, 1;
    sll        $2, $6, 1;
    b          L0010CE74;
    subu      $4, $4, $2;
  L0010CE44:
    bgez       $16, L0010CE78;
    sll       $2, $4, 1;
    nor        $2, $0, $16;
    addiu      $4, $4, -0x1;
    sllv       $2, $2, $18;
    negu       $3, $6;
    addu       $2, $2, $5;
    subu       $4, $4, $2;
    slt        $3, $4, $3;
    beqz       $3, L0010CE74;
    sll       $2, $6, 1;
    addu       $4, $4, $2;
  L0010CE74:
    sll        $2, $4, 1;
  L0010CE78:
    movz       $2, $4, $21;
    beqz       $23, L0010CF14;
    sw        $2, 0x0($19);
    jal        IpuSyncIfBusy_10de98;
    daddu     $4, $17, $0;
    lui        $2, (0x10002000 >> 16);
    lui        $3, (0x3C000000 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    lui        $5, (0x30000000 >> 16);
    sw         $3, 0x0($2);
    daddu      $4, $17, $0;
    sw         $0, 0x828($17);
    jal        IpuWaitCmd_10db08;
    sw        $5, 0x82C($17);
    daddu      $6, $2, $0;
    lui        $3, (0x10002030 >> 16);
    lui        $2, (0x10002020 >> 16);
    ori        $3, $3, (0x10002030 & 0xFFFF);
    ori        $2, $2, (0x10002020 & 0xFFFF);
    lw         $5, 0x0($2);
    ld         $4, 0x0($3);
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
    bgez       $4, L0010CEEC;
    sw        $2, 0x848($17);
    andi       $2, $5, 0x1F;
    negu       $2, $2;
    b          L0010CEF0;
    andi      $2, $2, 0x1F;
  L0010CEEC:
    addiu      $2, $0, 0x20;
  L0010CEF0:
    sw         $2, 0x84C($17);
    andi       $3, $6, 0xFFFF;
    dsll32     $2, $6, 0;
    dsra32     $2, $2, 0;
    sltiu      $2, $2, 0x1;
    sll        $3, $3, 16;
    sw         $2, 0x12C($17);
    sra        $3, $3, 16;
    sw         $3, 0x0($30);
  L0010CF14:
    jal        IpuSyncIfBusy_10de98;
    daddu     $4, $17, $0;
    lui        $2, (0x10002000 >> 16);
    lui        $3, (0x38000000 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    lui        $5, (0x30000000 >> 16);
    sw         $3, 0x0($2);
    daddu      $4, $17, $0;
    sw         $0, 0x828($17);
    jal        IpuWaitCmd_10db08;
    sw        $5, 0x82C($17);
    daddu      $6, $2, $0;
    lui        $3, (0x10002030 >> 16);
    lui        $2, (0x10002020 >> 16);
    ori        $3, $3, (0x10002030 & 0xFFFF);
    ori        $2, $2, (0x10002020 & 0xFFFF);
    lw         $5, 0x0($2);
    ld         $4, 0x0($3);
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
    bgez       $4, L0010CF7C;
    sw        $2, 0x848($17);
    andi       $2, $5, 0x1F;
    negu       $2, $2;
    b          L0010CF80;
    andi      $2, $2, 0x1F;
  L0010CF7C:
    addiu      $2, $0, 0x20;
  L0010CF80:
    sw         $2, 0x84C($17);
    andi       $3, $6, 0xFFFF;
    dsll32     $2, $6, 0;
    dsra32     $2, $2, 0;
    sltiu      $2, $2, 0x1;
    sll        $3, $3, 16;
    sw         $2, 0x12C($17);
    beqz       $20, L0010CFBC;
    sra       $16, $3, 16;
    beqz       $16, L0010CFBC;
    daddu     $4, $17, $0;
    jal        IpuGetBits_10dc88;
    daddu     $5, $20, $0;
    b          L0010CFC0;
    daddu     $5, $2, $0;
  L0010CFBC:
    daddu      $5, $0, $0;
  L0010CFC0:
    beql       $22, $0, L0010CFD8;
    lw        $4, 0x4($19);
    lw         $2, 0x4($19);
    sra        $2, $2, 1;
    sw         $2, 0x4($19);
    lw         $4, 0x4($19);
  L0010CFD8:
    addiu      $2, $0, 0x10;
    sllv       $6, $2, $20;
    addiu      $7, $19, 0x4;
    sra        $2, $4, 1;
    blez       $16, L0010D01C;
    movn      $4, $2, $21;
    addiu      $2, $16, -0x1;
    addiu      $4, $4, 0x1;
    sllv       $2, $2, $20;
    addu       $2, $2, $5;
    addu       $4, $4, $2;
    slt        $3, $4, $6;
    bnez       $3, L0010D050;
    sll       $2, $4, 1;
    sll        $2, $6, 1;
    b          L0010D04C;
    subu      $4, $4, $2;
  L0010D01C:
    bgez       $16, L0010D050;
    sll       $2, $4, 1;
    nor        $2, $0, $16;
    addiu      $4, $4, -0x1;
    sllv       $2, $2, $20;
    negu       $3, $6;
    addu       $2, $2, $5;
    subu       $4, $4, $2;
    slt        $3, $4, $3;
    beqz       $3, L0010D04C;
    sll       $2, $6, 1;
    addu       $4, $4, $2;
  L0010D04C:
    sll        $2, $4, 1;
  L0010D050:
    movz       $2, $4, $21;
    beqz       $22, L0010D068;
    sw        $2, 0x0($7);
    lw         $2, 0x4($19);
    sll        $2, $2, 1;
    sw         $2, 0x4($19);
  L0010D068:
    beqz       $23, L0010D104;
    ld        $31, 0x90($29);
    jal        IpuSyncIfBusy_10de98;
    daddu     $4, $17, $0;
    lui        $2, (0x10002000 >> 16);
    lui        $3, (0x3C000000 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    lui        $5, (0x30000000 >> 16);
    sw         $3, 0x0($2);
    daddu      $4, $17, $0;
    sw         $0, 0x828($17);
    jal        IpuWaitCmd_10db08;
    sw        $5, 0x82C($17);
    daddu      $6, $2, $0;
    lui        $3, (0x10002030 >> 16);
    lui        $2, (0x10002020 >> 16);
    ori        $3, $3, (0x10002030 & 0xFFFF);
    ori        $2, $2, (0x10002020 & 0xFFFF);
    lw         $5, 0x0($2);
    ld         $4, 0x0($3);
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
    bgez       $4, L0010D0D8;
    sw        $2, 0x848($17);
    andi       $2, $5, 0x1F;
    negu       $2, $2;
    b          L0010D0DC;
    andi      $2, $2, 0x1F;
  L0010D0D8:
    addiu      $2, $0, 0x20;
  L0010D0DC:
    sw         $2, 0x84C($17);
    andi       $3, $6, 0xFFFF;
    dsll32     $2, $6, 0;
    dsra32     $2, $2, 0;
    sltiu      $2, $2, 0x1;
    sll        $3, $3, 16;
    sw         $2, 0x12C($17);
    sra        $3, $3, 16;
    sw         $3, 0x4($30);
    ld         $31, 0x90($29);
  L0010D104:
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

