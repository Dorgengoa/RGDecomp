#include "types.h"

extern void StdioSinit_12f8b8(void);
extern void Fflush_12f590(void);
extern void Submore_136400(void);

asm void Ungetc_1364e8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $3, $0, -0x1;
    sd         $17, 0x8($29);
    daddu      $17, $4, $0;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sd         $31, 0x10($29);
    beq        $17, $3, L0013665C;
    addiu     $2, $0, -0x1;
    lw         $3, 0x54($16);
    bnel       $3, $0, L00136528;
    lw        $2, 0x38($3);
    lui        $2, 0x45;
    lw         $3, -0x67A8($2);
    sw         $3, 0x54($16);
    lw         $2, 0x38($3);
  L00136528:
    bnel       $2, $0, L0013653C;
    lhu       $2, 0xC($16);
    jal        StdioSinit_12f8b8;
    daddu     $4, $3, $0;
    lhu        $2, 0xC($16);
  L0013653C:
    andi       $4, $2, 0xFFDF;
    andi       $3, $4, 0x4;
    bnez       $3, L00136594;
    sh        $4, 0xC($16);
    andi       $3, $4, 0x10;
    beqz       $3, L0013665C;
    addiu     $2, $0, -0x1;
    andi       $2, $4, 0x8;
    beql       $2, $0, L0013658C;
    lhu       $2, 0xC($16);
    jal        Fflush_12f590;
    daddu     $4, $16, $0;
    bnez       $2, L0013665C;
    addiu     $2, $0, -0x1;
    lhu        $2, 0xC($16);
    sw         $0, 0x8($16);
    andi       $2, $2, 0xFFF7;
    sw         $0, 0x18($16);
    sh         $2, 0xC($16);
    lhu        $2, 0xC($16);
  L0013658C:
    ori        $2, $2, 0x4;
    sh         $2, 0xC($16);
  L00136594:
    lw         $2, 0x30($16);
    beqz       $2, L001365E8;
    andi      $17, $17, 0xFF;
    lw         $2, 0x4($16);
    lw         $3, 0x34($16);
    slt        $2, $2, $3;
    bnel       $2, $0, L001365D0;
    lw        $4, 0x0($16);
    jal        Submore_136400;
    daddu     $4, $16, $0;
    beql       $2, $0, L001365D0;
    lw        $4, 0x0($16);
    b          L0013665C;
    addiu     $2, $0, -0x1;
    nop;
  L001365D0:
    daddu      $2, $17, $0;
    addiu      $4, $4, -0x1;
    sw         $4, 0x0($16);
    sb         $17, 0x0($4);
    b          L00136618;
    lw        $3, 0x4($16);
  L001365E8:
    lw         $2, 0x10($16);
    beqz       $2, L00136628;
    lw        $7, 0x0($16);
    sltu       $2, $2, $7;
    beqz       $2, L0013662C;
    lw        $3, 0x4($16);
    lbu        $2, -0x1($7);
    bne        $2, $17, L0013662C;
    nop;
    addiu      $2, $7, -0x1;
    sw         $2, 0x0($16);
    daddu      $2, $17, $0;
  L00136618:
    addiu      $3, $3, 0x1;
    b          L0013665C;
    sw        $3, 0x4($16);
    nop;
  L00136628:
    lw         $3, 0x4($16);
  L0013662C:
    addiu      $4, $16, 0x40;
    addiu      $5, $0, 0x3;
    addiu      $6, $16, 0x42;
    addiu      $2, $0, 0x1;
    sw         $3, 0x3C($16);
    sw         $7, 0x38($16);
    sw         $4, 0x30($16);
    sw         $5, 0x34($16);
    sw         $6, 0x0($16);
    sb         $17, 0x42($16);
    sw         $2, 0x4($16);
    daddu      $2, $17, $0;
  L0013665C:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

