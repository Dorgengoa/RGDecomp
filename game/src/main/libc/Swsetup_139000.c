#include "types.h"

extern void StdioSinit_12f8b8(void);
extern void FreeR_12f9f8(void);
extern void Smakebuf_130a50(void);

asm void Swsetup_139000(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x8($29);
    lw         $3, 0x54($16);
    bnel       $3, $0, L00139030;
    lw        $2, 0x38($3);
    lui        $2, 0x45;
    lw         $3, -0x67A8($2);
    sw         $3, 0x54($16);
    lw         $2, 0x38($3);
    nop;
  L00139030:
    bnel       $2, $0, L00139044;
    lhu       $4, 0xC($16);
    jal        StdioSinit_12f8b8;
    daddu     $4, $3, $0;
    lhu        $4, 0xC($16);
  L00139044:
    andi       $2, $4, 0x8;
    bnel       $2, $0, L001390B0;
    lw        $5, 0x10($16);
    andi       $3, $4, 0x10;
    beqz       $3, L001390FC;
    addiu     $2, $0, -0x1;
    andi       $2, $4, 0x4;
    beql       $2, $0, L001390A8;
    lw        $5, 0x10($16);
    lw         $5, 0x30($16);
    beqz       $5, L0013908C;
    addiu     $2, $16, 0x40;
    beql       $5, $2, L0013908C;
    sw        $0, 0x30($16);
    jal        FreeR_12f9f8;
    lw        $4, 0x54($16);
    lhu        $4, 0xC($16);
    sw         $0, 0x30($16);
  L0013908C:
    addiu      $2, $0, -0x25;
    lw         $5, 0x10($16);
    and        $2, $4, $2;
    sw         $0, 0x4($16);
    sh         $2, 0xC($16);
    daddu      $4, $2, $0;
    sw         $5, 0x0($16);
  L001390A8:
    ori        $2, $4, 0x8;
    sh         $2, 0xC($16);
  L001390B0:
    bnel       $5, $0, L001390C4;
    lhu       $3, 0xC($16);
    jal        Smakebuf_130a50;
    daddu     $4, $16, $0;
    lhu        $3, 0xC($16);
  L001390C4:
    andi       $2, $3, 0x1;
    beqz       $2, L001390E8;
    andi      $2, $3, 0x2;
    lw         $2, 0x14($16);
    sw         $0, 0x8($16);
    negu       $2, $2;
    b          L001390F8;
    sw        $2, 0x18($16);
    nop;
  L001390E8:
    bnez       $2, L001390F4;
    daddu     $3, $0, $0;
    lw         $3, 0x14($16);
  L001390F4:
    sw         $3, 0x8($16);
  L001390F8:
    daddu      $2, $0, $0;
  L001390FC:
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

