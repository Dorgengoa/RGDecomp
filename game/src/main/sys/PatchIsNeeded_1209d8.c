#include "types.h"

extern void GetOsdConfigParam(void);
extern void SetOsdConfigParam(void);

asm void PatchIsNeeded_1209d8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x10($29);
    sd         $31, 0x20($29);
    jal        GetOsdConfigParam;
    daddu     $4, $29, $0;
    lw         $3, 0x0($29);
    lui        $2, (0xFFFF1FFF >> 16);
    ori        $2, $2, (0xFFFF1FFF & 0xFFFF);
    addiu      $16, $29, 0x4;
    and        $3, $3, $2;
    daddu      $4, $16, $0;
    ori        $3, $3, 0x2000;
    jal        SetOsdConfigParam;
    sw        $3, 0x4($29);
    jal        GetOsdConfigParam;
    daddu     $4, $16, $0;
    jal        SetOsdConfigParam;
    daddu     $4, $29, $0;
    lw         $2, 0x4($29);
    ld         $31, 0x20($29);
    srl        $2, $2, 13;
    ld         $16, 0x10($29);
    andi       $2, $2, 0x7;
    sltiu      $2, $2, 0x1;
    jr         $31;
    addiu     $29, $29, 0x30;
}
