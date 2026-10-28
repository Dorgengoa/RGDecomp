#include "types.h"

extern void StdioSinit_12f8b8(void);
extern void Fflush_12f590(void);
extern void Smakebuf_130a50(void);
extern void FstatR_130310(void);
extern void FreeR_12f9f8(void);
extern void Srefill_133db0(void);

asm void Fseek_12fe60(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $16, 0x70($29);
    daddu      $16, $4, $0;
    sd         $20, 0x90($29);
    daddu      $20, $6, $0;
    sd         $22, 0xA0($29);
    sd         $17, 0x78($29);
    sd         $18, 0x80($29);
    sd         $19, 0x88($29);
    sd         $21, 0x98($29);
    sd         $23, 0xA8($29);
    sd         $31, 0xB0($29);
    lw         $17, 0x54($16);
    bnez       $17, L0012FEB0;
    daddu     $22, $5, $0;
    lui        $2, 0x45;
    lw         $3, -0x67A8($2);
    sw         $3, 0x54($16);
    daddu      $17, $3, $0;
    nop;
  L0012FEB0:
    lw         $2, 0x38($17);
    bnel       $2, $0, L0012FECC;
    lw        $2, 0xC($16);
    jal        StdioSinit_12f8b8;
    daddu     $4, $17, $0;
    lw         $17, 0x54($16);
    lw         $2, 0xC($16);
  L0012FECC:
    addiu      $3, $0, 0x108;
    andi       $2, $2, 0x108;
    bnel       $2, $3, L0012FEE8;
    lw        $21, 0x28($16);
    jal        Fflush_12f590;
    daddu     $4, $16, $0;
    lw         $21, 0x28($16);
  L0012FEE8:
    bnel       $21, $0, L0012FEF8;
    addiu     $2, $0, 0x1;
    b          L0012FFE0;
    addiu     $3, $0, 0x1D;
  L0012FEF8:
    beq        $20, $2, L0012FF28;
    slti      $2, $20, 0x2;
    beqz       $2, L0012FF18;
    addiu     $2, $0, 0x2;
    beqz       $20, L0012FFD0;
    addiu     $3, $0, 0x16;
    b          L0012FFE4;
    addiu     $2, $0, -0x1;
  L0012FF18:
    beq        $20, $2, L0012FFD0;
    addiu     $3, $0, 0x16;
    b          L0012FFE4;
    addiu     $2, $0, -0x1;
  L0012FF28:
    jal        Fflush_12f590;
    daddu     $4, $16, $0;
    lhu        $6, 0xC($16);
    andi       $2, $6, 0x1000;
    beql       $2, $0, L0012FF48;
    lw        $4, 0x1C($16);
    b          L0012FF68;
    lw        $18, 0x50($16);
  L0012FF48:
    daddu      $5, $0, $0;
    jalr $31, $21;
    addiu     $6, $0, 0x1;
    addiu      $3, $0, -0x1;
    daddu      $18, $2, $0;
    beq        $18, $3, L001302E0;
    addiu     $2, $0, -0x1;
    lhu        $6, 0xC($16);
  L0012FF68:
    andi       $2, $6, 0x4;
    beqz       $2, L0012FF98;
    andi      $2, $6, 0x8;
    lw         $2, 0x4($16);
    lw         $5, 0x30($16);
    beqz       $5, L0012FFB8;
    dsubu     $18, $18, $2;
    lw         $2, 0x3C($16);
    lw         $7, 0x10($16);
    b          L0012FFBC;
    dsubu     $18, $18, $2;
    nop;
  L0012FF98:
    beqz       $2, L0012FFBC;
    lw        $7, 0x10($16);
    lw         $2, 0x0($16);
    beqz       $2, L0012FFBC;
    nop;
    subu       $2, $2, $7;
    b          L0012FFBC;
    daddu     $18, $18, $2;
  L0012FFB8:
    lw         $7, 0x10($16);
  L0012FFBC:
    daddu      $22, $22, $18;
    daddu      $20, $0, $0;
    b          L0012FFF0;
    addiu     $23, $0, 0x1;
    nop;
  L0012FFD0:
    daddu      $23, $0, $0;
    b          L0012FFF0;
    lw        $7, 0x10($16);
    nop;
  L0012FFE0:
    addiu      $2, $0, -0x1;
  L0012FFE4:
    b          L001302E0;
    sw        $3, 0x0($17);
    nop;
  L0012FFF0:
    bnel       $7, $0, L00130004;
    lhu       $6, 0xC($16);
    jal        Smakebuf_130a50;
    daddu     $4, $16, $0;
    lhu        $6, 0xC($16);
  L00130004:
    andi       $2, $6, 0x81A;
    bnez       $2, L00130270;
    andi      $2, $6, 0x400;
    bnez       $2, L00130078;
    lui       $2, 0x13;
    addiu      $2, $2, 0x4530;
    bnel       $21, $2, L00130060;
    ori       $2, $6, 0x800;
    lh         $5, 0xE($16);
    bltzl      $5, L00130060;
    ori       $2, $6, 0x800;
    daddu      $4, $17, $0;
    jal        FstatR_130310;
    daddu     $6, $29, $0;
    bnel       $2, $0, L0013005C;
    lhu       $6, 0xC($16);
    lw         $2, 0x4($29);
    ori        $3, $0, 0x8000;
    andi       $2, $2, 0xF000;
    beql       $2, $3, L00130068;
    lhu       $2, 0xC($16);
    lhu        $6, 0xC($16);
  L0013005C:
    ori        $2, $6, 0x800;
  L00130060:
    b          L00130270;
    sh        $2, 0xC($16);
  L00130068:
    addiu      $3, $0, 0x400;
    sw         $3, 0x4C($16);
    ori        $2, $2, 0x400;
    sh         $2, 0xC($16);
  L00130078:
    beqz       $20, L0013009C;
    daddu     $19, $22, $0;
    lh         $5, 0xE($16);
    daddu      $4, $17, $0;
    jal        FstatR_130310;
    daddu     $6, $29, $0;
    bnez       $2, L00130270;
    ld        $2, 0x10($29);
    daddu      $19, $2, $22;
  L0013009C:
    bnez       $23, L001300F8;
    lhu       $6, 0xC($16);
    andi       $2, $6, 0x1000;
    beql       $2, $0, L001300B8;
    lw        $4, 0x1C($16);
    b          L001300D8;
    lw        $18, 0x50($16);
  L001300B8:
    daddu      $5, $0, $0;
    jalr $31, $21;
    addiu     $6, $0, 0x1;
    daddu      $18, $2, $0;
    addiu      $2, $0, -0x1;
    beq        $18, $2, L00130270;
    nop;
    lhu        $6, 0xC($16);
  L001300D8:
    lw         $2, 0x4($16);
    lw         $5, 0x30($16);
    beqz       $5, L00130130;
    dsubu     $18, $18, $2;
    lw         $2, 0x3C($16);
    b          L001300FC;
    dsubu     $18, $18, $2;
    nop;
  L001300F8:
    lw         $5, 0x30($16);
  L001300FC:
    beql       $5, $0, L00130134;
    lw        $2, 0x0($16);
    lw         $2, 0x38($16);
    lw         $7, 0x10($16);
    lw         $3, 0x4($16);
    subu       $17, $2, $7;
    lw         $4, 0x3C($16);
    dsll32     $2, $17, 0;
    daddu      $18, $18, $3;
    dsrl32     $2, $2, 0;
    addu       $17, $17, $4;
    b          L00130150;
    dsubu     $18, $18, $2;
  L00130130:
    lw         $2, 0x0($16);
  L00130134:
    lw         $7, 0x10($16);
    lw         $4, 0x4($16);
    subu       $17, $2, $7;
    dsll32     $3, $17, 0;
    addu       $17, $17, $4;
    dsrl32     $3, $3, 0;
    dsubu      $18, $18, $3;
  L00130150:
    andi       $2, $6, 0x2000;
    bnel       $2, $0, L001301D0;
    lw        $2, 0x4C($16);
    slt        $2, $19, $18;
    bnel       $2, $0, L001301D0;
    lw        $2, 0x4C($16);
    dsll32     $2, $17, 0;
    dsrl32     $2, $2, 0;
    daddu      $2, $18, $2;
    slt        $2, $19, $2;
    beql       $2, $0, L001301D0;
    lw        $2, 0x4C($16);
    dsubu      $2, $19, $18;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    subu       $3, $17, $2;
    addu       $2, $7, $2;
    sw         $2, 0x0($16);
    beqz       $5, L001301BC;
    sw        $3, 0x4($16);
    addiu      $2, $16, 0x40;
    beql       $5, $2, L001301BC;
    sw        $0, 0x30($16);
    jal        FreeR_12f9f8;
    lw        $4, 0x54($16);
    lhu        $6, 0xC($16);
    sw         $0, 0x30($16);
  L001301BC:
    andi       $3, $6, 0xFFDF;
    daddu      $2, $0, $0;
    b          L001302E0;
    sh        $3, 0xC($16);
    nop;
  L001301D0:
    daddu      $6, $0, $0;
    lw         $4, 0x1C($16);
    negu       $2, $2;
    and        $18, $2, $19;
    jalr $31, $21;
    daddu     $5, $18, $0;
    addiu      $3, $0, -0x1;
    beq        $2, $3, L00130270;
    nop;
    lw         $5, 0x30($16);
    beqz       $5, L00130218;
    sw        $0, 0x4($16);
    addiu      $2, $16, 0x40;
    beql       $5, $2, L00130218;
    sw        $0, 0x30($16);
    jal        FreeR_12f9f8;
    lw        $4, 0x54($16);
    sw         $0, 0x30($16);
  L00130218:
    lhu        $2, 0xC($16);
    dsubu      $3, $19, $18;
    dsll32     $17, $3, 0;
    dsra32     $17, $17, 0;
    andi       $2, $2, 0xFFDF;
    beqz       $17, L00130264;
    sh        $2, 0xC($16);
    jal        Srefill_133db0;
    daddu     $4, $16, $0;
    bnez       $2, L00130270;
    nop;
    lw         $3, 0x4($16);
    sltu       $2, $3, $17;
    bnez       $2, L00130270;
    subu      $3, $3, $17;
    lw         $2, 0x0($16);
    sw         $3, 0x4($16);
    addu       $2, $2, $17;
    sw         $2, 0x0($16);
  L00130264:
    b          L001302E0;
    daddu     $2, $0, $0;
    nop;
  L00130270:
    jal        Fflush_12f590;
    daddu     $4, $16, $0;
    bnel       $2, $0, L001302E0;
    addiu     $2, $0, -0x1;
    lw         $4, 0x1C($16);
    daddu      $5, $22, $0;
    jalr $31, $21;
    daddu     $6, $20, $0;
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L001302A8;
    lw        $5, 0x30($16);
    b          L001302E0;
    addiu     $2, $0, -0x1;
    nop;
  L001302A8:
    beqz       $5, L001302C4;
    addiu     $2, $16, 0x40;
    beql       $5, $2, L001302C4;
    sw        $0, 0x30($16);
    jal        FreeR_12f9f8;
    lw        $4, 0x54($16);
    sw         $0, 0x30($16);
  L001302C4:
    lhu        $3, 0xC($16);
    daddu      $2, $0, $0;
    lw         $4, 0x10($16);
    andi       $3, $3, 0xFFDF;
    sw         $0, 0x4($16);
    sh         $3, 0xC($16);
    sw         $4, 0x0($16);
  L001302E0:
    ld         $16, 0x70($29);
    ld         $17, 0x78($29);
    ld         $18, 0x80($29);
    ld         $19, 0x88($29);
    ld         $20, 0x90($29);
    ld         $21, 0x98($29);
    ld         $22, 0xA0($29);
    ld         $23, 0xA8($29);
    ld         $31, 0xB0($29);
    jr         $31;
    addiu     $29, $29, 0xC0;
}

