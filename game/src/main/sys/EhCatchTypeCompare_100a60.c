#include "types.h"

asm void EhCatchTypeCompare_100a60(void)
{
    .set noreorder;
    sd         $0, 0x0($6);
    bnez       $5, L00100A74;
    daddu     $2, $5, $0;
    b          L00100CA4;
    addiu     $2, $0, 0x1;
  L00100A74:
    lb         $7, 0x0($5);
    addiu      $3, $0, 0x50;
    bnel       $7, $3, L00100AF0;
    lb        $7, 0x0($4);
    addiu      $2, $2, 0x1;
    addiu      $3, $0, 0x43;
    lb         $7, 0x0($2);
    bnel       $7, $3, L00100AA0;
    lb        $7, 0x0($2);
    addiu      $2, $2, 0x1;
    lb         $7, 0x0($2);
  L00100AA0:
    addiu      $3, $0, 0x56;
    bnel       $7, $3, L00100AB4;
    lb        $3, 0x0($2);
    addiu      $2, $2, 0x1;
    lb         $3, 0x0($2);
  L00100AB4:
    addiu      $2, $0, 0x76;
    bnel       $3, $2, L00100AEC;
    daddu     $2, $5, $0;
    lb         $3, 0x0($4);
    addiu      $2, $0, 0x50;
    beql       $3, $2, L00100CA4;
    addiu     $2, $0, 0x1;
    addiu      $2, $0, 0x2A;
    bne        $3, $2, L00100AE8;
    nop;
    addiu      $2, $0, 0x1;
    b          L00100CA4;
    nop;
  L00100AE8:
    daddu      $2, $5, $0;
  L00100AEC:
    lb         $7, 0x0($4);
  L00100AF0:
    addiu      $3, $0, 0x21;
    beql       $7, $3, L00100B20;
    lb        $7, 0x0($4);
    addiu      $3, $0, 0x2A;
    beq        $7, $3, L00100B1C;
    nop;
    addiu      $5, $0, 0x52;
    addiu      $9, $0, 0x43;
    addiu      $7, $0, 0x56;
    b          L00100C4C;
    addiu     $6, $0, 0x50;
  L00100B1C:
    lb         $7, 0x0($4);
  L00100B20:
    lb         $3, 0x0($2);
    addiu      $4, $4, 0x1;
    beq        $7, $3, L00100B38;
    addiu     $2, $2, 0x1;
    b          L00100CA4;
    daddu     $2, $0, $0;
  L00100B38:
    lb         $3, 0x0($2);
    lb         $8, 0x0($4);
    bne        $8, $3, L00100B94;
    addiu     $2, $2, 0x1;
    addiu      $7, $0, 0x21;
    bne        $8, $7, L00100B38;
    addiu     $4, $4, 0x1;
    lb         $5, 0x0($4);
    beq        $5, $7, L00100B88;
    daddu     $8, $0, $0;
  L00100B60:
    dsll32     $3, $5, 24;
    dsll       $2, $8, 2;
    addiu      $4, $4, 0x1;
    daddu      $2, $2, $8;
    lb         $5, 0x0($4);
    dsra32     $3, $3, 24;
    dsll       $2, $2, 1;
    daddu      $2, $3, $2;
    bne        $5, $7, L00100B60;
    daddiu    $8, $2, -0x30;
  L00100B88:
    sd         $8, 0x0($6);
    b          L00100CA4;
    addiu     $2, $0, 0x1;
  L00100B94:
    lb         $2, 0x0($4);
    addiu      $3, $0, 0x21;
    addiu      $4, $4, 0x1;
    nop;
    nop;
    bne        $2, $3, L00100B94;
    nop;
  L00100BB0:
    lb         $2, 0x0($4);
    addiu      $4, $4, 0x1;
    nop;
    nop;
    nop;
    bne        $2, $3, L00100BB0;
    nop;
    lb         $2, 0x0($4);
    bnel       $2, $0, L00100B38;
    addiu     $2, $5, 0x1;
    b          L00100CA4;
    daddu     $2, $0, $0;
  L00100BE0:
    addiu      $2, $2, 0x1;
    lb         $3, 0x0($2);
    bne        $3, $9, L00100C08;
    addiu     $4, $4, 0x1;
    lb         $3, 0x0($4);
    bne        $3, $9, L00100C00;
    nop;
    addiu      $4, $4, 0x1;
  L00100C00:
    addiu      $2, $2, 0x1;
    nop;
  L00100C08:
    lb         $8, 0x0($4);
    bnel       $8, $9, L00100C1C;
    lb        $3, 0x0($2);
    b          L00100CA4;
    daddu     $2, $0, $0;
  L00100C1C:
    bne        $3, $7, L00100C38;
    nop;
    bne        $8, $7, L00100C30;
    nop;
    addiu      $4, $4, 0x1;
  L00100C30:
    addiu      $2, $2, 0x1;
    nop;
  L00100C38:
    lb         $3, 0x0($4);
    bnel       $3, $7, L00100C50;
    lb        $8, 0x0($4);
    b          L00100CA4;
    daddu     $2, $0, $0;
  L00100C4C:
    lb         $8, 0x0($4);
  L00100C50:
    beq        $8, $6, L00100C60;
    nop;
    bne        $8, $5, L00100C70;
    nop;
  L00100C60:
    lb         $3, 0x0($2);
    beq        $8, $3, L00100BE0;
    nop;
    nop;
  L00100C70:
    lb         $3, 0x0($2);
    bne        $8, $3, L00100CA0;
    nop;
  L00100C7C:
    bnel       $8, $0, L00100C8C;
    addiu     $4, $4, 0x1;
    b          L00100CA4;
    addiu     $2, $0, 0x1;
  L00100C8C:
    addiu      $2, $2, 0x1;
    lb         $8, 0x0($4);
    lb         $3, 0x0($2);
    beq        $8, $3, L00100C7C;
    nop;
  L00100CA0:
    daddu      $2, $0, $0;
  L00100CA4:
    jr         $31;
    nop;
}

