#include "types.h"

extern void MallocR_1310d0(void);

asm void InitSignalR_133fd0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x8($29);
    lw         $2, 0x1D4($16);
    bnel       $2, $0, L00134030;
    daddu     $2, $0, $0;
    jal        MallocR_1310d0;
    addiu     $5, $0, 0x80;
    daddu      $3, $2, $0;
    addiu      $2, $0, -0x1;
    beqz       $3, L00134030;
    sw        $3, 0x1D4($16);
    addiu      $2, $3, 0x7C;
    addiu      $3, $0, 0x1F;
    nop;
  L00134010:
    addiu      $3, $3, -0x1;
    sw         $0, 0x0($2);
    nop;
    nop;
    nop;
    bgez       $3, L00134010;
    addiu     $2, $2, -0x4;
    daddu      $2, $0, $0;
  L00134030:
    ld         $16, 0x0($29);
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
