#include "types.h"

extern void _lf_bind(void);
extern void _lf_version(void);
extern void memcpy(void);
extern void sceSifCallRpc(void);

asm void sceSifStopModule_11f170(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    sd         $22, 0x70($29);
    sd         $19, 0x40($29);
    daddu      $22, $7, $0;
    sd         $17, 0x20($29);
    daddu      $19, $4, $0;
    sd         $16, 0x10($29);
    daddu      $17, $5, $0;
    sd         $31, 0x80($29);
    daddu      $16, $6, $0;
    sd         $21, 0x60($29);
    sd         $20, 0x50($29);
    jal        _lf_bind;
    sd        $18, 0x30($29);
    bltz       $2, L0011F350;
    lui       $2, (0xFFFF0000 >> 16);
    jal        _lf_version;
    nop;
    beqz       $2, L0011F1CC;
    lui       $20, 0x49;
    lui        $2, (0xFFFEFFFC >> 16);
    b          L0011F350;
    ori       $2, $2, (0xFFFEFFFC & 0xFFFF);
  L0011F1CC:
    daddu      $21, $20, $0;
    addiu      $18, $20, -0x6280;
    beqz       $16, L0011F300;
    sw        $19, -0x6280($20);
    slti       $2, $17, 0xFD;
    bnez       $2, L0011F2EC;
    daddu     $5, $16, $0;
    addiu      $4, $18, 0x104;
    or         $2, $16, $4;
    andi       $2, $2, 0x7;
    beqz       $2, L0011F260;
    daddu     $7, $16, $0;
    addiu      $2, $16, 0xE0;
    lui        $5, (0x490000 >> 16);
  L0011F204:
    ldl        $3, 0x7($7);
    ldr        $3, 0x0($7);
    ldl        $6, 0xF($7);
    ldr        $6, 0x8($7);
    ldl        $8, 0x17($7);
    ldr        $8, 0x10($7);
    ldl        $9, 0x1F($7);
    ldr        $9, 0x18($7);
    sdl        $3, 0x7($4);
    sdr        $3, 0x0($4);
    sdl        $6, 0xF($4);
    sdr        $6, 0x8($4);
    sdl        $8, 0x17($4);
    sdr        $8, 0x10($4);
    sdl        $9, 0x1F($4);
    sdr        $9, 0x18($4);
    addiu      $7, $7, 0x20;
    addiu      $4, $4, 0x20;
    nop;
    bne        $7, $2, L0011F204;
    nop;
    b          L0011F29C;
    nop;
  L0011F260:
    addiu      $2, $16, 0xE0;
    lui        $5, 0x49;
  L0011F268:
    ld         $10, 0x0($7);
    ld         $3, 0x8($7);
    ld         $6, 0x10($7);
    ld         $8, 0x18($7);
    sd         $10, 0x0($4);
    sd         $3, 0x8($4);
    sd         $6, 0x10($4);
    sd         $8, 0x18($4);
    addiu      $7, $7, 0x20;
    addiu      $4, $4, 0x20;
    nop;
    bne        $7, $2, L0011F268;
    nop;
  L0011F29C:
    ldl        $9, 0x7($7);
    ldr        $9, 0x0($7);
    ldl        $10, 0xF($7);
    ldr        $10, 0x8($7);
    ldl        $6, 0x17($7);
    ldr        $6, 0x10($7);
    lwl        $8, 0x1B($7);
    lwr        $8, 0x18($7);
    sdl        $9, 0x7($4);
    sdr        $9, 0x0($4);
    sdl        $10, 0xF($4);
    sdr        $10, 0x8($4);
    sdl        $6, 0x17($4);
    sdr        $6, 0x10($4);
    swl        $8, 0x1B($4);
    addiu      $3, $21, -0x6280;
    addiu      $2, $0, 0xFC;
    swr        $8, 0x18($4);
    b          L0011F308;
    sw        $2, 0x4($3);
  L0011F2EC:
    addiu      $4, $18, 0x104;
    jal        memcpy;
    daddu     $6, $17, $0;
    b          L0011F304;
    sw        $17, 0x4($18);
  L0011F300:
    sw         $0, 0x4($18);
  L0011F304:
    lui        $5, 0x49;
  L0011F308:
    addiu      $16, $21, -0x6280;
    addiu      $4, $5, -0x6080;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x7;
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x200;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x8;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0011F348;
    lw        $3, 0x4($16);
    lui        $2, (0xFFFEFFFF >> 16);
    b          L0011F350;
    ori       $2, $2, (0xFFFEFFFF & 0xFFFF);
  L0011F348:
    lw         $2, -0x6280($20);
    sw         $3, 0x0($22);
  L0011F350:
    ld         $31, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
