#include "types.h"

extern void sceSifCallRpc(void);

asm void sceSdRemote_1229e8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x100;
    lui        $13, 0x49;
    sd         $16, 0x20($29);
    addiu      $3, $29, 0xD0;
    lui        $16, 0x49;
    sd         $19, 0x50($29);
    addiu      $2, $16, -0x2700;
    sd         $18, 0x40($29);
    sd         $5, 0xC8($29);
    daddu      $12, $16, $0;
    sd         $6, 0xD0($29);
    daddu      $18, $0, $0;
    sd         $31, 0x70($29);
    addiu      $6, $2, 0x4;
    sd         $20, 0x60($29);
    daddu      $19, $0, $0;
    sd         $7, 0xD8($29);
    addiu      $5, $0, 0x5;
    sd         $8, 0xE0($29);
    sd         $9, 0xE8($29);
    sd         $10, 0xF0($29);
    sd         $11, 0xF8($29);
    sw         $2, -0x2700($16);
    sd         $17, 0x30($29);
    lw         $17, -0x8($3);
    nop;
  L00122A50:
    addiu      $3, $3, 0x8;
    addiu      $5, $5, -0x1;
    lw         $2, -0x8($3);
    sw         $2, 0x0($6);
    addiu      $6, $6, 0x4;
    bgez       $5, L00122A50;
    nop;
    bnez       $4, L00122A80;
    daddu     $11, $0, $0;
    lui        $2, 0x44;
    addiu      $11, $0, 0x1;
    lw         $18, 0x78D0($2);
  L00122A80:
    ori        $2, $0, 0x8160;
    bne        $17, $2, L00122AEC;
    daddu     $20, $0, $0;
    addiu      $3, $12, -0x2700;
    lw         $2, 0x4($3);
    bnez       $2, L00122AC4;
    lw        $5, 0xC($3);
    lui        $2, 0x44;
    lw         $3, 0x8($3);
    lui        $4, 0x44;
    lw         $20, 0x78E8($2);
    sw         $3, 0x78E8($2);
    sw         $5, 0x78F4($4);
    daddu      $3, $28, $0;
    lui        $2, 0x44;
    b          L00122B24;
    sw        $3, 0x7900($2);
  L00122AC4:
    lui        $2, 0x44;
    lw         $3, 0x8($3);
    lui        $4, 0x44;
    lw         $20, 0x78EC($2);
    sw         $3, 0x78EC($2);
    sw         $5, 0x78F8($4);
    daddu      $3, $28, $0;
    lui        $2, 0x44;
    b          L00122B24;
    sw        $3, 0x7904($2);
  L00122AEC:
    ori        $2, $0, 0x8170;
    bne        $17, $2, L00122B28;
    ori       $2, $0, 0x8130;
    addiu      $3, $12, -0x2700;
    lui        $4, 0x44;
    lw         $6, 0x8($3);
    lui        $5, 0x44;
    lw         $2, 0x4($3);
    lw         $20, 0x78F0($4);
    sw         $2, 0x78F0($4);
    sw         $6, 0x78FC($5);
    daddu      $3, $28, $0;
    lui        $2, 0x44;
    sw         $3, 0x7908($2);
  L00122B24:
    ori        $2, $0, 0x8130;
  L00122B28:
    beq        $17, $2, L00122B44;
    sw        $0, 0x10($29);
    ori        $2, $0, 0x81A0;
    beq        $17, $2, L00122B44;
    ori       $2, $0, 0x81B0;
    bne        $17, $2, L00122B84;
    ori       $2, $0, 0x8140;
  L00122B44:
    beqz       $18, L00122B58;
    lui       $2, 0x44;
    lw         $3, 0x78D4($2);
    daddu      $19, $28, $0;
    daddu      $28, $3, $0;
  L00122B58:
    addiu      $9, $12, -0x2700;
    lw         $2, -0x2700($12);
    lw         $5, 0x4($9);
    daddu      $6, $11, $0;
    lw         $7, 0x8($9);
    addiu      $4, $13, -0x26C0;
    sw         $2, 0x0($29);
    or         $5, $17, $5;
    addiu      $8, $0, 0x40;
    b          L00122D14;
    addiu     $10, $0, 0x40;
  L00122B84:
    bne        $17, $2, L00122BE8;
    ori       $2, $0, 0x81C0;
    beqz       $18, L00122BA0;
    lui       $2, 0x44;
    lw         $3, 0x78D4($2);
    daddu      $19, $28, $0;
    daddu      $28, $3, $0;
  L00122BA0:
    addiu      $7, $12, -0x2700;
    daddu      $6, $11, $0;
    lw         $2, 0x8($7);
    addiu      $4, $13, -0x26C0;
    lw         $5, 0x4($7);
    addiu      $8, $0, 0x40;
    daddu      $9, $2, $0;
    sw         $2, 0x0($29);
    ori        $5, $5, 0x8140;
    addiu      $10, $0, 0x40;
    jal        sceSifCallRpc;
    daddu     $11, $18, $0;
    beqz       $18, L00122D38;
    ori       $2, $0, 0x8160;
    daddu      $2, $28, $0;
    daddu      $28, $19, $0;
    b          L00122D38;
    ori       $2, $0, 0x8160;
  L00122BE8:
    beq        $17, $2, L00122BF8;
    ori       $2, $0, 0x81D0;
    bne        $17, $2, L00122C8C;
    nop;
  L00122BF8:
    addiu      $16, $12, -0x2700;
    ori        $3, $0, 0x81D0;
    lw         $4, 0x4($16);
    lhu        $2, 0x8($16);
    bne        $17, $3, L00122C18;
    sh        $2, 0x2($4);
    lw         $2, 0x14($16);
    sw         $2, 0x4($4);
  L00122C18:
    lw         $9, 0xC($16);
    bnez       $9, L00122C2C;
    lw        $10, 0x10($16);
    addiu      $9, $29, 0x10;
    addiu      $10, $0, 0x4;
  L00122C2C:
    beqz       $18, L00122C40;
    lui       $2, 0x44;
    lw         $3, 0x78D4($2);
    daddu      $19, $28, $0;
    daddu      $28, $3, $0;
  L00122C40:
    lw         $8, 0x8($16);
    daddu      $6, $11, $0;
    lw         $7, 0x4($16);
    addiu      $4, $13, -0x26C0;
    addiu      $8, $8, 0x1;
    sw         $16, 0x0($29);
    sll        $8, $8, 3;
    daddu      $5, $17, $0;
    jal        sceSifCallRpc;
    daddu     $11, $18, $0;
    beql       $18, $0, L00122C7C;
    lw        $2, 0xC($16);
    daddu      $2, $28, $0;
    daddu      $28, $19, $0;
    lw         $2, 0xC($16);
  L00122C7C:
    beql       $2, $0, L00122D38;
    ori       $2, $0, 0x8160;
    b          L00122D30;
    lw        $2, 0x0($2);
  L00122C8C:
    lui        $2, (0xFFFF7000 >> 16);
    ori        $2, $2, (0xFFFF7000 & 0xFFFF);
    addu       $2, $17, $2;
    sltiu      $2, $2, 0xF1;
    beqz       $2, L00122CDC;
    nop;
    beqz       $18, L00122CB8;
    lui       $2, 0x44;
    lw         $3, 0x78D4($2);
    daddu      $19, $28, $0;
    daddu      $28, $3, $0;
  L00122CB8:
    addiu      $2, $12, -0x2700;
    daddu      $6, $11, $0;
    lw         $7, 0x4($2);
    addiu      $4, $13, -0x26C0;
    lw         $8, 0x8($2);
    daddu      $9, $2, $0;
    sw         $2, 0x0($29);
    b          L00122D10;
    daddu     $5, $17, $0;
  L00122CDC:
    beqz       $18, L00122CF0;
    lui       $2, 0x44;
    lw         $3, 0x78D4($2);
    daddu      $19, $28, $0;
    daddu      $28, $3, $0;
  L00122CF0:
    addiu      $2, $12, -0x2700;
    daddu      $6, $11, $0;
    daddu      $7, $2, $0;
    addiu      $4, $13, -0x26C0;
    sw         $2, 0x0($29);
    daddu      $5, $17, $0;
    addiu      $8, $0, 0x40;
    daddu      $9, $7, $0;
  L00122D10:
    addiu      $10, $0, 0x10;
  L00122D14:
    jal        sceSifCallRpc;
    daddu     $11, $18, $0;
    beqz       $18, L00122D30;
    lw        $2, -0x2700($16);
    daddu      $2, $28, $0;
    daddu      $28, $19, $0;
    lw         $2, -0x2700($16);
  L00122D30:
    sw         $2, 0x10($29);
    ori        $2, $0, 0x8160;
  L00122D38:
    beq        $17, $2, L00122D48;
    ori       $2, $0, 0x8170;
    bne        $17, $2, L00122D50;
    lw        $2, 0x10($29);
  L00122D48:
    sw         $20, 0x10($29);
    lw         $2, 0x10($29);
  L00122D50:
    ld         $31, 0x70($29);
    ld         $20, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x100;
}
