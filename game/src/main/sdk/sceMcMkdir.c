#include "types.h"

extern void sceMcOpen_12ca58(void); /* sceMcOpen, not yet promoted */
/* D_00449558 (mcRunCmdNo) is addressed by raw hi/lo immediate below, per
   this project's naked-asm-void convention -- %hi()/%lo() are not accepted
   inside an asm block. */

/* Naked `asm void` (lever 6): opens a directory entry with the
   create/dir mode bit (0x40) through the shared sceMcOpen path; on
   success records the command as "mkdir" (0xB) for the async status
   poll every mc op goes through afterward. */

asm void sceMcMkdir(void)
{
    .set noreorder;
    addiu $29, $29, -0x10;
    sd    $31, 0x0($29);
    jal   sceMcOpen_12ca58;
    addiu $7, $0, 0x40;
    daddu $4, $2, $0;
    bnez  $4, L0012CBA8;
    ld    $31, 0x0($29);
    lui   $3, 0x45;
    addiu $2, $0, 0xB;
    sw    $2, -0x6AA8($3);
L0012CBA8:
    daddu $2, $4, $0;
    jr    $31;
    addiu $29, $29, 0x10;
}
