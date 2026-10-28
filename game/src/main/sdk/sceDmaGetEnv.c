#include "types.h"

asm void sceDmaGetEnv(void)
{
    .set noreorder;
    lui        $3, 0x48;
    addiu      $8, $3, 0x5978;
    ldl        $5, 0x7($8);
    ldr        $5, 0x0($8);
    ldl        $6, 0xF($8);
    ldr        $6, 0x8($8);
    lw         $7, 0x10($8);
    sdl        $5, 0x7($4);
    sdr        $5, 0x0($4);
    sdl        $6, 0xF($4);
    sdr        $6, 0x8($4);
    sw         $7, 0x10($4);
    jr         $31;
    daddu     $2, $4, $0;
}

