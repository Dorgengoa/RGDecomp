#include "types.h"

extern void IosInit_102a50(void);

asm void WostreamCtor_1044e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x30($29);
    sq         $18, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $16, $5, $0;
    dsll32     $2, $16, 16;
    dsra32     $2, $2, 16;
    beqz       $2, L00104528;
    daddu     $17, $4, $0;
    addiu      $2, $17, 0x8;
    lui        $3, 0x47;
    sw         $2, 0x0($17);
    addiu      $3, $3, -0x260;
    lui        $2, 0x47;
    sw         $3, 0x8($17);
    addiu      $2, $2, -0x228;
    sw         $2, 0x8($17);
  L00104528:
    lui        $2, 0x47;
    lui        $4, 0x47;
    addiu      $2, $2, -0x210;
    addiu      $4, $4, -0x204;
    sw         $2, 0x4($17);
    daddu      $5, $6, $0;
    lw         $3, 0x0($17);
    addiu      $2, $17, 0x8;
    sw         $4, 0x0($3);
    lw         $3, 0x0($17);
    subu       $2, $2, $3;
    sw         $2, 0x48($3);
    lw         $18, 0x0($17);
    jal        IosInit_102a50;
    daddu     $4, $18, $0;
    sw         $0, 0x40($18);
    addiu      $3, $0, 0x20;
    sh         $3, 0x44($18);
    daddu      $2, $17, $0;
    ld         $31, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

