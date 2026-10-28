#include "types.h"

extern void Multadd_131dc8(void);
extern void I2b_132140(void);
extern void Mult_132178(void);
extern void _Bfree(void);

asm void Pow5mult_132388(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x8($29);
    daddu      $17, $6, $0;
    andi       $2, $17, 0x3;
    sd         $18, 0x10($29);
    sd         $19, 0x18($29);
    daddu      $19, $4, $0;
    sd         $16, 0x0($29);
    daddu      $18, $5, $0;
    beqz       $2, L001323D0;
    sd        $31, 0x20($29);
    sll        $2, $2, 2;
    lui        $6, 0x46;
    addu       $6, $6, $2;
    lw         $6, -0x7FBC($6);
    jal        Multadd_131dc8;
    daddu     $7, $0, $0;
    daddu      $18, $2, $0;
  L001323D0:
    sra        $17, $17, 2;
    beqz       $17, L00132468;
    daddu     $2, $18, $0;
    lw         $16, 0x48($19);
    bnez       $16, L00132434;
    andi      $2, $17, 0x1;
    daddu      $4, $19, $0;
    jal        I2b_132140;
    addiu     $5, $0, 0x271;
    daddu      $16, $2, $0;
    sw         $2, 0x48($19);
    b          L00132430;
    sw        $0, 0x0($16);
    nop;
  L00132408:
    bnel       $3, $0, L00132430;
    daddu     $16, $3, $0;
    daddu      $5, $16, $0;
    daddu      $6, $16, $0;
    jal        Mult_132178;
    daddu     $4, $19, $0;
    daddu      $3, $2, $0;
    sw         $2, 0x0($16);
    sw         $0, 0x0($3);
    daddu      $16, $3, $0;
  L00132430:
    andi       $2, $17, 0x1;
  L00132434:
    beqz       $2, L0013245C;
    sra       $17, $17, 1;
    daddu      $5, $18, $0;
    daddu      $4, $19, $0;
    jal        Mult_132178;
    daddu     $6, $16, $0;
    daddu      $4, $19, $0;
    daddu      $5, $18, $0;
    jal        _Bfree;
    daddu     $18, $2, $0;
  L0013245C:
    bnel       $17, $0, L00132408;
    lw        $3, 0x0($16);
    daddu      $2, $18, $0;
  L00132468:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $31, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
