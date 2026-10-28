#include "types.h"

extern void KprintfSerialMaybe_119308(const char *);
extern void KernelExit_120d18(s32);
extern s32 RFU086_WaitEvnetFlag(s32, s32, s32, s32);

/* Naked `asm void` (lever 6). D_00456C30/D_004468F8/D_00456C68/
   D_00456C80/D_00456C98 hi/lo hardcoded per lever 5. */

asm void InitTLB32MB_1200f8(void)
{
    .set noreorder;
    addiu $29, $29, -0x40;
    lui   $4, 0x45;
    sd    $18, 0x20($29);
    addiu $4, $4, 0x6C30;
    sd    $17, 0x10($29);
    lui   $18, 0x44;
    sd    $16, 0x0($29);
    sd    $31, 0x30($29);
    addiu $16, $18, 0x68F8;
    lw    $5, 0x68F8($18);
    lw    $7, 0x4($16);
    lw    $9, 0x8($16);
    daddu $6, $5, $0;
    addu  $7, $5, $7;
    addu  $9, $7, $9;
    daddu $8, $7, $0;
    addiu $5, $5, -0x1;
    addiu $9, $9, -0x1;
    jal   KprintfSerialMaybe_119308;
    addiu $7, $7, -0x1;
    mtc0  $0, $6;
    sync.p;
    lw    $17, 0x68F8($18);
    slti  $2, $17, 0x31;
    bnez  $2, L00120174;
    daddu $25, $0, $0;
    lui   $4, 0x45;
    jal   KprintfSerialMaybe_119308;
    addiu $4, $4, 0x6C68;
    jal   KernelExit_120d18;
    addiu $4, $0, 0x1;
L00120174:
    slt   $2, $25, $17;
    beqz  $2, L001201B0;
    lw    $16, 0x10($16);
    lw    $5, 0x0($16);
    nop;
L00120188:
    daddu $4, $25, $0;
    lw    $6, 0x4($16);
    lw    $7, 0x8($16);
    lw    $8, 0xC($16);
    jal   RFU086_WaitEvnetFlag;
    addiu $16, $16, 0x10;
    addiu $25, $25, 0x1;
    slt   $2, $25, $17;
    bnel  $2, $0, L00120188;
    lw    $5, 0x0($16);
L001201B0:
    addiu $16, $18, 0x68F8;
    lw    $2, 0x4($16);
    addu  $17, $25, $2;
    slti  $3, $17, 0x31;
    bnez  $3, L001201E0;
    slt   $2, $25, $17;
    lui   $4, 0x45;
    jal   KprintfSerialMaybe_119308;
    addiu $4, $4, 0x6C80;
    jal   KernelExit_120d18;
    addiu $4, $0, 0x1;
    slt   $2, $25, $17;
L001201E0:
    beqz  $2, L00120218;
    lw    $16, 0x14($16);
    lw    $5, 0x0($16);
    nop;
L001201F0:
    daddu $4, $25, $0;
    lw    $6, 0x4($16);
    lw    $7, 0x8($16);
    lw    $8, 0xC($16);
    jal   RFU086_WaitEvnetFlag;
    addiu $16, $16, 0x10;
    addiu $25, $25, 0x1;
    slt   $2, $25, $17;
    bnel  $2, $0, L001201F0;
    lw    $5, 0x0($16);
L00120218:
    addiu $16, $18, 0x68F8;
    sw    $25, 0xC($16);
    mtc0  $25, $6;
    sync.p;
    lw    $2, 0x8($16);
    blezl $2, L00120294;
    daddu $16, $25, $0;
    addu  $17, $25, $2;
    slti  $2, $17, 0x31;
    bnez  $2, L0012025C;
    slt   $2, $25, $17;
    lui   $4, 0x45;
    jal   KprintfSerialMaybe_119308;
    addiu $4, $4, 0x6C98;
    jal   KernelExit_120d18;
    addiu $4, $0, 0x1;
    slt   $2, $25, $17;
L0012025C:
    beqz  $2, L00120290;
    lw    $16, 0x18($16);
    lw    $5, 0x0($16);
L00120268:
    daddu $4, $25, $0;
    lw    $6, 0x4($16);
    lw    $7, 0x8($16);
    lw    $8, 0xC($16);
    jal   RFU086_WaitEvnetFlag;
    addiu $16, $16, 0x10;
    addiu $25, $25, 0x1;
    slt   $2, $25, $17;
    bnel  $2, $0, L00120268;
    lw    $5, 0x0($16);
L00120290:
    daddu $16, $25, $0;
L00120294:
    slti  $2, $16, 0x30;
    beqz  $2, L001202D0;
    sll   $25, $25, 13;
    lui   $2, 0xE000;
    addu  $17, $25, $2;
L001202A8:
    daddu $4, $16, $0;
    daddu $6, $17, $0;
    daddu $5, $0, $0;
    daddu $7, $0, $0;
    daddu $8, $0, $0;
    jal   RFU086_WaitEvnetFlag;
    addiu $16, $16, 0x1;
    slti  $2, $16, 0x30;
    bnez  $2, L001202A8;
    addiu $17, $17, (0xE0002000 & 0xFFFF);
L001202D0:
    ld    $31, 0x30($29);
    daddu $2, $25, $0;
    ld    $18, 0x20($29);
    ld    $17, 0x10($29);
    ld    $16, 0x0($29);
    jr    $31;
    addiu $29, $29, 0x40;
}
