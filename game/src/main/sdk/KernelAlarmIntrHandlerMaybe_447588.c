#include "types.h"

extern void func_076460(void);
extern void func_076680(void);

/* Naked `asm void` (lever 6). func_076460/func_076680 are file-offset
   style names (no vaddr-based symbol found for them) -- declared extern
   anyway since only the `jal` relocation needs a name, not a resolvable
   address, for the byte match. Six trailing nops past the registered
   size are padding. */

asm void KernelAlarmIntrHandlerMaybe_447588(void)
{
    .set noreorder;
    addiu $29, $29, -0xB0;
    daddu $8, $0, $0;
    sd    $31, 0xA0($29);
    sd    $23, 0x90($29);
    sd    $22, 0x80($29);
    sd    $21, 0x70($29);
    sd    $20, 0x60($29);
    sd    $19, 0x50($29);
    sd    $18, 0x40($29);
    sd    $17, 0x30($29);
    sd    $16, 0x20($29);
    lui   $17, 0x8007;
    lui   $18, 0x8007;
    nop;
L004475C0:
    lw    $2, (0x80076700 & 0xFFFF)($17);
    slt   $2, $8, $2;
    beqz  $2, L004475F4;
    addiu $3, $0, 0x14;
    addiu $4, $18, (0x80076740 & 0xFFFF);
    mult  $3, $8, $3;
    lhu   $5, (0x80076740 & 0xFFFF)($18);
    addu  $3, $3, $4;
    lhu   $2, 0x0($3);
    beq   $5, $2, L004475C0;
    addiu $8, $8, 0x1;
    jal   func_076460;
    daddu $4, $2, $0;
L004475F4:
    lui   $2, 0x8007;
    daddu $22, $17, $0;
    addiu $20, $2, (0x80076740 & 0xFFFF);
    addiu $19, $0, 0x14;
    lui   $21, 0x8007;
    b     L0044761C;
    addiu $23, $0, 0x1;
L00447610:
    lhu   $2, (0x80076740 & 0xFFFF)($18);
    bne   $3, $2, L00447710;
    lw    $2, (0x80076700 & 0xFFFF)($17);
L0044761C:
    lw    $2, (0x80076700 & 0xFFFF)($22);
    daddu $8, $0, $0;
    addiu $6, $18, (0x80076740 & 0xFFFF);
    ldl   $3, 0x7($6);
    ldr   $3, 0x0($6);
    ldl   $4, 0xF($6);
    ldr   $4, 0x8($6);
    lw    $5, 0x10($6);
    sdl   $3, 0x7($29);
    sdr   $3, 0x0($29);
    sdl   $4, 0xF($29);
    sdr   $4, 0x8($29);
    sw    $5, 0x10($29);
    addiu $2, $2, -0x1;
    blez  $2, L004476C0;
    sw    $2, (0x80076700 & 0xFFFF)($22);
    lw    $9, (0x80076700 & 0xFFFF)($17);
    lw    $10, 0x10($29);
    lw    $6, 0x4($29);
    lhu   $7, 0x0($29);
    nop;
L00447670:
    mult  $3, $8, $19;
    addiu $2, $8, 0x1;
    daddu $8, $2, $0;
    addu  $5, $3, $20;
    mult  $3, $2, $19;
    addu  $4, $3, $20;
    ldl   $11, 0x7($4);
    ldr   $11, 0x0($4);
    ldl   $12, 0xF($4);
    ldr   $12, 0x8($4);
    lw    $13, 0x10($4);
    sdl   $11, 0x7($5);
    sdr   $11, 0x0($5);
    sdl   $12, 0xF($5);
    sdr   $12, 0x8($5);
    slt   $3, $8, $9;
    bnez  $3, L00447670;
    sw    $13, 0x10($5);
    b     L004476CC;
    nop;
L004476C0:
    lw    $10, 0x10($29);
    lw    $6, 0x4($29);
    lhu   $7, 0x0($29);
L004476CC:
    daddu $16, $28, $0;
    daddu $28, $10, $0;
    ld    $3, (0x80076708 & 0xFFFF)($21);
    dsllv $2, $23, $6;
    nor   $2, $0, $2;
    lui   $4, (0x82000 >> 16);
    and   $3, $3, $2;
    lw    $5, 0x8($29);
    lw    $8, 0xC($29);
    ori   $4, $4, (0x82000 & 0xFFFF);
    jal   func_076680;
    sd    $3, (0x80076708 & 0xFFFF)($21);
    daddu $28, $16, $0;
    lw    $2, (0x80076700 & 0xFFFF)($17);
    bgtz  $2, L00447610;
    lhu   $3, 0x0($29);
    lw    $2, (0x80076700 & 0xFFFF)($17);
L00447710:
    blez  $2, L00447728;
    addiu $3, $0, 0x483;
    jal   func_076460;
    lhu   $4, (0x80076740 & 0xFFFF)($18);
    b     L00447734;
    nop;
L00447728:
    lui   $2, (0xB0001810 >> 16);
    ori   $2, $2, (0xB0001810 & 0xFFFF);
    sw    $3, 0x0($2);
L00447734:
    sync;
    ei;
    ld    $31, 0xA0($29);
    ld    $23, 0x90($29);
    ld    $22, 0x80($29);
    ld    $21, 0x70($29);
    ld    $20, 0x60($29);
    ld    $19, 0x50($29);
    ld    $18, 0x40($29);
    ld    $17, 0x30($29);
    ld    $16, 0x20($29);
    jr    $31;
    addiu $29, $29, 0xB0;
}
