#include "types.h"

extern void EhFindExceptionTableMaybe_102690(void);
extern void EhSkipHeaderVarUInts_102640(void);
extern void DecodeVarUInt_100ed0(void);

asm void EhFindCallSite_102380(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $31, 0x30($29);
    sq         $18, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $5, $0;
    sw         $0, 0x4($5);
    daddu      $16, $4, $0;
    sw         $0, 0x8($5);
    daddu      $4, $17, $0;
    jal        EhFindExceptionTableMaybe_102690;
    daddu     $5, $16, $0;
    beql       $2, $0, L00102520;
    ld        $31, 0x30($29);
    lw         $7, 0xC($17);
    lui        $4, (0x2AAAAAAB >> 16);
    lw         $5, 0x10($17);
    dsll32     $3, $16, 0;
    ori        $4, $4, (0x2AAAAAAB & 0xFFFF);
    dsra32     $3, $3, 0;
    addiu      $8, $0, -0x2;
    daddu      $10, $0, $0;
    subu       $5, $5, $7;
    and        $3, $3, $8;
    mult       $0, $4, $5;
    dsll32     $3, $3, 0;
    nop;
    mfhi       $4;
    srl        $5, $5, 31;
    sra        $4, $4, 1;
    addu       $4, $4, $5;
    addiu      $9, $4, -0x1;
    bltz       $9, L00102470;
    dsra32    $3, $3, 0;
    addu       $4, $10, $9;
  L0010240C:
    sra        $6, $4, 1;
    sll        $4, $6, 1;
    addu       $4, $4, $6;
    sll        $4, $4, 2;
    addu       $11, $7, $4;
    lw         $5, 0x0($11);
    sltu       $1, $3, $5;
    beqz       $1, L00102438;
    nop;
    b          L00102460;
    addiu     $9, $6, -0x1;
  L00102438:
    lw         $4, 0x4($11);
    and        $4, $4, $8;
    addu       $4, $5, $4;
    sltu       $1, $4, $3;
    beqz       $1, L00102458;
    nop;
    b          L00102460;
    addiu     $10, $6, 0x1;
  L00102458:
    b          L00102474;
    nop;
  L00102460:
    slt        $1, $9, $10;
    beql       $1, $0, L0010240C;
    addu      $4, $10, $9;
    nop;
  L00102470:
    daddu      $11, $0, $0;
  L00102474:
    beqz       $11, L0010251C;
    nop;
    lw         $2, 0x4($11);
    andi       $2, $2, 0x1;
    beql       $2, $0, L00102498;
    lw        $2, 0x8($11);
    addiu      $2, $11, 0x8;
    b          L0010249C;
    sw        $2, 0x4($17);
  L00102498:
    sw         $2, 0x4($17);
  L0010249C:
    lw         $2, 0x0($11);
    sw         $2, 0x0($17);
    lw         $2, 0x0($11);
    lw         $4, 0x4($17);
    jal        EhSkipHeaderVarUInts_102640;
    subu      $16, $3, $2;
    daddu      $4, $2, $0;
    daddu      $18, $0, $0;
  L001024BC:
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $29, 0x4C;
    lw         $3, 0x4C($29);
    beqz       $3, L0010251C;
    daddu     $4, $2, $0;
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $29, 0x48;
    daddu      $4, $2, $0;
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $29, 0x44;
    lw         $3, 0x4C($29);
    addu       $5, $18, $3;
    sltu       $3, $16, $5;
    bnez       $3, L0010251C;
    daddu     $4, $2, $0;
    lw         $3, 0x48($29);
    addu       $18, $5, $3;
    sltu       $1, $18, $16;
    bnez       $1, L001024BC;
    nop;
    lw         $4, 0x4($17);
    lw         $3, 0x44($29);
    addu       $3, $4, $3;
    sw         $3, 0x8($17);
  L0010251C:
    ld         $31, 0x30($29);
  L00102520:
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

