#include "types.h"

extern void strlen(void);
extern void OperatorNewArray_100900(void);
extern void SharedArrayPtrCtor_102b30(void);
extern void strcpy(void);
extern void ThrowException_1025c0(void);
extern void StringReplace_106f90(void);

asm void StringReplaceFromStringMaybe_107cd0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $31, 0x90($29);
    sq         $30, 0x80($29);
    sq         $23, 0x70($29);
    addu       $30, $29, $0;
    sq         $22, 0x60($29);
    sq         $21, 0x50($29);
    sq         $20, 0x40($29);
    daddu      $21, $6, $0;
    sq         $19, 0x30($29);
    daddu      $20, $5, $0;
    sq         $18, 0x20($29);
    daddu      $19, $4, $0;
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    sw         $9, 0xA4($30);
    lw         $2, 0x0($7);
    andi       $2, $2, 0x1;
    bnez       $2, L00107D34;
    daddu     $18, $8, $0;
    lbu        $2, 0x0($7);
    addiu      $17, $7, 0x1;
    dsll32     $2, $2, 24;
    b          L00107D3C;
    dsrl32    $16, $2, 25;
  L00107D34:
    lw         $17, 0x8($7);
    lw         $16, 0x4($7);
  L00107D3C:
    sltu       $1, $16, $18;
    beql       $1, $0, L00107DB4;
    lw        $2, 0xA4($30);
    lui        $2, 0x47;
    lui        $4, 0x45;
    addiu      $2, $2, -0x80;
    addiu      $22, $30, 0xA8;
    sw         $2, 0xA8($30);
    addiu      $4, $4, 0x5AA0;
    jal        strlen;
    addiu     $23, $30, 0xAC;
    jal        OperatorNewArray_100900;
    addiu     $4, $2, 0x1;
    daddu      $5, $2, $0;
    jal        SharedArrayPtrCtor_102b30;
    daddu     $4, $23, $0;
    lw         $4, 0x0($23);
    lui        $5, 0x45;
    jal        strcpy;
    addiu     $5, $5, 0x5AA0;
    lui        $2, 0x47;
    lui        $4, 0x45;
    addiu      $2, $2, -0x90;
    lui        $6, 0x10;
    addiu      $4, $4, 0x5AC0;
    sw         $2, 0xA8($30);
    daddu      $5, $22, $0;
    jal        ThrowException_1025c0;
    addiu     $6, $6, 0x74C0;
    lw         $2, 0xA4($30);
  L00107DB4:
    subu       $3, $16, $18;
    addu       $17, $17, $18;
    sltu       $1, $3, $2;
    beqz       $1, L00107DD0;
    sw        $3, 0xBC($30);
    b          L00107DD4;
    addiu     $2, $30, 0xBC;
  L00107DD0:
    addiu      $2, $30, 0xA4;
  L00107DD4:
    lw         $2, 0x0($2);
    daddu      $4, $19, $0;
    lb         $9, 0xB8($30);
    daddu      $5, $20, $0;
    daddu      $6, $21, $0;
    daddu      $7, $17, $0;
    addu       $8, $17, $2;
    jal        StringReplace_106f90;
    sw        $2, 0xA4($30);
    addu       $29, $30, $0;
    ld         $31, 0x90($29);
    lq         $30, 0x80($29);
    lq         $23, 0x70($29);
    lq         $22, 0x60($29);
    lq         $21, 0x50($29);
    lq         $20, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0xC0;
}

