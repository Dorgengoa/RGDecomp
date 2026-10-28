#include "types.h"

extern void strlen(void);
extern void OperatorNewArray_100900(void);
extern void OperatorNew_100990(void);
extern void OperatorDeleteArray_100820(void);
extern void ThrowException_1025c0(void);
extern void EhEndCatch_101010(void);
extern void strcpy(void);
extern void memcpy(void);
extern void OperatorDelete_100840(void);

asm void StringReserve_107e80(void)
{
    .set noreorder;
    addiu      $29, $29, -0xE0;
    lui        $1, (0x7FFFFFFF >> 16);
    sd         $31, 0x80($29);
    ori        $1, $1, (0x7FFFFFFF & 0xFFFF);
    sq         $30, 0x70($29);
    sq         $22, 0x60($29);
    addu       $30, $29, $0;
    sq         $21, 0x50($29);
    sq         $20, 0x40($29);
    sq         $19, 0x30($29);
    sq         $18, 0x20($29);
    daddu      $18, $5, $0;
    sq         $17, 0x10($29);
    sltu       $1, $18, $1;
    sq         $16, 0x0($29);
    bnez       $1, L00107F7C;
    daddu     $17, $4, $0;
    lui        $2, 0x47;
    lui        $4, 0x45;
    addiu      $2, $2, -0x80;
    addiu      $19, $30, 0xD0;
    sw         $2, 0xD0($30);
    addiu      $4, $4, 0x5C10;
    jal        strlen;
    addiu     $16, $30, 0xD4;
    jal        OperatorNewArray_100900;
    addiu     $4, $2, 0x1;
    sw         $2, 0x0($16);
    sw         $0, 0x4($16);
    lw         $2, 0x0($16);
    beqz       $2, L00107F48;
    sw        $29, 0xA4($30);
    jal        OperatorNew_100990;
    addiu     $4, $0, 0x4;
    beql       $2, $0, L00107F48;
    sw        $2, 0x4($16);
    addiu      $3, $0, 0x1;
    sw         $3, 0x0($2);
    sw         $2, 0x4($16);
    b          L00107F48;
    nop;
    jal        OperatorDeleteArray_100820;
    lw        $4, 0x0($16);
    daddu      $4, $0, $0;
    daddu      $5, $0, $0;
    jal        ThrowException_1025c0;
    daddu     $6, $0, $0;
    jal        EhEndCatch_101010;
    addiu     $4, $30, 0x90;
    lw         $29, 0xA4($30);
  L00107F48:
    lw         $4, 0x0($16);
    lui        $5, 0x45;
    jal        strcpy;
    addiu     $5, $5, 0x5C10;
    lui        $2, 0x47;
    lui        $4, 0x45;
    addiu      $2, $2, -0xA0;
    lui        $6, 0x10;
    addiu      $4, $4, 0x5B20;
    sw         $2, 0x0($19);
    daddu      $5, $19, $0;
    jal        ThrowException_1025c0;
    addiu     $6, $6, 0x7430;
  L00107F7C:
    lw         $4, 0x0($17);
    andi       $3, $4, 0x1;
    sltu       $21, $0, $3;
    bnel       $21, $0, L00107FA4;
    lw        $16, 0x4($17);
    lbu        $3, 0x0($17);
    addiu      $5, $0, 0xB;
    dsll32     $3, $3, 24;
    b          L00107FAC;
    dsrl32    $16, $3, 25;
  L00107FA4:
    dsll32     $3, $4, 0;
    dsrl32     $5, $3, 1;
  L00107FAC:
    sltu       $1, $18, $16;
    beql       $1, $0, L00107FC0;
    addiu     $3, $18, 0x1;
    daddu      $18, $16, $0;
    addiu      $3, $18, 0x1;
  L00107FC0:
    sltiu      $1, $3, 0xC;
    beql       $1, $0, L00107FD4;
    addiu     $4, $18, 0x10;
    b          L00107FDC;
    addiu     $18, $0, 0xB;
  L00107FD4:
    addiu      $3, $0, -0x10;
    and        $18, $4, $3;
  L00107FDC:
    beq        $18, $5, L001080E0;
    nop;
    addiu      $2, $0, 0xB;
    bnel       $18, $2, L00108000;
    sltu      $1, $5, $18;
    lw         $19, 0x8($17);
    addiu      $20, $17, 0x1;
    b          L0010804C;
    daddu     $22, $0, $0;
  L00108000:
    beql       $1, $0, L00108018;
    daddu     $4, $18, $0;
    jal        OperatorNew_100990;
    daddu     $4, $18, $0;
    b          L00108038;
    daddu     $20, $2, $0;
  L00108018:
    jal        OperatorNew_100990;
    sw        $29, 0xC4($30);
    b          L00108038;
    daddu     $20, $2, $0;
    jal        EhEndCatch_101010;
    addiu     $4, $30, 0xB0;
    b          L001080E0;
    lw        $29, 0xC4($30);
  L00108038:
    beqz       $21, L00108048;
    daddiu    $22, $0, 0x1;
    b          L0010804C;
    lw        $19, 0x8($17);
  L00108048:
    addiu      $19, $17, 0x1;
  L0010804C:
    daddu      $4, $20, $0;
    daddu      $5, $19, $0;
    jal        memcpy;
    daddu     $6, $16, $0;
    addu       $3, $20, $16;
    beqz       $21, L00108070;
    sb        $0, 0x0($3);
    jal        OperatorDelete_100840;
    daddu     $4, $19, $0;
  L00108070:
    lw         $5, 0x0($17);
    addiu      $3, $0, -0x2;
    andi       $4, $22, 0x1;
    and        $3, $5, $3;
    or         $3, $3, $4;
    bnez       $22, L001080AC;
    sw        $3, 0x0($17);
    andi       $3, $16, 0x7F;
    lbu        $5, 0x0($17);
    sll        $4, $3, 1;
    addiu      $3, $0, -0xFF;
    and        $3, $5, $3;
    or         $3, $3, $4;
    b          L001080E0;
    sb        $3, 0x0($17);
  L001080AC:
    dsll32     $3, $18, 1;
    sw         $20, 0x8($17);
    dsrl32     $3, $3, 1;
    sw         $16, 0x4($17);
    sll        $5, $3, 1;
    lw         $6, 0x0($17);
    addiu      $3, $0, -0x1;
    dsll32     $4, $3, 0;
    addiu      $3, $0, 0x1;
    or         $3, $3, $4;
    and        $3, $6, $3;
    or         $3, $3, $5;
    sw         $3, 0x0($17);
  L001080E0:
    addu       $29, $30, $0;
    ld         $31, 0x80($29);
    lq         $30, 0x70($29);
    lq         $22, 0x60($29);
    lq         $21, 0x50($29);
    lq         $20, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0xE0;
}

