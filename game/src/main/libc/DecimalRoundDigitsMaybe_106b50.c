#include "types.h"

extern void StringCtorSubstrMaybe_107b70(void);
extern void StringFindChar_107550(void);
extern void StringInsertChar_107a60(void);
extern void StringResize_106e20(void);
extern void StringCopyCtor_107c30(void);
extern void StringDtor_107b00(void);

asm void DecimalRoundDigitsMaybe_106b50(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $31, 0x40($29);
    sq         $19, 0x30($29);
    sq         $18, 0x20($29);
    daddu      $19, $4, $0;
    sq         $17, 0x10($29);
    daddu      $18, $5, $0;
    sq         $16, 0x0($29);
    bgtz       $6, L00106B88;
    daddu     $17, $7, $0;
    sw         $0, 0x0($19);
    sw         $0, 0x4($19);
    b          L00106DFC;
    sw        $0, 0x8($19);
  L00106B88:
    daddu      $16, $6, $0;
    addiu      $4, $29, 0x58;
    daddu      $6, $0, $0;
    jal        StringCtorSubstrMaybe_107b70;
    daddu     $7, $16, $0;
    lh         $2, 0xC($18);
    sw         $2, 0x0($17);
    lw         $2, 0x0($18);
    andi       $2, $2, 0x1;
    sltu       $2, $0, $2;
    xori       $2, $2, 0x1;
    andi       $3, $2, 0xFF;
    beql       $3, $0, L00106BCC;
    lw        $2, 0x4($18);
    lbu        $2, 0x0($18);
    dsll32     $2, $2, 24;
    dsrl32     $2, $2, 25;
  L00106BCC:
    sltu       $1, $16, $2;
    beqz       $1, L00106D70;
    nop;
    beql       $3, $0, L00106BEC;
    lw        $2, 0x4($18);
    lbu        $2, 0x0($18);
    dsll32     $2, $2, 24;
    dsrl32     $2, $2, 25;
  L00106BEC:
    sltu       $2, $16, $2;
    bnez       $2, L00106C00;
    nop;
    b          L00106C54;
    addiu     $4, $0, -0x1;
  L00106C00:
    beql       $3, $0, L00106C0C;
    lw        $2, 0x8($18);
    addiu      $2, $18, 0x1;
  L00106C0C:
    addu       $2, $2, $16;
    lb         $2, 0x0($2);
    slti       $1, $2, 0x6;
    bnel       $1, $0, L00106C28;
    slti      $1, $2, 0x5;
    b          L00106C54;
    addiu     $4, $0, 0x1;
  L00106C28:
    beql       $1, $0, L00106C38;
    addiu     $6, $16, 0x1;
    b          L00106C54;
    addiu     $4, $0, -0x1;
  L00106C38:
    daddu      $4, $18, $0;
    jal        StringFindChar_107550;
    daddu     $5, $0, $0;
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L00106C54;
    addiu     $4, $0, 0x1;
    daddu      $4, $0, $0;
  L00106C54:
    bltz       $4, L00106D70;
    nop;
    lw         $2, 0x58($29);
    andi       $2, $2, 0x1;
    bnel       $2, $0, L00106C80;
    lw        $3, 0x60($29);
    lbu        $2, 0x58($29);
    addiu      $3, $29, 0x59;
    dsll32     $2, $2, 24;
    b          L00106C84;
    dsrl32    $2, $2, 25;
  L00106C80:
    lw         $2, 0x5C($29);
  L00106C84:
    addu       $3, $3, $2;
    xori       $2, $4, 0x1;
    addiu      $5, $3, -0x1;
    bnez       $4, L00106CB4;
    sltiu     $2, $2, 0x1;
    lb         $3, 0x0($5);
    bgez       $3, L00106CB0;
    andi      $2, $3, 0x1;
    beql       $2, $0, L00106CB4;
    sltu      $2, $0, $2;
    addiu      $2, $2, -0x2;
  L00106CB0:
    sltu       $2, $0, $2;
  L00106CB4:
    beqz       $2, L00106D70;
    nop;
  L00106CBC:
    dsll32     $4, $5, 0;
    dsra32     $4, $4, 0;
    lb         $2, 0x0($4);
    slti       $1, $2, 0x9;
    beql       $1, $0, L00106CE0;
    sb        $0, 0x0($4);
    addiu      $2, $2, 0x1;
    b          L00106D70;
    sb        $2, 0x0($4);
  L00106CE0:
    lw         $2, 0x58($29);
    andi       $2, $2, 0x1;
    sltu       $2, $0, $2;
    xori       $2, $2, 0x1;
    andi       $3, $2, 0xFF;
    beql       $3, $0, L00106D00;
    lw        $2, 0x60($29);
    addiu      $2, $29, 0x59;
  L00106D00:
    bnel       $4, $2, L00106D64;
    dsll32    $2, $5, 0;
    beql       $3, $0, L00106D14;
    lw        $6, 0x60($29);
    addiu      $6, $29, 0x59;
  L00106D14:
    addiu      $4, $29, 0x70;
    addiu      $5, $29, 0x58;
    jal        StringInsertChar_107a60;
    addiu     $7, $0, 0x1;
    lw         $2, 0x58($29);
    andi       $2, $2, 0x1;
    beql       $2, $0, L00106D3C;
    lbu       $2, 0x58($29);
    b          L00106D44;
    lw        $2, 0x5C($29);
  L00106D3C:
    dsll32     $2, $2, 24;
    dsrl32     $2, $2, 25;
  L00106D44:
    addiu      $5, $2, -0x1;
    addiu      $4, $29, 0x58;
    jal        StringResize_106e20;
    daddu     $6, $0, $0;
    lw         $2, 0x0($17);
    addiu      $2, $2, 0x1;
    b          L00106D70;
    sw        $2, 0x0($17);
  L00106D64:
    dsra32     $2, $2, 0;
    b          L00106CBC;
    addiu     $5, $2, -0x1;
  L00106D70:
    lw         $2, 0x58($29);
    andi       $3, $2, 0x1;
    bnel       $3, $0, L00106D94;
    lw        $4, 0x60($29);
    lbu        $2, 0x58($29);
    addiu      $4, $29, 0x59;
    dsll32     $2, $2, 24;
    b          L00106D98;
    dsrl32    $2, $2, 25;
  L00106D94:
    lw         $2, 0x5C($29);
  L00106D98:
    beqz       $3, L00106DA8;
    addu      $2, $4, $2;
    b          L00106DAC;
    lw        $6, 0x60($29);
  L00106DA8:
    addiu      $6, $29, 0x59;
  L00106DAC:
    dsll32     $5, $2, 0;
    dsra32     $5, $5, 0;
    sltu       $1, $6, $5;
    beqz       $1, L00106DE0;
    nop;
  L00106DC0:
    dsll32     $4, $6, 0;
    dsra32     $4, $4, 0;
    lb         $3, 0x0($4);
    addiu      $6, $4, 0x1;
    sltu       $2, $6, $5;
    addiu      $3, $3, 0x30;
    bnez       $2, L00106DC0;
    sb        $3, 0x0($4);
  L00106DE0:
    daddu      $4, $19, $0;
    jal        StringCopyCtor_107c30;
    addiu     $5, $29, 0x58;
    addiu      $4, $29, 0x58;
    jal        StringDtor_107b00;
    addiu     $5, $0, -0x1;
    daddu      $2, $0, $0;
  L00106DFC:
    ld         $31, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

