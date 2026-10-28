#include "types.h"

extern void Isinf_128610(void);
extern void Isnan_128658(void);
extern void Sprintf_1343b8(void);
extern void StringAssignCStr_106ee0(void);
extern void StringEraseRange_107960(void);
extern void StringEraseAt_1079e0(void);

asm void DecimalFromLongDoubleMaybe_106830(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $5, $0;
    sw         $0, 0x0($4);
    daddu      $16, $4, $0;
    sw         $0, 0x4($4);
    sw         $0, 0x8($4);
    sh         $0, 0xC($4);
    sh         $0, 0xE($4);
    jal        Isinf_128610;
    daddu     $4, $17, $0;
    beql       $2, $0, L0010687C;
    daddu     $4, $17, $0;
    addiu      $3, $0, 0x2;
    daddu      $2, $16, $0;
    b          L00106A94;
    sh        $3, 0xE($16);
  L0010687C:
    jal        Isnan_128658;
    nop;
    beqz       $2, L0010689C;
    nop;
    addiu      $3, $0, 0x1;
    daddu      $2, $16, $0;
    b          L00106A94;
    sh        $3, 0xE($16);
  L0010689C:
    lui        $5, 0x45;
    daddu      $7, $17, $0;
    addiu      $4, $29, 0x30;
    addiu      $5, $5, 0x5A90;
    jal        Sprintf_1343b8;
    addiu     $6, $0, 0x1F;
    daddu      $4, $16, $0;
    jal        StringAssignCStr_106ee0;
    addiu     $5, $29, 0x30;
    lw         $2, 0x0($16);
    andi       $2, $2, 0x1;
    beql       $2, $0, L001068D4;
    addiu     $2, $16, 0x1;
    lw         $2, 0x8($16);
  L001068D4:
    addiu      $6, $2, 0x23;
    b          L00106920;
    addiu     $4, $16, 0x1;
  L001068E0:
    dsll32     $3, $6, 0;
    dsra32     $3, $3, 0;
    addiu      $6, $3, 0x1;
    sll        $2, $5, 2;
    addu       $2, $2, $5;
    sll        $2, $2, 1;
    sh         $2, 0xC($16);
    lb         $3, 0x0($3);
    dsll32     $2, $2, 16;
    dsra32     $2, $2, 16;
    addiu      $3, $3, -0x30;
    dsll32     $3, $3, 16;
    dsra32     $3, $3, 16;
    addu       $2, $2, $3;
    sh         $2, 0xC($16);
    nop;
  L00106920:
    lw         $2, 0x0($16);
    andi       $5, $2, 0x1;
    bnez       $5, L00106948;
    nop;
    lbu        $2, 0x0($16);
    daddu      $3, $4, $0;
    dsll32     $2, $2, 24;
    b          L00106950;
    dsrl32    $2, $2, 25;
    nop;
  L00106948:
    lw         $3, 0x8($16);
    lw         $2, 0x4($16);
  L00106950:
    addu       $3, $3, $2;
    dsll32     $2, $6, 0;
    dsra32     $2, $2, 0;
    xor        $2, $2, $3;
    sltiu      $2, $2, 0x1;
    xori       $2, $2, 0x1;
    bnel       $2, $0, L001068E0;
    lh        $5, 0xC($16);
    beql       $5, $0, L0010697C;
    addiu     $2, $16, 0x1;
    lw         $2, 0x8($16);
  L0010697C:
    lb         $3, 0x22($2);
    addiu      $4, $2, 0x22;
    addiu      $2, $0, 0x2D;
    bnel       $3, $2, L001069A0;
    lw        $3, 0x0($16);
    lh         $2, 0xC($16);
    negu       $2, $2;
    sh         $2, 0xC($16);
    lw         $3, 0x0($16);
  L001069A0:
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
    andi       $3, $3, 0x1;
    bnez       $3, L001069C8;
    addiu     $2, $2, -0x1;
    lbu        $3, 0x0($16);
    addiu      $4, $16, 0x1;
    dsll32     $3, $3, 24;
    b          L001069D0;
    dsrl32    $3, $3, 25;
  L001069C8:
    lw         $4, 0x8($16);
    lw         $3, 0x4($16);
  L001069D0:
    addu       $7, $4, $3;
    dsll32     $6, $2, 0;
    dsra32     $6, $6, 0;
    addiu      $4, $29, 0x78;
    jal        StringEraseRange_107960;
    daddu     $5, $16, $0;
    lw         $2, 0x0($16);
    andi       $2, $2, 0x1;
    beql       $2, $0, L001069FC;
    addiu     $2, $16, 0x1;
    lw         $2, 0x8($16);
  L001069FC:
    addiu      $6, $2, 0x1;
    addiu      $4, $29, 0x70;
    jal        StringEraseAt_1079e0;
    daddu     $5, $16, $0;
    lw         $2, 0x0($16);
    andi       $2, $2, 0x1;
    beql       $2, $0, L00106A20;
    addiu     $5, $16, 0x1;
    lw         $5, 0x8($16);
  L00106A20:
    b          L00106A40;
    addiu     $4, $16, 0x1;
  L00106A28:
    dsra32     $3, $3, 0;
    lb         $2, 0x0($3);
    addiu      $5, $3, 0x1;
    addiu      $2, $2, -0x30;
    sb         $2, 0x0($3);
    nop;
  L00106A40:
    lw         $2, 0x0($16);
    andi       $2, $2, 0x1;
    bnez       $2, L00106A68;
    nop;
    lbu        $2, 0x0($16);
    daddu      $3, $4, $0;
    dsll32     $2, $2, 24;
    b          L00106A70;
    dsrl32    $2, $2, 25;
    nop;
  L00106A68:
    lw         $3, 0x8($16);
    lw         $2, 0x4($16);
  L00106A70:
    addu       $3, $3, $2;
    dsll32     $2, $5, 0;
    dsra32     $2, $2, 0;
    xor        $2, $2, $3;
    sltiu      $2, $2, 0x1;
    xori       $2, $2, 0x1;
    bnel       $2, $0, L00106A28;
    dsll32    $3, $5, 0;
    daddu      $2, $16, $0;
  L00106A94:
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

