#include "types.h"

extern void _lf_bind(void);
extern void sceSifCallRpc(void);

asm void sceSifGetIopAddr(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $19, 0x40($29);
    sd         $18, 0x30($29);
    daddu      $19, $4, $0;
    sd         $16, 0x10($29);
    daddu      $18, $5, $0;
    sd         $31, 0x50($29);
    daddu      $16, $6, $0;
    jal        _lf_bind;
    sd        $17, 0x20($29);
    bgez       $2, L0011F968;
    sltiu     $2, $16, 0x3;
    b          L0011FA00;
    lui       $2, (0xFFFF0000 >> 16);
  L0011F968:
    beqz       $2, L0011F9EC;
    lui       $17, 0x49;
    lui        $4, 0x49;
    addiu      $2, $17, -0x6280;
    sw         $19, -0x6280($17);
    daddu      $7, $2, $0;
    sw         $16, 0x4($2);
    addiu      $4, $4, -0x6080;
    addiu      $5, $0, 0x3;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x20;
    daddu      $9, $7, $0;
    addiu      $10, $0, 0x20;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0011F9BC;
    nop;
    lui        $2, (0xFFFEFFFF >> 16);
    b          L0011FA00;
    ori       $2, $2, (0xFFFEFFFF & 0xFFFF);
  L0011F9BC:
    bnez       $16, L0011F9D0;
    addiu     $2, $0, 0x1;
    lbu        $2, -0x6280($17);
    b          L0011F9FC;
    sb        $2, 0x0($18);
  L0011F9D0:
    bne        $16, $2, L0011F9E4;
    addiu     $2, $0, 0x2;
    lhu        $2, -0x6280($17);
    b          L0011F9FC;
    sh        $2, 0x0($18);
  L0011F9E4:
    beql       $16, $2, L0011F9F8;
    lw        $2, -0x6280($17);
  L0011F9EC:
    lui        $2, (0xFFFEFFFE >> 16);
    b          L0011FA00;
    ori       $2, $2, (0xFFFEFFFE & 0xFFFF);
  L0011F9F8:
    sw         $2, 0x0($18);
  L0011F9FC:
    daddu      $2, $0, $0;
  L0011FA00:
    ld         $31, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
