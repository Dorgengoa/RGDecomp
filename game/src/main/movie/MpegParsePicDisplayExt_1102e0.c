#include "types.h"

extern void IpuGetBits_10dc88(void);

asm void MpegParsePicDisplayExt_1102e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $17, 0x10($29);
    sd         $31, 0x60($29);
    daddu      $17, $4, $0;
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    sd         $16, 0x0($29);
    lw         $2, 0x14C($17);
    beql       $2, $0, L0011032C;
    lw        $3, 0x184($17);
    lw         $2, 0x194($17);
    beqz       $2, L00110338;
    addiu     $19, $0, 0x2;
    lw         $3, 0x188($17);
    addiu      $2, $0, 0x3;
    b          L00110348;
    movn      $19, $2, $3;
  L0011032C:
    addiu      $2, $0, 0x3;
    beql       $3, $2, L00110340;
    lw        $2, 0x194($17);
  L00110338:
    b          L00110348;
    addiu     $19, $0, 0x1;
  L00110340:
    addiu      $19, $0, 0x2;
    movn       $19, $3, $2;
  L00110348:
    blez       $19, L001103B0;
    daddu     $18, $0, $0;
    addiu      $21, $17, 0x19C;
    addiu      $20, $17, 0x1A8;
    daddu      $4, $17, $0;
    nop;
  L00110360:
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x10;
    sll        $16, $18, 2;
    addu       $3, $21, $16;
    daddu      $4, $17, $0;
    sw         $2, 0x0($3);
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    addiu      $18, $18, 0x1;
    daddu      $4, $17, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x10;
    addu       $16, $20, $16;
    daddu      $4, $17, $0;
    sw         $2, 0x0($16);
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    slt        $3, $18, $19;
    bnez       $3, L00110360;
    daddu     $4, $17, $0;
  L001103B0:
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
