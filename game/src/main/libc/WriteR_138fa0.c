#include "types.h"

extern void write(void);

asm void WriteR_138fa0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    lui        $2, 0x4F;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $17, 0x8($29);
    addiu      $17, $2, -0x6200;
    daddu      $4, $5, $0;
    daddu      $5, $6, $0;
    daddu      $6, $7, $0;
    sd         $31, 0x10($29);
    jal        write;
    sw        $0, 0x0($17);
    daddu      $3, $2, $0;
    addiu      $4, $0, -0x1;
    bne        $3, $4, L00138FEC;
    daddu     $2, $3, $0;
    lw         $3, 0x0($17);
    bnel       $3, $0, L00138FEC;
    sw        $3, 0x0($16);
  L00138FEC:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

