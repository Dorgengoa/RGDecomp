#include "types.h"

extern void DisableIntr_120660(void);
extern void printf_118388(void);
extern void EnableIntr_1206b0(void);

asm void sceVprintfMaybe_119218(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $18, 0x30($29);
    sd         $17, 0x20($29);
    daddu      $18, $5, $0;
    sd         $16, 0x10($29);
    daddu      $17, $4, $0;
    sd         $31, 0x40($29);
    jal        DisableIntr_120660;
    sw        $0, 0x0($29);
    lui        $4, 0x12;
    lui        $6, (0xFFFFFFFF >> 16);
    daddu      $16, $2, $0;
    addiu      $4, $4, -0x6F08;
    daddu      $7, $17, $0;
    daddu      $8, $18, $0;
    daddu      $5, $29, $0;
    jal        printf_118388;
    ori       $6, $6, (0xFFFFFFFF & 0xFFFF);
    beqz       $16, L00119274;
    ld        $31, 0x40($29);
    jal        EnableIntr_1206b0;
    nop;
    ld         $31, 0x40($29);
  L00119274:
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
