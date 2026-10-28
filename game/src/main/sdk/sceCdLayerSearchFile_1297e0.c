#include "types.h"

extern void CdInitSemas_129508(void);
extern void PollSema(void);
extern void sceCdSync(void);
extern void sceSifInitRpc_119b60(void);
extern void sceSifBindRpc(void);
extern void scePrintf_119288(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdLayerSearchFile_1297e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xC0;
    sd         $19, 0x50($29);
    sd         $18, 0x40($29);
    daddu      $19, $4, $0;
    sd         $22, 0x80($29);
    daddu      $18, $5, $0;
    sd         $31, 0xB0($29);
    lui        $22, 0x44;
    sd         $30, 0xA0($29);
    sd         $23, 0x90($29);
    sd         $21, 0x70($29);
    sd         $20, 0x60($29);
    sd         $17, 0x30($29);
    sd         $16, 0x20($29);
    jal        CdInitSemas_129508;
    sw        $6, 0x10($29);
    lw         $4, 0x7968($22);
    jal        PollSema;
    nop;
    lw         $3, 0x7968($22);
    bne        $3, $2, L00129AAC;
    daddu     $2, $0, $0;
    lui        $3, 0x44;
    addiu      $2, $0, 0x1;
    sw         $2, 0x795C($3);
    jal        sceCdSync;
    addiu     $4, $0, 0x1;
    bnez       $2, L001299E0;
    daddu     $4, $0, $0;
    jal        sceSifInitRpc_119b60;
    lui       $17, 0x44;
    lw         $2, 0x798C($17);
    bgez       $2, L00129914;
    lui       $23, 0x49;
    lui        $20, 0x44;
    lui        $21, 0x49;
    b          L0012989C;
    lui       $30, 0x49;
  L00129878:
    addiu      $3, $0, -0x1;
    nop;
  L00129880:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L00129880;
    nop;
  L0012989C:
    addiu      $16, $23, -0x13C0;
  L001298A0:
    lui        $5, (0x80000597 >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x80000597 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    bgezl      $2, L00129904;
    lw        $2, 0x24($16);
    lw         $2, 0x7950($20);
    blez       $2, L001298D8;
    lui       $2, 0x10;
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7A60;
    lui        $2, (0x100000 >> 16);
  L001298D8:
    addiu      $3, $0, -0x1;
    nop;
  L001298E0:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L001298E0;
    nop;
    b          L001298A0;
    addiu     $16, $23, -0x13C0;
  L00129904:
    beqz       $2, L00129878;
    lui       $2, 0x10;
    b          L00129920;
    sw        $0, 0x798C($17);
  L00129914:
    lui        $20, 0x44;
    lui        $21, 0x49;
    lui        $30, 0x49;
  L00129920:
    lbu        $3, 0x0($18);
    addiu      $4, $21, -0x1540;
    daddu      $5, $0, $0;
    sll        $2, $3, 24;
    beqz       $2, L00129964;
    sb        $3, 0x24($4);
    addiu      $6, $4, 0x24;
    addiu      $5, $5, 0x1;
  L00129940:
    slti       $2, $5, 0x100;
    beqz       $2, L00129964;
    addu      $2, $18, $5;
    addu       $4, $5, $6;
    lbu        $3, 0x0($2);
    sb         $3, 0x0($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L00129940;
    addiu     $5, $5, 0x1;
  L00129964:
    addiu      $2, $0, 0x100;
    bne        $5, $2, L0012997C;
    lw        $2, 0x7950($20);
    addiu      $2, $21, -0x1540;
    sb         $0, 0x123($2);
    lw         $2, 0x7950($20);
  L0012997C:
    blez       $2, L00129994;
    lui       $4, 0x45;
    lui        $5, 0x49;
    addiu      $4, $4, 0x7A80;
    jal        scePrintf_119288;
    addiu     $5, $5, -0x151C;
  L00129994:
    lw         $2, 0x10($29);
    addiu      $16, $21, -0x1540;
    addiu      $5, $0, 0x12C;
    daddu      $4, $16, $0;
    sw         $2, 0x128($16);
    jal        sceSifWriteBackDCache;
    sw        $16, 0x124($16);
    addiu      $4, $23, -0x13C0;
    sw         $0, 0x0($29);
    daddu      $5, $0, $0;
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x12C;
    addiu      $9, $30, -0x1400;
    addiu      $10, $0, 0x4;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L001299F4;
    lui       $2, (0x20000020 >> 16);
  L001299E0:
    lw         $4, 0x7968($22);
    jal        SignalSema;
    nop;
    b          L00129AAC;
    daddu     $2, $0, $0;
  L001299F4:
    or         $2, $16, $2;
    ldl        $3, (0x20000007 & 0xFFFF)($2);
    ldr        $3, (0x20000000 & 0xFFFF)($2);
    ldl        $4, (0x2000000F & 0xFFFF)($2);
    ldr        $4, (0x20000008 & 0xFFFF)($2);
    ldl        $5, (0x20000017 & 0xFFFF)($2);
    ldr        $5, (0x20000010 & 0xFFFF)($2);
    ldl        $6, (0x2000001F & 0xFFFF)($2);
    ldr        $6, (0x20000018 & 0xFFFF)($2);
    sdl        $3, 0x7($19);
    sdr        $3, 0x0($19);
    sdl        $4, 0xF($19);
    sdr        $4, 0x8($19);
    sdl        $5, 0x17($19);
    sdr        $5, 0x10($19);
    sdl        $6, 0x1F($19);
    sdr        $6, 0x18($19);
    lwl        $3, (0x20000023 & 0xFFFF)($2);
    lwr        $3, (0x20000020 & 0xFFFF)($2);
    swl        $3, 0x23($19);
    swr        $3, 0x20($19);
    lw         $3, 0x7950($20);
    blez       $3, L00129A90;
    lui       $4, 0x45;
    addiu      $5, $19, 0x8;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7A98;
    lw         $2, 0x7950($20);
    blez       $2, L00129A90;
    lui       $4, 0x45;
    lw         $5, 0x4($19);
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7AA8;
    lw         $2, 0x7950($20);
    blez       $2, L00129A90;
    lui       $4, 0x45;
    lw         $5, 0x0($19);
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7AB8;
  L00129A90:
    lui        $3, (0x20000000 >> 16);
    addiu      $2, $30, -0x1400;
    or         $2, $2, $3;
    lw         $4, 0x7968($22);
    jal        SignalSema;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L00129AAC:
    ld         $31, 0xB0($29);
    ld         $30, 0xA0($29);
    ld         $23, 0x90($29);
    ld         $22, 0x80($29);
    ld         $21, 0x70($29);
    ld         $20, 0x60($29);
    ld         $19, 0x50($29);
    ld         $18, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0xC0;
}
