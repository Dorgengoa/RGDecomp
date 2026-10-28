#include "types.h"

extern void strlen(void);
extern void memcpy(void);
extern void iSignalSema(void);

asm void mceStorePwd(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x10($29);
    sd         $31, 0x30($29);
    daddu      $17, $4, $0;
    sd         $18, 0x20($29);
    beqz       $17, L0012D564;
    sd        $16, 0x0($29);
    lui        $18, 0x49;
    lui        $2, (0x20000000 >> 16);
    addiu      $3, $18, -0xA40;
    or         $16, $3, $2;
    jal        strlen;
    daddu     $4, $16, $0;
    sltiu      $2, $2, 0x400;
    beql       $2, $0, L0012D544;
    addiu     $16, $0, 0x3FF;
    jal        strlen;
    daddu     $4, $16, $0;
    daddu      $16, $2, $0;
  L0012D544:
    addiu      $2, $18, -0xA40;
    lui        $5, (0x20000000 >> 16);
    or         $5, $2, $5;
    daddu      $4, $17, $0;
    jal        memcpy;
    daddu     $6, $16, $0;
    addu       $3, $17, $16;
    sb         $0, 0x0($3);
  L0012D564:
    lui        $2, 0x45;
    ld         $31, 0x30($29);
    lw         $4, -0x6AA0($2);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    j          iSignalSema;
    addiu     $29, $29, 0x40;
}
