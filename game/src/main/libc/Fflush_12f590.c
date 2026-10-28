#include "types.h"

extern void Fwalk_130858(void);
extern void StdioSinit_12f8b8(void);

asm void Fflush_12f590(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $17, 0x8($29);
    daddu      $17, $4, $0;
    sd         $16, 0x0($29);
    sd         $18, 0x10($29);
    bnez       $17, L0012F5D8;
    sd        $31, 0x18($29);
    lui        $2, 0x45;
    lui        $5, 0x13;
    lw         $4, -0x67A8($2);
    addiu      $5, $5, -0xA70;
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    j          Fwalk_130858;
    addiu     $29, $29, 0x20;
    nop;
  L0012F5D8:
    lw         $3, 0x54($17);
    bnel       $3, $0, L0012F5F8;
    lw        $2, 0x38($3);
    lui        $2, 0x45;
    lw         $3, -0x67A8($2);
    sw         $3, 0x54($17);
    lw         $2, 0x38($3);
    nop;
  L0012F5F8:
    bnel       $2, $0, L0012F60C;
    lh        $3, 0xC($17);
    jal        StdioSinit_12f8b8;
    daddu     $4, $3, $0;
    lh         $3, 0xC($17);
  L0012F60C:
    andi       $2, $3, 0x8;
    beqz       $2, L0012F68C;
    daddu     $2, $0, $0;
    lw         $18, 0x10($17);
    beqz       $18, L0012F68C;
    daddu     $4, $0, $0;
    lw         $2, 0x0($17);
    andi       $3, $3, 0x3;
    sw         $18, 0x0($17);
    bnez       $3, L0012F658;
    subu      $16, $2, $18;
    b          L0012F658;
    lw        $4, 0x14($17);
  L0012F640:
    lhu        $3, 0xC($17);
    addiu      $2, $0, -0x1;
    ori        $3, $3, 0x40;
    b          L0012F68C;
    sh        $3, 0xC($17);
    nop;
  L0012F658:
    blez       $16, L0012F688;
    sw        $4, 0x8($17);
  L0012F660:
    lw         $2, 0x24($17);
    daddu      $6, $16, $0;
    lw         $4, 0x1C($17);
    jalr $31, $2;
    daddu     $5, $18, $0;
    daddu      $3, $2, $0;
    blez       $3, L0012F640;
    subu      $16, $16, $3;
    bgtz       $16, L0012F660;
    addu      $18, $18, $3;
  L0012F688:
    daddu      $2, $0, $0;
  L0012F68C:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

