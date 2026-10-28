#include "types.h"

extern void scePadGetDmaStr(void);
extern void memcpy(void);

asm void scePadRead(void)
{
    .set noreorder;
    daddu      $7, $4, $0;
    addiu      $3, $0, 0x70;
    addiu      $4, $0, 0x1C;
    mult1      $3, $7, $3;
    mult       $4, $5, $4;
    addiu      $29, $29, -0xA0;
    lui        $2, 0x49;
    sd         $16, 0x80($29);
    sd         $31, 0x90($29);
    addiu      $2, $2, -0x12B0;
    addu       $4, $4, $3;
    addu       $2, $2, $4;
    lw         $3, 0x10($2);
    bnez       $3, L0012B844;
    daddu     $16, $6, $0;
    b          L0012B864;
    daddu     $2, $0, $0;
  L0012B844:
    daddu      $4, $7, $0;
    jal        scePadGetDmaStr;
    daddu     $6, $29, $0;
    lw         $6, 0x60($29);
    daddu      $4, $16, $0;
    jal        memcpy;
    daddu     $5, $29, $0;
    lw         $2, 0x60($29);
  L0012B864:
    ld         $31, 0x90($29);
    ld         $16, 0x80($29);
    jr         $31;
    addiu     $29, $29, 0xA0;
}
