#include "types.h"

extern void scePadGetDmaStr(void);
extern void PadSifDmaSendMaybe_12b298(void);

asm void scePadSetActDirect(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $18, 0xA0($29);
    sd         $17, 0x90($29);
    daddu      $18, $5, $0;
    sd         $16, 0x80($29);
    daddu      $17, $4, $0;
    daddu      $16, $6, $0;
    sd         $31, 0xB0($29);
    jal        scePadGetDmaStr;
    daddu     $6, $29, $0;
    lbu        $3, 0x72($29);
    addiu      $2, $0, 0x1;
    bne        $3, $2, L0012BF40;
    daddu     $2, $0, $0;
    addiu      $3, $0, 0x1C;
    addiu      $4, $0, 0x70;
    mult       $3, $18, $3;
    mult1      $4, $17, $4;
    lui        $2, 0x49;
    daddu      $5, $0, $0;
    addiu      $2, $2, -0x12B0;
    addu       $3, $3, $4;
    addu       $2, $2, $3;
    lw         $6, 0x4($2);
    addiu      $7, $6, 0xC;
    nop;
  L0012BEF8:
    addu       $2, $16, $5;
    addu       $4, $7, $5;
    lbu        $3, 0x0($2);
    addiu      $5, $5, 0x1;
    slti       $2, $5, 0x6;
    sb         $3, 0x0($4);
    bnez       $2, L0012BEF8;
    nop;
    addiu      $16, $0, 0x1;
    addiu      $2, $0, 0x6;
    sw         $16, 0x4($6);
    daddu      $4, $17, $0;
    sw         $2, 0x8($6);
    jal        PadSifDmaSendMaybe_12b298;
    daddu     $5, $18, $0;
    xori       $2, $2, 0x1;
    movn       $16, $0, $2;
    daddu      $2, $16, $0;
  L0012BF40:
    ld         $31, 0xB0($29);
    ld         $18, 0xA0($29);
    ld         $17, 0x90($29);
    ld         $16, 0x80($29);
    jr         $31;
    addiu     $29, $29, 0xC0;
}
