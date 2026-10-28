#include "types.h"

extern void MallocR_1310d0(void);
extern void memset(void);

asm void SfMoreGlue_12f708(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $18, 0x10($29);
    daddu      $18, $5, $0;
    sd         $16, 0x0($29);
    sll        $16, $18, 1;
    addu       $16, $16, $18;
    sd         $17, 0x8($29);
    sll        $16, $16, 2;
    sd         $31, 0x18($29);
    subu       $16, $16, $18;
    sll        $16, $16, 3;
    jal        MallocR_1310d0;
    addiu     $5, $16, 0xC;
    daddu      $5, $0, $0;
    daddu      $17, $2, $0;
    daddu      $6, $16, $0;
    addiu      $3, $17, 0xC;
    beqz       $17, L0012F768;
    daddu     $4, $3, $0;
    sw         $18, 0x4($17);
    sw         $0, 0x0($17);
    jal        memset;
    sw        $3, 0x8($17);
    daddu      $2, $17, $0;
  L0012F768:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
