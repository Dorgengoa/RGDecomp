#include "types.h"

extern void _lf_bind(void);
extern void sceSifCallRpc(void);

asm void sceSifSetIopAddr(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $18, 0x30($29);
    sd         $17, 0x20($29);
    daddu      $18, $4, $0;
    sd         $16, 0x10($29);
    daddu      $17, $5, $0;
    sd         $31, 0x40($29);
    jal        _lf_bind;
    daddu     $16, $6, $0;
    bgez       $2, L0011FA54;
    lui       $7, 0x49;
    b          L0011FAE4;
    lui       $2, (0xFFFF0000 >> 16);
  L0011FA54:
    addiu      $3, $7, -0x6280;
    sw         $18, -0x6280($7);
    bnez       $16, L0011FA70;
    sw        $16, 0x4($3);
    lbu        $2, 0x0($17);
    b          L0011FAA0;
    sb        $2, 0x8($3);
  L0011FA70:
    addiu      $2, $0, 0x1;
    bne        $16, $2, L0011FA88;
    addiu     $2, $0, 0x2;
    lhu        $2, 0x0($17);
    b          L0011FAA0;
    sh        $2, 0x8($3);
  L0011FA88:
    beql       $16, $2, L0011FA9C;
    lw        $2, 0x0($17);
    lui        $2, (0xFFFEFFFE >> 16);
    b          L0011FAE4;
    ori       $2, $2, (0xFFFEFFFE & 0xFFFF);
  L0011FA9C:
    sw         $2, 0x8($3);
  L0011FAA0:
    addiu      $7, $7, -0x6280;
    lui        $4, 0x49;
    addiu      $4, $4, -0x6080;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x2;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x20;
    daddu      $9, $7, $0;
    addiu      $10, $0, 0x10;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    lui        $4, (0xFFFEFFFF >> 16);
    addiu      $3, $0, -0x1;
    slt        $3, $3, $2;
    ori        $4, $4, (0xFFFEFFFF & 0xFFFF);
    daddu      $2, $4, $0;
    movn       $2, $0, $3;
  L0011FAE4:
    ld         $31, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
