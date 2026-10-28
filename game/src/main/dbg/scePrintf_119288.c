#include "types.h"

extern void DisableIntr_120660(void);
extern void printf_118388(void);
extern void EnableIntr_1206b0(void);

asm void scePrintf_119288(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $16, 0x10($29);
    sd         $17, 0x20($29);
    daddu      $16, $4, $0;
    sd         $31, 0x30($29);
    sd         $5, 0x88($29);
    sd         $6, 0x90($29);
    sd         $7, 0x98($29);
    sd         $8, 0xA0($29);
    sd         $9, 0xA8($29);
    sd         $10, 0xB0($29);
    sd         $11, 0xB8($29);
    jal        DisableIntr_120660;
    sw        $0, 0x0($29);
    lui        $4, 0x12;
    lui        $6, (0xFFFFFFFF >> 16);
    daddu      $17, $2, $0;
    addiu      $4, $4, -0x6F08;
    daddu      $7, $16, $0;
    daddu      $5, $29, $0;
    ori        $6, $6, (0xFFFFFFFF & 0xFFFF);
    jal        printf_118388;
    addiu     $8, $29, 0x88;
    beqz       $17, L001192F8;
    ld        $31, 0x30($29);
    jal        EnableIntr_1206b0;
    nop;
    ld         $31, 0x30($29);
  L001192F8:
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0xC0;
}
