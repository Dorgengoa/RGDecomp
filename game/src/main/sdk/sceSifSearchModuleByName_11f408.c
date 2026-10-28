#include "types.h"

extern void _lf_bind(void);
extern void _lf_version(void);
extern void strncpy(void);
extern void sceSifCallRpc(void);

asm void sceSifSearchModuleByName_11f408(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x10($29);
    sd         $31, 0x20($29);
    jal        _lf_bind;
    daddu     $16, $4, $0;
    bltz       $2, L0011F498;
    lui       $2, (0xFFFF0000 >> 16);
    jal        _lf_version;
    nop;
    beql       $2, $0, L0011F440;
    lui       $2, 0x49;
    lui        $2, (0xFFFEFFFC >> 16);
    b          L0011F498;
    ori       $2, $2, (0xFFFEFFFC & 0xFFFF);
  L0011F440:
    daddu      $5, $16, $0;
    addiu      $16, $2, -0x6278;
    addiu      $6, $0, 0xFC;
    jal        strncpy;
    daddu     $4, $16, $0;
    addiu      $3, $16, -0x8;
    lui        $4, 0x49;
    daddu      $7, $3, $0;
    sb         $0, 0x103($3);
    addiu      $4, $4, -0x6080;
    addiu      $5, $0, 0x9;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x200;
    daddu      $9, $7, $0;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0011F498;
    lw        $2, -0x8($16);
    lui        $2, (0xFFFEFFFF >> 16);
    ori        $2, $2, (0xFFFEFFFF & 0xFFFF);
  L0011F498:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
