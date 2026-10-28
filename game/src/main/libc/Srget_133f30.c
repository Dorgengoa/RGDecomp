#include "types.h"

extern void Srefill_133db0(void);

asm void Srget_133f30(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    sd         $31, 0x8($29);
    jal        Srefill_133db0;
    daddu     $16, $4, $0;
    bnel       $2, $0, L00133F68;
    addiu     $2, $0, -0x1;
    lw         $2, 0x4($16);
    lw         $3, 0x0($16);
    addiu      $2, $2, -0x1;
    sw         $2, 0x4($16);
    lbu        $2, 0x0($3);
    addiu      $3, $3, 0x1;
    sw         $3, 0x0($16);
  L00133F68:
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
