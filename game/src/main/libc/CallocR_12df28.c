#include "types.h"

extern void MallocR_1310d0(void);
extern void memset(void);

asm void CallocR_12df28(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    sd         $31, 0x8($29);
    jal        MallocR_1310d0;
    mult      $5, $5, $6;
    daddu      $16, $2, $0;
    beqz       $16, L0012DFCC;
    addiu     $3, $0, -0x4;
    lw         $2, -0x4($16);
    and        $2, $2, $3;
    addiu      $7, $2, -0x4;
    daddu      $5, $0, $0;
    sltiu      $2, $7, 0x25;
    daddu      $6, $7, $0;
    daddu      $4, $16, $0;
    beqz       $2, L0012DFC0;
    sltiu     $8, $7, 0x14;
    bnez       $8, L0012DFA8;
    daddu     $3, $16, $0;
    sltiu      $2, $7, 0x1C;
    sw         $0, 0x0($16);
    sw         $0, 0x4($16);
    bnez       $2, L0012DFA8;
    addiu     $3, $16, 0x8;
    sltiu      $2, $7, 0x24;
    sw         $0, 0x0($3);
    addiu      $3, $16, 0x10;
    bnez       $2, L0012DFA8;
    sw        $0, 0xC($16);
    sw         $0, 0x0($3);
    addiu      $3, $16, 0x18;
    sw         $0, 0x14($16);
  L0012DFA8:
    sw         $0, 0x0($3);
    addiu      $3, $3, 0x4;
    sw         $0, 0x4($3);
    b          L0012DFC8;
    sw        $0, 0x0($3);
    nop;
  L0012DFC0:
    jal        memset;
    nop;
  L0012DFC8:
    daddu      $2, $16, $0;
  L0012DFCC:
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
