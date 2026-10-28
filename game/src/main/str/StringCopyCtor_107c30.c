#include "types.h"

extern void StringReserve_107e80(void);
extern void StringReplace_106f90(void);

asm void StringCopyCtor_107c30(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $4, $0;
    lw         $2, 0x0($5);
    andi       $2, $2, 0x1;
    bnez       $2, L00107C70;
    daddu     $16, $5, $0;
    lwc1       $f2, 0x0($16);
    lwc1       $f1, 0x4($16);
    lwc1       $f0, 0x8($16);
    swc1       $f2, 0x0($17);
    swc1       $f1, 0x4($17);
    b          L00107CA4;
    swc1      $f0, 0x8($17);
  L00107C70:
    sw         $0, 0x0($17);
    sw         $0, 0x4($17);
    sw         $0, 0x8($17);
    jal        StringReserve_107e80;
    lw        $5, 0x4($16);
    lw         $7, 0x8($16);
    daddu      $4, $17, $0;
    lw         $2, 0x4($16);
    daddu      $5, $0, $0;
    lb         $9, 0x3C($29);
    daddu      $6, $0, $0;
    jal        StringReplace_106f90;
    addu      $8, $7, $2;
  L00107CA4:
    daddu      $2, $17, $0;
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

