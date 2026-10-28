#include "types.h"

extern void _lf_bind(void);
extern void _lf_version(void);
extern void sceSifCallRpc(void);

asm void sceSifUnloadModule_11f378(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x20($29);
    sd         $31, 0x30($29);
    daddu      $17, $4, $0;
    jal        _lf_bind;
    sd        $16, 0x10($29);
    bltz       $2, L0011F3F4;
    lui       $2, (0xFFFF0000 >> 16);
    jal        _lf_version;
    nop;
    beqz       $2, L0011F3B4;
    lui       $16, 0x49;
    lui        $2, (0xFFFEFFFC >> 16);
    b          L0011F3F4;
    ori       $2, $2, (0xFFFEFFFC & 0xFFFF);
  L0011F3B4:
    lui        $4, 0x49;
    addiu      $7, $16, -0x6280;
    sw         $17, -0x6280($16);
    addiu      $4, $4, -0x6080;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x8;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x4;
    daddu      $9, $7, $0;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0011F3F4;
    lw        $2, -0x6280($16);
    lui        $2, (0xFFFEFFFF >> 16);
    ori        $2, $2, (0xFFFEFFFF & 0xFFFF);
  L0011F3F4:
    ld         $31, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
