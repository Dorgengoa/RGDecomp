#include "types.h"

extern void StdioSinit_12f8b8(void);
extern void Swsetup_139000(void);
extern void Fflush_12f590(void);

asm void Swbuf_138e90(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    daddu      $16, $5, $0;
    sd         $17, 0x8($29);
    sd         $31, 0x10($29);
    lw         $3, 0x54($16);
    bnez       $3, L00138EC0;
    daddu     $17, $4, $0;
    lui        $2, 0x45;
    lw         $3, -0x67A8($2);
    sw         $3, 0x54($16);
    nop;
  L00138EC0:
    lw         $2, 0x38($3);
    bnel       $2, $0, L00138ED8;
    lhu       $2, 0xC($16);
    jal        StdioSinit_12f8b8;
    daddu     $4, $3, $0;
    lhu        $2, 0xC($16);
  L00138ED8:
    lw         $3, 0x18($16);
    andi       $2, $2, 0x8;
    beqz       $2, L00138EF4;
    sw        $3, 0x8($16);
    lw         $3, 0x10($16);
    bnel       $3, $0, L00138F0C;
    lw        $5, 0x0($16);
  L00138EF4:
    jal        Swsetup_139000;
    daddu     $4, $16, $0;
    bnez       $2, L00138F8C;
    addiu     $2, $0, -0x1;
    lw         $3, 0x10($16);
    lw         $5, 0x0($16);
  L00138F0C:
    lw         $2, 0x14($16);
    subu       $4, $5, $3;
    slt        $2, $4, $2;
    bnez       $2, L00138F38;
    andi      $17, $17, 0xFF;
    jal        Fflush_12f590;
    daddu     $4, $16, $0;
    bnez       $2, L00138F8C;
    addiu     $2, $0, -0x1;
    lw         $5, 0x0($16);
    daddu      $4, $0, $0;
  L00138F38:
    lw         $2, 0x8($16);
    addiu      $3, $5, 0x1;
    addiu      $4, $4, 0x1;
    addiu      $2, $2, -0x1;
    sw         $2, 0x8($16);
    sb         $17, 0x0($5);
    sw         $3, 0x0($16);
    lw         $2, 0x14($16);
    beq        $4, $2, L00138F78;
    nop;
    lhu        $2, 0xC($16);
    andi       $2, $2, 0x1;
    beqz       $2, L00138F88;
    addiu     $2, $0, 0xA;
    bne        $17, $2, L00138F8C;
    daddu     $2, $17, $0;
  L00138F78:
    jal        Fflush_12f590;
    daddu     $4, $16, $0;
    bnez       $2, L00138F8C;
    addiu     $2, $0, -0x1;
  L00138F88:
    daddu      $2, $17, $0;
  L00138F8C:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

