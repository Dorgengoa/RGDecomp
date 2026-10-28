#include "types.h"

asm void DecodeVarUInt_100ed0(void)
{
    .set noreorder;
    lbu        $3, 0x0($4);
    andi       $2, $3, 0x1;
    bnel       $2, $0, L00100EF0;
    lbu       $6, 0x1($4);
    srl        $3, $3, 1;
    addiu      $2, $4, 0x1;
    b          L00100F64;
    sw        $3, 0x0($5);
  L00100EF0:
    andi       $2, $3, 0x2;
    bnel       $2, $0, L00100F14;
    lbu       $7, 0x2($4);
    srl        $3, $3, 2;
    addiu      $2, $4, 0x2;
    sll        $3, $3, 8;
    or         $3, $3, $6;
    b          L00100F64;
    sw        $3, 0x0($5);
  L00100F14:
    andi       $2, $3, 0x4;
    bnel       $2, $0, L00100F40;
    srl       $2, $3, 3;
    srl        $2, $3, 3;
    sll        $3, $6, 8;
    sll        $6, $2, 16;
    or         $3, $6, $3;
    addiu      $2, $4, 0x3;
    or         $3, $7, $3;
    b          L00100F64;
    sw        $3, 0x0($5);
  L00100F40:
    sll        $3, $6, 16;
    sll        $6, $2, 24;
    or         $6, $6, $3;
    sll        $2, $7, 8;
    lbu        $3, 0x3($4);
    or         $6, $2, $6;
    addiu      $2, $4, 0x4;
    or         $3, $3, $6;
    sw         $3, 0x0($5);
  L00100F64:
    jr         $31;
    nop;
}

