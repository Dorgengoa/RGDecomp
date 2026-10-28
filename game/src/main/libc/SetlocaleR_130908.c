#include "types.h"

extern void strcmp(void);

asm void SetlocaleR_130908(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x0($29);
    daddu      $16, $6, $0;
    sd         $17, 0x8($29);
    daddu      $17, $4, $0;
    sd         $18, 0x10($29);
    daddu      $18, $5, $0;
    sd         $19, 0x18($29);
    daddu      $4, $16, $0;
    beqz       $16, L00130970;
    sd        $31, 0x20($29);
    lui        $19, 0x46;
    jal        strcmp;
    addiu     $5, $19, -0x7FC0;
    lui        $5, 0x46;
    addiu      $5, $5, -0x7FD0;
    beqz       $2, L00130960;
    daddu     $4, $16, $0;
    jal        strcmp;
    nop;
    bnez       $2, L00130978;
    daddu     $2, $0, $0;
  L00130960:
    sw         $16, 0x34($17);
    b          L00130974;
    sw        $18, 0x30($17);
    nop;
  L00130970:
    lui        $19, 0x46;
  L00130974:
    addiu      $2, $19, -0x7FC0;
  L00130978:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $31, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
