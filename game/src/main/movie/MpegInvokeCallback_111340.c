#include "types.h"

asm void MpegInvokeCallback_111340(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $9, $0, $0;
    sd         $31, 0x10($29);
    beqz       $4, L001113A4;
    sd        $16, 0x0($29);
    lw         $6, 0x40($4);
    beqz       $6, L001113A4;
    addiu     $8, $0, 0xC;
    lw         $3, 0x0($5);
    mult       $3, $3, $8;
    addu       $2, $6, $3;
    lw         $7, 0xC($2);
    beqz       $7, L001113A8;
    ld        $31, 0x10($29);
    lw         $3, 0x14($2);
    daddu      $16, $28, $0;
    daddu      $28, $3, $0;
    lw         $2, 0x0($5);
    mult       $3, $2, $8;
    addu       $2, $3, $6;
    jalr $31, $7;
    lw        $6, 0x10($2);
    daddu      $9, $2, $0;
    daddu      $2, $28, $0;
    daddu      $28, $16, $0;
  L001113A4:
    ld         $31, 0x10($29);
  L001113A8:
    daddu      $2, $9, $0;
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

