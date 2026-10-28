#include "types.h"

asm void MpegInvokeNodataCallback_1113b8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    addiu      $2, $0, 0x1;
    sd         $31, 0x30($29);
    sd         $16, 0x20($29);
    beqz       $4, L00111418;
    sw        $2, 0x0($29);
    lw         $6, 0x40($4);
    beqz       $6, L00111420;
    ld        $31, 0x30($29);
    lw         $7, 0x18($6);
    beqz       $7, L00111424;
    ld        $16, 0x20($29);
    lw         $2, 0x20($6);
    daddu      $16, $28, $0;
    daddu      $28, $2, $0;
    lw         $3, 0x0($29);
    addiu      $2, $0, 0xC;
    daddu      $5, $29, $0;
    mult       $8, $3, $2;
    addu       $3, $8, $6;
    jalr $31, $7;
    lw        $6, 0x10($3);
    daddu      $3, $28, $0;
    daddu      $28, $16, $0;
  L00111418:
    ld         $31, 0x30($29);
    addiu      $2, $0, 0x1;
  L00111420:
    ld         $16, 0x20($29);
  L00111424:
    jr         $31;
    addiu     $29, $29, 0x40;
}

