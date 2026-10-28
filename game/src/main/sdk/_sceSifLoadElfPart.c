#include "types.h"

extern void _lf_bind(void);
extern void _lf_version(void);
extern void strncpy(void);
extern void sceSifCallRpc(void);

asm void _sceSifLoadElfPart(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $20, 0x50($29);
    sd         $19, 0x40($29);
    daddu      $20, $6, $0;
    sd         $18, 0x30($29);
    daddu      $19, $7, $0;
    sd         $16, 0x10($29);
    daddu      $18, $5, $0;
    sd         $31, 0x60($29);
    daddu      $16, $4, $0;
    jal        _lf_bind;
    sd        $17, 0x20($29);
    bltz       $2, L0011F8C4;
    lui       $2, (0xFFFF0000 >> 16);
    jal        _lf_version;
    nop;
    beql       $2, $0, L0011F834;
    lui       $2, 0x49;
    lui        $2, (0xFFFEFFFC >> 16);
    b          L0011F8C4;
    ori       $2, $2, (0xFFFEFFFC & 0xFFFF);
  L0011F834:
    daddu      $5, $16, $0;
    addiu      $17, $2, -0x6278;
    addiu      $6, $0, 0xFC;
    daddu      $4, $17, $0;
    jal        strncpy;
    addiu     $16, $17, -0x8;
    daddu      $5, $18, $0;
    sb         $0, 0x103($16);
    addiu      $4, $17, 0xFC;
    jal        strncpy;
    addiu     $6, $0, 0xFC;
    lui        $4, 0x49;
    sb         $0, 0x1FF($16);
    daddu      $5, $19, $0;
    addiu      $4, $4, -0x6080;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x200;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x10;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0011F8A4;
    lw        $2, -0x8($17);
    lui        $2, (0xFFFEFFFF >> 16);
    b          L0011F8C4;
    ori       $2, $2, (0xFFFEFFFF & 0xFFFF);
  L0011F8A4:
    bnel       $2, $0, L0011F8B8;
    sw        $2, 0x0($20);
    lui        $2, (0xFFFEFFFD >> 16);
    b          L0011F8C4;
    ori       $2, $2, (0xFFFEFFFD & 0xFFFF);
  L0011F8B8:
    daddu      $2, $0, $0;
    lw         $3, 0x4($16);
    sw         $3, 0x4($20);
  L0011F8C4:
    ld         $31, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}
