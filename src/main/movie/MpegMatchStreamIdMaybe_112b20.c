#include "types.h"

asm void MpegMatchStreamIdMaybe_112b20(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    lui        $3, 0x44;
    sd         $23, 0x70($29);
    andi       $2, $6, 0xFFFF;
    sd         $22, 0x60($29);
    dsrl       $14, $6, 24;
    sd         $21, 0x50($29);
    dsrl32     $13, $6, 0;
    sd         $20, 0x40($29);
    dsll32     $12, $2, 0;
    dsra32     $12, $12, 0;
    sd         $19, 0x30($29);
    addiu      $3, $3, 0x60C0;
    sd         $18, 0x20($29);
    daddu      $10, $0, $0;
    sd         $17, 0x10($29);
    daddu      $9, $0, $0;
    sd         $16, 0x0($29);
    ori        $11, $0, 0xFFFF;
    dsll       $11, $11, 24;
    ori        $23, $0, 0xFF00;
    dsll       $23, $23, 24;
    addiu      $22, $0, -0x1;
    dsrl       $22, $22, 24;
    addiu      $21, $0, -0x1;
    dsll32     $21, $21, 8;
    dsrl       $21, $21, 24;
    ori        $20, $0, 0xBD20;
    dsll       $20, $20, 24;
    ori        $19, $0, 0xBD80;
    dsll       $19, $19, 24;
    ori        $18, $0, 0xBD90;
    dsll       $18, $18, 24;
    ori        $17, $0, 0xBDA0;
    dsll       $17, $17, 24;
    ori        $16, $0, 0xFFE0;
    dsll       $16, $16, 24;
    ori        $25, $0, 0xFFF8;
    dsll       $25, $25, 24;
    ori        $24, $0, 0xF000;
    dsll       $24, $24, 24;
    ori        $15, $0, 0xC000;
    dsll       $15, $15, 24;
    ld         $7, 0x8($3);
  L00112BD0:
    beq        $7, $11, L00112C18;
    sltu      $2, $11, $7;
    bnez       $2, L00112BF0;
    nop;
    beql       $7, $23, L00112C84;
    ld        $8, 0x0($3);
    b          L00112CDC;
    addiu     $9, $9, 0x1;
  L00112BF0:
    bnel       $7, $22, L00112CDC;
    addiu     $9, $9, 0x1;
    ld         $2, 0x0($3);
    and        $7, $6, $21;
    bnel       $7, $2, L00112CDC;
    addiu     $9, $9, 0x1;
    sw         $9, 0x0($4);
    addiu      $10, $0, 0x1;
    b          L00112CD8;
    sw        $12, 0x0($5);
  L00112C18:
    ld         $8, 0x0($3);
    ori        $2, $0, 0xBD88;
    dsll       $2, $2, 24;
    beq        $8, $2, L00112C6C;
    sltu      $2, $2, $8;
    bnez       $2, L00112C4C;
    nop;
    beq        $8, $20, L00112C64;
    and       $7, $6, $16;
    beq        $8, $19, L00112C6C;
    and       $7, $6, $11;
    b          L00112C74;
    daddu     $2, $0, $0;
  L00112C4C:
    beq        $8, $18, L00112C70;
    and       $7, $6, $25;
    beq        $8, $17, L00112C6C;
    and       $7, $6, $11;
    b          L00112C74;
    daddu     $2, $0, $0;
  L00112C64:
    b          L00112C74;
    addiu     $2, $0, 0x1F;
  L00112C6C:
    and        $7, $6, $25;
  L00112C70:
    addiu      $2, $0, 0x7;
  L00112C74:
    bnel       $7, $8, L00112CDC;
    addiu     $9, $9, 0x1;
    b          L00112CC4;
    and       $2, $14, $2;
  L00112C84:
    ori        $2, $0, 0xE000;
    dsll       $2, $2, 24;
    bne        $8, $2, L00112CA0;
    nop;
    and        $7, $6, $24;
    b          L00112CB8;
    addiu     $2, $0, 0xF;
  L00112CA0:
    bne        $8, $15, L00112CB4;
    and       $7, $6, $7;
    and        $7, $6, $2;
    b          L00112CB8;
    addiu     $2, $0, 0x1F;
  L00112CB4:
    daddu      $2, $0, $0;
  L00112CB8:
    bnel       $7, $8, L00112CDC;
    addiu     $9, $9, 0x1;
    and        $2, $13, $2;
  L00112CC4:
    sw         $9, 0x0($4);
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    addiu      $10, $0, 0x1;
    sw         $2, 0x0($5);
  L00112CD8:
    addiu      $9, $9, 0x1;
  L00112CDC:
    sltiu      $2, $9, 0xA;
    beqz       $2, L00112CF0;
    addiu     $3, $3, 0x10;
    beql       $10, $0, L00112BD0;
    ld        $7, 0x8($3);
  L00112CF0:
    ld         $23, 0x70($29);
    daddu      $2, $10, $0;
    ld         $22, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
