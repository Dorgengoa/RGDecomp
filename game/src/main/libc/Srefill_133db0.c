#include "types.h"

extern void StdioSinit_12f8b8(void);
extern void Fflush_12f590(void);
extern void FreeR_12f9f8(void);
extern void Smakebuf_130a50(void);
extern void Fwalk_130858(void);

asm void Srefill_133db0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x8($29);
    lw         $3, 0x54($16);
    bnel       $3, $0, L00133DE0;
    lw        $2, 0x38($3);
    lui        $2, 0x45;
    lw         $3, -0x67A8($2);
    sw         $3, 0x54($16);
    lw         $2, 0x38($3);
    nop;
  L00133DE0:
    bnel       $2, $0, L00133DF4;
    lhu       $4, 0xC($16);
    jal        StdioSinit_12f8b8;
    daddu     $4, $3, $0;
    lhu        $4, 0xC($16);
  L00133DF4:
    addiu      $2, $0, -0x1;
    andi       $3, $4, 0x20;
    bnez       $3, L00133F1C;
    sw        $0, 0x4($16);
    andi       $2, $4, 0x4;
    bnel       $2, $0, L00133E60;
    lw        $5, 0x30($16);
    andi       $3, $4, 0x10;
    beqz       $3, L00133F1C;
    addiu     $2, $0, -0x1;
    andi       $2, $4, 0x8;
    beql       $2, $0, L00133E54;
    ori       $2, $4, 0x4;
    jal        Fflush_12f590;
    daddu     $4, $16, $0;
    bnez       $2, L00133F1C;
    addiu     $2, $0, -0x1;
    lhu        $2, 0xC($16);
    sw         $0, 0x8($16);
    andi       $2, $2, 0xFFF7;
    sw         $0, 0x18($16);
    sh         $2, 0xC($16);
    daddu      $4, $2, $0;
    ori        $2, $4, 0x4;
  L00133E54:
    b          L00133E98;
    sh        $2, 0xC($16);
    nop;
  L00133E60:
    beqz       $5, L00133E98;
    addiu     $2, $16, 0x40;
    beql       $5, $2, L00133E7C;
    lw        $2, 0x3C($16);
    jal        FreeR_12f9f8;
    lw        $4, 0x54($16);
    lw         $2, 0x3C($16);
  L00133E7C:
    sw         $0, 0x30($16);
    beqz       $2, L00133E98;
    sw        $2, 0x4($16);
    lw         $3, 0x38($16);
    daddu      $2, $0, $0;
    b          L00133F1C;
    sw        $3, 0x0($16);
  L00133E98:
    lw         $2, 0x10($16);
    bnel       $2, $0, L00133EB0;
    lhu       $2, 0xC($16);
    jal        Smakebuf_130a50;
    daddu     $4, $16, $0;
    lhu        $2, 0xC($16);
  L00133EB0:
    andi       $2, $2, 0x3;
    beqz       $2, L00133EC8;
    lui       $5, 0x13;
    lw         $4, 0x54($16);
    jal        Fwalk_130858;
    addiu     $5, $5, 0x3D78;
  L00133EC8:
    lw         $5, 0x10($16);
    lw         $4, 0x1C($16);
    lw         $2, 0x20($16);
    sw         $5, 0x0($16);
    jalr $31, $2;
    lw        $6, 0x14($16);
    lhu        $3, 0xC($16);
    daddu      $4, $2, $0;
    daddu      $2, $0, $0;
    andi       $3, $3, 0xDFFF;
    sw         $4, 0x4($16);
    bgtz       $4, L00133F1C;
    sh        $3, 0xC($16);
    bnel       $4, $0, L00133F10;
    ori       $2, $3, 0x40;
    b          L00133F14;
    ori       $2, $3, 0x20;
    nop;
  L00133F10:
    sw         $0, 0x4($16);
  L00133F14:
    sh         $2, 0xC($16);
    addiu      $2, $0, -0x1;
  L00133F1C:
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

