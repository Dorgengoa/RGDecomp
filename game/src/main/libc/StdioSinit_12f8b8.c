#include "types.h"

extern void StdioStdInit_12f6a8(void);

asm void StdioSinit_12f8b8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    lui        $2, 0x13;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    addiu      $2, $2, -0x788;
    addiu      $3, $0, 0x1;
    sd         $17, 0x8($29);
    addiu      $17, $16, 0x1E4;
    sd         $31, 0x10($29);
    daddu      $4, $17, $0;
    sw         $2, 0x3C($16);
    daddu      $7, $16, $0;
    sw         $3, 0x38($16);
    addiu      $5, $0, 0x4;
    jal        StdioStdInit_12f6a8;
    daddu     $6, $0, $0;
    addiu      $4, $16, 0x23C;
    daddu      $7, $16, $0;
    addiu      $5, $0, 0x9;
    jal        StdioStdInit_12f6a8;
    addiu     $6, $0, 0x1;
    addiu      $4, $16, 0x294;
    daddu      $7, $16, $0;
    addiu      $5, $0, 0xA;
    jal        StdioStdInit_12f6a8;
    addiu     $6, $0, 0x2;
    sw         $0, 0x1D8($16);
    addiu      $2, $0, 0x3;
    sw         $17, 0x1E0($16);
    sw         $2, 0x1DC($16);
    ld         $17, 0x8($29);
    ld         $16, 0x0($29);
    ld         $31, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
