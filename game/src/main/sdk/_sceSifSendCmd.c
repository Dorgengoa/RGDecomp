#include "types.h"

extern void sceSifWriteBackDCache(void);
extern void isceSifSetDma(void);
extern void sceSifSetDma(void);

asm void _sceSifSendCmd(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $17, 0x30($29);
    sd         $20, 0x60($29);
    daddu      $17, $7, $0;
    sd         $19, 0x50($29);
    daddu      $20, $4, $0;
    sd         $16, 0x20($29);
    addiu      $2, $17, -0x10;
    daddu      $19, $5, $0;
    sd         $31, 0x70($29);
    sd         $18, 0x40($29);
    daddu      $16, $6, $0;
    daddu      $4, $8, $0;
    sltiu      $2, $2, 0x61;
    bnez       $2, L001197F8;
    daddu     $5, $10, $0;
    b          L001198C4;
    daddu     $2, $0, $0;
  L001197F8:
    blez       $5, L00119840;
    daddu     $18, $0, $0;
    lbu        $2, 0x0($16);
    sll        $3, $5, 8;
    sw         $9, 0x4($16);
    addiu      $18, $0, 0x1;
    or         $2, $2, $3;
    sw         $4, 0x0($29);
    sw         $2, 0x0($16);
    andi       $3, $19, 0x4;
    sw         $9, 0x4($29);
    sw         $5, 0x8($29);
    beqz       $3, L0011984C;
    sw        $0, 0xC($29);
    jal        sceSifWriteBackDCache;
    nop;
    b          L00119850;
    sll       $5, $18, 4;
  L00119840:
    lbu        $2, 0x0($16);
    sw         $0, 0x4($16);
    sw         $2, 0x0($16);
  L0011984C:
    sll        $5, $18, 4;
  L00119850:
    lui        $2, 0x48;
    lw         $4, 0x6920($2);
    addu       $3, $29, $5;
    sw         $16, 0x0($3);
    addiu      $2, $29, 0x4;
    addu       $2, $2, $5;
    addiu      $3, $29, 0x8;
    sw         $4, 0x0($2);
    addu       $3, $3, $5;
    sw         $17, 0x0($3);
    addiu      $4, $29, 0xC;
    addu       $4, $4, $5;
    sw         $20, 0x8($16);
    sb         $17, 0x0($16);
    addiu      $2, $0, 0x44;
    sw         $2, 0x0($4);
    daddu      $5, $17, $0;
    daddu      $4, $16, $0;
    jal        sceSifWriteBackDCache;
    addiu     $18, $18, 0x1;
    andi       $2, $19, 0x1;
    beqz       $2, L001198BC;
    daddu     $5, $18, $0;
    jal        isceSifSetDma;
    daddu     $4, $29, $0;
    b          L001198C8;
    ld        $31, 0x70($29);
  L001198BC:
    jal        sceSifSetDma;
    daddu     $4, $29, $0;
  L001198C4:
    ld         $31, 0x70($29);
  L001198C8:
    ld         $20, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
