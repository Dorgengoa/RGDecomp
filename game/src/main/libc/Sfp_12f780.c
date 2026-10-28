#include "types.h"

extern void StdioSinit_12f8b8(void);
extern void SfMoreGlue_12f708(void);

asm void Sfp_12f780(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $17, 0x8($29);
    daddu      $17, $4, $0;
    sd         $16, 0x0($29);
    sd         $18, 0x10($29);
    sd         $31, 0x18($29);
    lw         $2, 0x38($17);
    bnez       $2, L0012F7AC;
    addiu     $16, $17, 0x1D8;
    jal        StdioSinit_12f8b8;
    nop;
  L0012F7AC:
    addiu      $18, $0, 0xC;
  L0012F7B0:
    lw         $3, 0x4($16);
    addiu      $3, $3, -0x1;
    bltz       $3, L0012F7E4;
    lw        $4, 0x8($16);
  L0012F7C0:
    lh         $2, 0xC($4);
    beqz       $2, L0012F820;
    addiu     $3, $3, -0x1;
    nop;
    nop;
    nop;
    nop;
    bgez       $3, L0012F7C0;
    addiu     $4, $4, 0x58;
  L0012F7E4:
    lw         $4, 0x0($16);
    nop;
    bnel       $4, $0, L0012F7B0;
    daddu     $16, $4, $0;
    daddu      $4, $17, $0;
    jal        SfMoreGlue_12f708;
    addiu     $5, $0, 0x4;
    daddu      $3, $2, $0;
    sw         $3, 0x0($16);
    bnez       $3, L0012F818;
    daddu     $4, $3, $0;
    b          L0012F860;
    sw        $18, 0x0($17);
  L0012F818:
    b          L0012F7B0;
    daddu     $16, $4, $0;
  L0012F820:
    addiu      $3, $0, -0x1;
    addiu      $2, $0, 0x1;
    sh         $3, 0xE($4);
    sw         $17, 0x54($4);
    sw         $0, 0x0($4);
    sw         $0, 0x8($4);
    sw         $0, 0x4($4);
    sw         $0, 0x10($4);
    sw         $0, 0x14($4);
    sw         $0, 0x18($4);
    sw         $0, 0x30($4);
    sw         $0, 0x34($4);
    sw         $0, 0x44($4);
    sw         $0, 0x48($4);
    sh         $2, 0xC($4);
    daddu      $2, $4, $0;
  L0012F860:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $31, 0x18($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
