#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void MpegCopyMbViaSprMaybe_1117a8(void)
{
    .set noreorder;
    addiu      $29, $29, -0xB0;
    lui        $2, (0xFFFFFFF >> 16);
    sd         $22, 0x70($29);
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    sd         $18, 0x30($29);
    daddu      $22, $5, $0;
    sw         $4, 0x0($29);
    sd         $31, 0xA0($29);
    sd         $30, 0x90($29);
    sd         $23, 0x80($29);
    sd         $21, 0x60($29);
    sd         $20, 0x50($29);
    sd         $19, 0x40($29);
    sd         $17, 0x20($29);
    sd         $16, 0x10($29);
    lw         $6, 0x0($29);
    lw         $3, 0x0($22);
    lw         $4, 0xEC($4);
    lw         $5, 0x184($6);
    and        $18, $3, $2;
    and        $4, $4, $2;
    addiu      $3, $0, 0x3;
    beq        $5, $3, L0011181C;
    sw        $4, 0x8($29);
    lw         $4, 0xF4($6);
    bnez       $4, L00111854;
    daddu     $3, $4, $0;
    b          L00111828;
    lw        $2, 0x10($22);
  L0011181C:
    lw         $7, 0x0($29);
    lw         $3, 0xF4($7);
    lw         $2, 0x10($22);
  L00111828:
    addiu      $4, $0, 0x180;
    mult       $21, $2, $4;
    beqz       $3, L00111844;
    sra       $20, $21, 4;
    sra        $2, $3, 4;
    b          L00111848;
    mult      $30, $2, $4;
  L00111844:
    daddu      $30, $21, $0;
  L00111848:
    addiu      $2, $0, 0x1;
    b          L0011187C;
    sw        $2, 0x4($29);
  L00111854:
    lw         $2, 0x10($22);
    addiu      $5, $0, 0x180;
    addiu      $3, $0, 0xC0;
    sra        $4, $4, 4;
    sra        $2, $2, 1;
    mult       $30, $4, $3;
    mult1      $21, $2, $5;
    addiu      $3, $0, 0x2;
    sw         $3, 0x4($29);
    sra        $20, $21, 4;
  L0011187C:
    lw         $6, 0x4($29);
    beqz       $6, L00111A08;
    daddu     $5, $0, $0;
    lw         $6, 0xC($22);
    nop;
  L00111890:
    lw         $17, 0x8($29);
    blez       $6, L001119D4;
    daddu     $16, $0, $0;
    addiu      $23, $5, 0x1;
  L001118A0:
    jal        DisableIntr_120660;
    nop;
    lui        $3, (0x1000D480 >> 16);
    lui        $5, (0x1000D410 >> 16);
    ori        $3, $3, (0x1000D480 & 0xFFFF);
    ori        $5, $5, (0x1000D410 & 0xFFFF);
    sw         $0, 0x0($3);
    lui        $4, (0x1000D420 >> 16);
    sw         $18, 0x0($5);
    ori        $4, $4, (0x1000D420 & 0xFFFF);
    lui        $5, (0x1000D400 >> 16);
    sw         $20, 0x0($4);
    ori        $5, $5, (0x1000D400 & 0xFFFF);
    addiu      $3, $0, 0x101;
    sw         $3, 0x0($5);
    beqz       $2, L001118F0;
    lui       $3, (0x1000D400 >> 16);
    jal        EnableIntr_1206b0;
    nop;
    lui        $3, (0x1000D400 >> 16);
  L001118F0:
    addu       $19, $18, $21;
    addiu      $16, $16, 0x1;
    addu       $18, $17, $30;
    ori        $3, $3, (0x1000D400 & 0xFFFF);
  L00111900:
    lw         $2, 0x0($3);
    andi       $2, $2, 0x100;
    nop;
    nop;
    nop;
    bnez       $2, L00111900;
    nop;
    jal        DisableIntr_120660;
    nop;
    lui        $3, (0x1000D080 >> 16);
    lui        $5, (0x1000D010 >> 16);
    ori        $3, $3, (0x1000D080 & 0xFFFF);
    ori        $5, $5, (0x1000D010 & 0xFFFF);
    sw         $0, 0x0($3);
    lui        $4, (0x1000D020 >> 16);
    sw         $17, 0x0($5);
    ori        $4, $4, (0x1000D020 & 0xFFFF);
    lui        $5, (0x1000D000 >> 16);
    sw         $20, 0x0($4);
    ori        $5, $5, (0x1000D000 & 0xFFFF);
    addiu      $3, $0, 0x100;
    sw         $3, 0x0($5);
    beqz       $2, L0011196C;
    lui       $3, (0x1000D000 >> 16);
    jal        EnableIntr_1206b0;
    nop;
    lui        $3, (0x1000D000 >> 16);
  L0011196C:
    lw         $6, 0xC($22);
    ori        $3, $3, (0x1000D000 & 0xFFFF);
    nop;
  L00111978:
    lw         $2, 0x0($3);
    andi       $2, $2, 0x100;
    nop;
    nop;
    nop;
    bnez       $2, L00111978;
    nop;
    lui        $3, (0x1000D020 >> 16);
    ori        $3, $3, (0x1000D020 & 0xFFFF);
    nop;
  L001119A0:
    lw         $2, 0x0($3);
    nop;
    nop;
    nop;
    nop;
    bnez       $2, L001119A0;
    nop;
    daddu      $17, $18, $0;
    slt        $2, $16, $6;
    bnez       $2, L001118A0;
    daddu     $18, $19, $0;
    b          L001119DC;
    lw        $7, 0x0($29);
  L001119D4:
    addiu      $23, $5, 0x1;
    lw         $7, 0x0($29);
  L001119DC:
    daddu      $5, $23, $0;
    addiu      $3, $0, 0xC0;
    lw         $2, 0xF8($7);
    lw         $7, 0x4($29);
    slt        $4, $5, $7;
    lw         $7, 0x8($29);
    mtlo       $7;
    madd       $0, $2, $3;
    mflo       $7;
    bnez       $4, L00111890;
    sw        $7, 0x8($29);
  L00111A08:
    ld         $31, 0xA0($29);
    ld         $30, 0x90($29);
    ld         $23, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0xB0;
}
