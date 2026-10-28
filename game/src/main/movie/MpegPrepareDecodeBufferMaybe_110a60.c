#include "types.h"

asm void MpegPrepareDecodeBufferMaybe_110a60(void)
{
    .set noreorder;
    daddu      $7, $4, $0;
    addiu      $11, $0, 0x4;
    lw         $9, 0x184($7);
    addiu      $12, $0, 0x2;
    lw         $10, 0x160($7);
    daddu      $8, $0, $0;
    xori       $2, $9, 0x3;
    daddu      $13, $0, $0;
    addiu      $14, $0, 0x3;
    bne        $10, $14, L00110B98;
    movz      $11, $12, $2;
    lw         $2, 0xB4($7);
    lw         $3, 0xB8($7);
    lw         $5, 0x1D4($7);
    lw         $6, 0x1E4($7);
    addu       $2, $2, $3;
    lw         $4, 0x1F4($7);
    slt        $2, $2, $11;
    sw         $5, 0x1D0($7);
    sw         $6, 0x1E0($7);
    bnez       $2, L00110AC4;
    sw        $4, 0x1F0($7);
    sw         $0, 0xFC($7);
    sw         $0, 0x1B8($7);
    sw         $0, 0x1B4($7);
  L00110AC4:
    lw         $2, 0xFC($7);
    bnel       $2, $0, L00110AE0;
    lw        $2, 0x1B4($7);
    lw         $2, 0x1B8($7);
    beql       $2, $0, L00110B08;
    sw        $0, 0xFC($7);
    lw         $2, 0x1B4($7);
  L00110AE0:
    bnel       $2, $0, L00110B08;
    sw        $0, 0xFC($7);
    lw         $2, 0x1C8($7);
    lw         $4, 0x1D8($7);
    sw         $0, 0x28($2);
    lw         $3, 0x1E8($7);
    sw         $0, 0x28($4);
    sw         $0, 0x28($3);
    lw         $9, 0x184($7);
    sw         $0, 0xFC($7);
  L00110B08:
    addiu      $2, $0, 0x3;
    bne        $9, $2, L00110B3C;
    sw        $0, 0x1B8($7);
    lw         $3, 0x1C8($7);
    addiu      $4, $0, 0x1;
    lw         $2, 0x28($3);
    beql       $2, $4, L00110B84;
    lw        $3, 0x1CC($7);
    lw         $2, 0x1B4($7);
    beqz       $2, L00110C50;
    addiu     $2, $0, 0x2;
    b          L00110B84;
    lw        $3, 0x1CC($7);
  L00110B3C:
    lw         $2, 0x1D8($7);
    addiu      $3, $0, 0x1;
    lw         $4, 0x28($2);
    bnel       $4, $3, L00110B64;
    lw        $2, 0x1B4($7);
    lw         $2, 0x1E8($7);
    lw         $3, 0x28($2);
    beql       $3, $4, L00110B70;
    lw        $2, 0x1DC($7);
    lw         $2, 0x1B4($7);
  L00110B64:
    beqz       $2, L00110C50;
    addiu     $2, $0, 0x2;
    lw         $2, 0x1DC($7);
  L00110B70:
    addiu      $3, $0, 0x1;
    lw         $4, 0x28($2);
    bne        $4, $3, L00110C50;
    addiu     $2, $0, 0x2;
    lw         $3, 0x1EC($7);
  L00110B84:
    daddu      $13, $4, $0;
    lw         $2, 0x28($3);
    xori       $2, $2, 0x1;
    b          L00110C4C;
    movn      $13, $0, $2;
  L00110B98:
    bnel       $5, $0, L00110BD4;
    lw        $2, 0x1CC($7);
    lw         $6, 0x1C8($7);
    lw         $4, 0x1CC($7);
    sw         $6, 0x1CC($7);
    lw         $6, 0x1D8($7);
    lw         $3, 0x1DC($7);
    sw         $6, 0x1DC($7);
    lw         $6, 0x1E8($7);
    lw         $2, 0x1EC($7);
    sw         $4, 0x1C8($7);
    sw         $3, 0x1D8($7);
    sw         $2, 0x1E8($7);
    sw         $6, 0x1EC($7);
    lw         $2, 0x1CC($7);
  L00110BD4:
    lw         $4, 0x1DC($7);
    lw         $3, 0x1EC($7);
    sw         $2, 0x1D0($7);
    sw         $4, 0x1E0($7);
    bne        $9, $14, L00110C00;
    sw        $3, 0x1F0($7);
    bnel       $10, $12, L00110C4C;
    addiu     $13, $0, 0x1;
    lw         $2, 0x1C8($7);
    b          L00110C3C;
    addiu     $4, $0, 0x1;
  L00110C00:
    xori       $2, $9, 0x1;
    addiu      $6, $0, 0x1;
    movn       $3, $4, $2;
    bne        $10, $12, L00110C48;
    daddu     $2, $3, $0;
    beql       $5, $0, L00110C2C;
    lw        $2, 0x1D8($7);
    lw         $2, 0x28($2);
    beql       $2, $6, L00110C4C;
    addiu     $13, $0, 0x1;
    lw         $2, 0x1D8($7);
  L00110C2C:
    lw         $4, 0x28($2);
    bne        $4, $6, L00110C50;
    addiu     $2, $0, 0x2;
    lw         $2, 0x1E8($7);
  L00110C3C:
    lw         $3, 0x28($2);
    bne        $3, $4, L00110C50;
    addiu     $2, $0, 0x2;
  L00110C48:
    addiu      $13, $0, 0x1;
  L00110C4C:
    addiu      $2, $0, 0x2;
  L00110C50:
    beq        $9, $2, L00110C84;
    slti      $2, $9, 0x3;
    beqz       $2, L00110C70;
    addiu     $2, $0, 0x1;
    beql       $9, $2, L00110C88;
    lw        $8, 0x1E0($7);
    b          L00110C8C;
    sw        $0, 0x28($8);
  L00110C70:
    addiu      $2, $0, 0x3;
    beql       $9, $2, L00110C88;
    lw        $8, 0x1D0($7);
    b          L00110C8C;
    sw        $0, 0x28($8);
  L00110C84:
    lw         $8, 0x1F0($7);
  L00110C88:
    sw         $0, 0x28($8);
  L00110C8C:
    daddu      $2, $13, $0;
    ld         $3, 0x838($7);
    lw         $4, 0x160($7);
    sd         $3, 0x18($8);
    sw         $4, 0x2C($8);
    ld         $3, 0x840($7);
    lw         $4, 0x184($7);
    sd         $3, 0x20($8);
    sw         $4, 0x30($8);
    lw         $3, 0x14C($7);
    sw         $3, 0x34($8);
    lw         $4, 0x198($7);
    sw         $4, 0x38($8);
    lw         $3, 0x188($7);
    sw         $3, 0x3C($8);
    lw         $4, 0x194($7);
    sw         $4, 0x40($8);
    lw         $3, 0x19C($7);
    sw         $3, 0x44($8);
    lw         $4, 0x1A0($7);
    sw         $4, 0x48($8);
    lw         $3, 0x1A4($7);
    sw         $3, 0x4C($8);
    lw         $4, 0x1A8($7);
    sw         $4, 0x50($8);
    lw         $3, 0x1AC($7);
    sw         $3, 0x54($8);
    lw         $4, 0x1B0($7);
    sw         $4, 0x58($8);
    lw         $3, 0x158($7);
    sw         $3, 0x5C($8);
    lw         $4, 0x15C($7);
    jr         $31;
    sw        $4, 0x60($8);
}
