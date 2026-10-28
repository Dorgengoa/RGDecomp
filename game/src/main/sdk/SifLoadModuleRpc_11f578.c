#include "types.h"

extern void _lf_bind(void);
extern void _lf_version(void);
extern void strncpy(void);
extern void memcpy(void);
extern void sceSifCallRpc(void);

asm void SifLoadModuleRpc_11f578(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $20, 0x50($29);
    sd         $19, 0x40($29);
    daddu      $20, $7, $0;
    sd         $18, 0x30($29);
    daddu      $19, $8, $0;
    sd         $17, 0x20($29);
    daddu      $18, $5, $0;
    sd         $16, 0x10($29);
    daddu      $17, $4, $0;
    sd         $31, 0x70($29);
    daddu      $16, $6, $0;
    jal        _lf_bind;
    sd        $21, 0x60($29);
    bltz       $2, L0011F778;
    lui       $2, (0xFFFF0000 >> 16);
    jal        _lf_version;
    nop;
    beql       $2, $0, L0011F5D4;
    lui       $2, 0x49;
    lui        $2, (0xFFFEFFFC >> 16);
    b          L0011F778;
    ori       $2, $2, (0xFFFEFFFC & 0xFFFF);
  L0011F5D4:
    daddu      $5, $17, $0;
    addiu      $17, $2, -0x6278;
    addiu      $6, $0, 0xFC;
    jal        strncpy;
    daddu     $4, $17, $0;
    addiu      $2, $17, -0x8;
    beqz       $16, L0011F720;
    sb        $0, 0x103($2);
    slti       $2, $18, 0xFD;
    bnez       $2, L0011F708;
    daddu     $5, $16, $0;
    addiu      $4, $17, 0xFC;
    or         $2, $16, $4;
    andi       $2, $2, 0x7;
    beqz       $2, L0011F67C;
    daddu     $3, $16, $0;
    addiu      $2, $16, 0xE0;
    lui        $21, 0x49;
    lui        $5, (0x490000 >> 16);
  L0011F620:
    ldl        $6, 0x7($3);
    ldr        $6, 0x0($3);
    ldl        $7, 0xF($3);
    ldr        $7, 0x8($3);
    ldl        $8, 0x17($3);
    ldr        $8, 0x10($3);
    ldl        $9, 0x1F($3);
    ldr        $9, 0x18($3);
    sdl        $6, 0x7($4);
    sdr        $6, 0x0($4);
    sdl        $7, 0xF($4);
    sdr        $7, 0x8($4);
    sdl        $8, 0x17($4);
    sdr        $8, 0x10($4);
    sdl        $9, 0x1F($4);
    sdr        $9, 0x18($4);
    addiu      $3, $3, 0x20;
    addiu      $4, $4, 0x20;
    nop;
    bne        $3, $2, L0011F620;
    nop;
    b          L0011F6BC;
    nop;
  L0011F67C:
    addiu      $2, $16, 0xE0;
    lui        $21, 0x49;
    lui        $5, 0x49;
  L0011F688:
    ld         $6, 0x0($3);
    ld         $7, 0x8($3);
    ld         $8, 0x10($3);
    ld         $9, 0x18($3);
    sd         $6, 0x0($4);
    sd         $7, 0x8($4);
    sd         $8, 0x10($4);
    sd         $9, 0x18($4);
    addiu      $3, $3, 0x20;
    addiu      $4, $4, 0x20;
    nop;
    bne        $3, $2, L0011F688;
    nop;
  L0011F6BC:
    ldl        $6, 0x7($3);
    ldr        $6, 0x0($3);
    ldl        $7, 0xF($3);
    ldr        $7, 0x8($3);
    ldl        $8, 0x17($3);
    ldr        $8, 0x10($3);
    lwl        $9, 0x1B($3);
    lwr        $9, 0x18($3);
    sdl        $6, 0x7($4);
    sdr        $6, 0x0($4);
    sdl        $7, 0xF($4);
    sdr        $7, 0x8($4);
    sdl        $8, 0x17($4);
    sdr        $8, 0x10($4);
    swl        $9, 0x1B($4);
    addiu      $2, $0, 0xFC;
    swr        $9, 0x18($4);
    b          L0011F730;
    sw        $2, -0x6280($21);
  L0011F708:
    addiu      $4, $17, 0xFC;
    daddu      $6, $18, $0;
    jal        memcpy;
    lui       $21, 0x49;
    b          L0011F72C;
    sw        $18, -0x8($17);
  L0011F720:
    sb         $0, 0x104($2);
    lui        $21, 0x49;
    sw         $0, -0x8($17);
  L0011F72C:
    lui        $5, 0x49;
  L0011F730:
    addiu      $16, $21, -0x6280;
    addiu      $4, $5, -0x6080;
    daddu      $5, $19, $0;
    sw         $0, 0x0($29);
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x200;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x8;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgezl      $2, L0011F770;
    lw        $3, 0x4($16);
    lui        $2, (0xFFFEFFFF >> 16);
    b          L0011F778;
    ori       $2, $2, (0xFFFEFFFF & 0xFFFF);
  L0011F770:
    lw         $2, -0x6280($21);
    sw         $3, 0x0($20);
  L0011F778:
    ld         $31, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
