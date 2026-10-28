#include "types.h"

extern void CallocR_12df28(void);

asm void Balloc_131cf0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $17, 0x8($29);
    daddu      $17, $5, $0;
    sd         $31, 0x10($29);
    lw         $3, 0x4C($16);
    bnez       $3, L00131D28;
    addiu     $5, $0, 0x4;
    jal        CallocR_12df28;
    addiu     $6, $0, 0x10;
    daddu      $3, $2, $0;
    beqz       $3, L00131D80;
    sw        $3, 0x4C($16);
  L00131D28:
    sll        $2, $17, 2;
    addu       $4, $2, $3;
    lw         $3, 0x0($4);
    beqz       $3, L00131D48;
    addiu     $2, $0, 0x1;
    lw         $2, 0x0($3);
    b          L00131D74;
    sw        $2, 0x0($4);
  L00131D48:
    daddu      $4, $16, $0;
    sllv       $16, $2, $17;
    addiu      $5, $0, 0x1;
    sll        $6, $16, 2;
    jal        CallocR_12df28;
    addiu     $6, $6, 0x14;
    daddu      $3, $2, $0;
    beql       $3, $0, L00131D84;
    ld        $16, 0x0($29);
    sw         $17, 0x4($3);
    sw         $16, 0x8($3);
  L00131D74:
    sw         $0, 0x10($3);
    daddu      $2, $3, $0;
    sw         $0, 0xC($3);
  L00131D80:
    ld         $16, 0x0($29);
  L00131D84:
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
