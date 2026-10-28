#include "types.h"

extern void kputs_117a90(void);

asm void deci2Putchar(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x10($29);
    lui        $17, 0x44;
    sd         $16, 0x0($29);
    lw         $5, 0x6200($17);
    daddu      $16, $4, $0;
    sd         $31, 0x30($29);
    slti       $2, $5, 0x7E;
    bnez       $2, L00118080;
    sd        $18, 0x20($29);
    lui        $18, 0x48;
    sw         $0, 0x6200($17);
    addiu      $2, $18, 0x67C0;
    daddu      $4, $2, $0;
    jal        kputs_117a90;
    sb        $0, 0x7F($2);
    b          L00118084;
    lw        $5, 0x6200($17);
  L00118080:
    lui        $18, 0x48;
  L00118084:
    addiu      $2, $0, 0xA;
    bne        $16, $2, L001180C0;
    addiu     $2, $18, 0x67C0;
    addiu      $4, $18, 0x67C0;
    sw         $0, 0x6200($17);
    addu       $2, $5, $4;
    ld         $31, 0x30($29);
    sb         $16, 0x0($2);
    daddu      $3, $2, $0;
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    sb         $0, 0x1($3);
    j          kputs_117a90;
    addiu     $29, $29, 0x40;
  L001180C0:
    addiu      $3, $5, 0x1;
    sw         $3, 0x6200($17);
    addu       $2, $5, $2;
    sb         $16, 0x0($2);
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
