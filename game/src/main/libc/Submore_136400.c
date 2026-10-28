#include "types.h"

extern void MallocR_1310d0(void);
extern void ReallocR_1337d8(void);
extern void memcpy(void);

asm void Submore_136400(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $18, 0x10($29);
    daddu      $18, $4, $0;
    sd         $16, 0x0($29);
    addiu      $2, $18, 0x40;
    sd         $17, 0x8($29);
    sd         $19, 0x18($29);
    sd         $20, 0x20($29);
    sd         $31, 0x28($29);
    lw         $5, 0x30($18);
    bnel       $5, $2, L00136488;
    lw        $19, 0x34($18);
    lw         $4, 0x54($18);
    jal        MallocR_1310d0;
    addiu     $5, $0, 0x400;
    daddu      $17, $2, $0;
    beqz       $17, L001364C8;
    addiu     $2, $0, -0x1;
    addiu      $2, $0, 0x400;
    sw         $17, 0x30($18);
    sw         $2, 0x34($18);
    addiu      $19, $0, 0x2;
    addiu      $17, $17, 0x3FD;
    addiu      $4, $18, 0x42;
  L00136460:
    lbu        $3, 0x0($4);
    addiu      $4, $4, -0x1;
    addu       $2, $17, $19;
    addiu      $19, $19, -0x1;
    nop;
    bgez       $19, L00136460;
    sb        $3, 0x0($2);
    sw         $17, 0x0($18);
    b          L001364C8;
    daddu     $2, $0, $0;
  L00136488:
    lw         $4, 0x54($18);
    sll        $20, $19, 1;
    jal        ReallocR_1337d8;
    daddu     $6, $20, $0;
    daddu      $17, $2, $0;
    beqz       $17, L001364C8;
    addiu     $2, $0, -0x1;
    addu       $16, $17, $19;
    daddu      $6, $19, $0;
    daddu      $4, $16, $0;
    jal        memcpy;
    daddu     $5, $17, $0;
    sw         $16, 0x0($18);
    sw         $20, 0x34($18);
    daddu      $2, $0, $0;
    sw         $17, 0x30($18);
  L001364C8:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $31, 0x28($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

