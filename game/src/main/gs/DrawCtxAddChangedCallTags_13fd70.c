#include "types.h"

asm void DrawCtxAddChangedCallTags_13fd70(void)
{
    .set noreorder;
    addiu      $3, $0, 0x6;
    bnel       $6, $3, L0013FEF0;
    lw        $3, 0x3C44($4);
    lw         $12, 0x0($5);
    lw         $11, 0x4($5);
    lw         $8, 0x8($5);
    lw         $7, 0xC($5);
    lw         $6, 0x10($5);
    lw         $3, 0x14($5);
    lw         $5, 0x3C48($4);
    beql       $5, $12, L0013FDD0;
    lw        $5, 0x3C4C($4);
    lq         $10, -0x7330($28);
    dsll32     $9, $12, 4;
    lw         $5, 0x4($4);
    dsrl32     $9, $9, 4;
    sq         $10, 0x0($5);
    lw         $5, 0x4($4);
    sw         $9, 0x4($5);
    lw         $5, 0x4($4);
    addiu      $5, $5, 0x10;
    sw         $5, 0x4($4);
    sw         $12, 0x3C48($4);
    lw         $5, 0x3C4C($4);
  L0013FDD0:
    beql       $5, $11, L0013FE08;
    lw        $5, 0x3C50($4);
    lq         $10, -0x7330($28);
    dsll32     $9, $11, 4;
    lw         $5, 0x4($4);
    dsrl32     $9, $9, 4;
    sq         $10, 0x0($5);
    lw         $5, 0x4($4);
    sw         $9, 0x4($5);
    lw         $5, 0x4($4);
    addiu      $5, $5, 0x10;
    sw         $5, 0x4($4);
    sw         $11, 0x3C4C($4);
    lw         $5, 0x3C50($4);
  L0013FE08:
    beql       $5, $8, L0013FE40;
    lw        $5, 0x3C54($4);
    lq         $10, -0x7330($28);
    dsll32     $9, $8, 4;
    lw         $5, 0x4($4);
    dsrl32     $9, $9, 4;
    sq         $10, 0x0($5);
    lw         $5, 0x4($4);
    sw         $9, 0x4($5);
    lw         $5, 0x4($4);
    addiu      $5, $5, 0x10;
    sw         $5, 0x4($4);
    sw         $8, 0x3C50($4);
    lw         $5, 0x3C54($4);
  L0013FE40:
    beql       $5, $7, L0013FE78;
    lw        $5, 0x3C58($4);
    lq         $9, -0x7330($28);
    dsll32     $8, $7, 4;
    lw         $5, 0x4($4);
    dsrl32     $8, $8, 4;
    sq         $9, 0x0($5);
    lw         $5, 0x4($4);
    sw         $8, 0x4($5);
    lw         $5, 0x4($4);
    addiu      $5, $5, 0x10;
    sw         $5, 0x4($4);
    sw         $7, 0x3C54($4);
    lw         $5, 0x3C58($4);
  L0013FE78:
    beql       $5, $6, L0013FEB0;
    lw        $5, 0x3C5C($4);
    lq         $8, -0x7330($28);
    dsll32     $7, $6, 4;
    lw         $5, 0x4($4);
    dsrl32     $7, $7, 4;
    sq         $8, 0x0($5);
    lw         $5, 0x4($4);
    sw         $7, 0x4($5);
    lw         $5, 0x4($4);
    addiu      $5, $5, 0x10;
    sw         $5, 0x4($4);
    sw         $6, 0x3C58($4);
    lw         $5, 0x3C5C($4);
  L0013FEB0:
    beq        $5, $3, L0013FF9C;
    nop;
    lq         $7, -0x7330($28);
    dsll32     $6, $3, 4;
    lw         $5, 0x4($4);
    dsrl32     $6, $6, 4;
    sq         $7, 0x0($5);
    lw         $5, 0x4($4);
    sw         $6, 0x4($5);
    lw         $5, 0x4($4);
    addiu      $5, $5, 0x10;
    sw         $5, 0x4($4);
    sw         $3, 0x3C5C($4);
    b          L0013FF9C;
    nop;
    lw         $3, 0x3C44($4);
  L0013FEF0:
    beq        $3, $6, L0013FF94;
    addiu     $10, $4, 0x3C48;
    b          L0013FF3C;
    daddu     $11, $6, $0;
    lw         $9, 0x0($5);
  L0013FF04:
    addiu      $11, $11, -0x1;
    lq         $8, -0x7330($28);
    lw         $3, 0x4($4);
    dsll32     $7, $9, 4;
    addiu      $5, $5, 0x4;
    dsrl32     $7, $7, 4;
    sq         $8, 0x0($3);
    lw         $3, 0x4($4);
    sw         $7, 0x4($3);
    lw         $3, 0x4($4);
    addiu      $3, $3, 0x10;
    sw         $3, 0x4($4);
    sw         $9, 0x0($10);
    addiu      $10, $10, 0x4;
  L0013FF3C:
    bgtzl      $11, L0013FF04;
    lw        $9, 0x0($5);
    b          L0013FF9C;
    sw        $6, 0x3C44($4);
    lw         $9, 0x0($5);
  L0013FF50:
    lw         $3, 0x0($10);
    beql       $3, $9, L0013FF8C;
    addiu     $6, $6, -0x1;
    lq         $8, -0x7330($28);
    dsll32     $7, $9, 4;
    lw         $3, 0x4($4);
    dsrl32     $7, $7, 4;
    sq         $8, 0x0($3);
    lw         $3, 0x4($4);
    sw         $7, 0x4($3);
    lw         $3, 0x4($4);
    addiu      $3, $3, 0x10;
    sw         $3, 0x4($4);
    sw         $9, 0x0($10);
    addiu      $6, $6, -0x1;
  L0013FF8C:
    addiu      $5, $5, 0x4;
    addiu      $10, $10, 0x4;
  L0013FF94:
    bgtzl      $6, L0013FF50;
    lw        $9, 0x0($5);
  L0013FF9C:
    jr         $31;
    nop;
}

