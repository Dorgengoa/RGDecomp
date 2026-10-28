#include "types.h"

extern void MemStackAllocQw_14d950(void);

asm void GsPktClose_13f5b0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    lw         $3, 0xE8($4);
    bnel       $3, $0, L0013F6A4;
    ld        $31, 0x0($29);
    lw         $5, 0xF4($4);
    addiu      $3, $0, 0x3F;
    sd         $0, 0x0($5);
    sd         $3, 0x8($5);
    lw         $3, 0xF4($4);
    addiu      $9, $3, 0x10;
    sw         $9, 0xF4($4);
    lw         $8, 0xF8($4);
    subu       $5, $9, $8;
    bgez       $5, L0013F5F8;
    sra       $3, $5, 4;
    addiu      $3, $5, 0xF;
    sra        $3, $3, 4;
  L0013F5F8:
    addiu      $7, $3, -0x1;
    lw         $3, 0xFC($4);
    subu       $5, $9, $3;
    bgez       $5, L0013F614;
    sra       $3, $5, 4;
    addiu      $3, $5, 0xF;
    sra        $3, $3, 4;
  L0013F614:
    addiu      $6, $3, -0x1;
    lw         $3, 0x100($4);
    subu       $5, $9, $3;
    bgez       $5, L0013F630;
    sra       $3, $5, 4;
    addiu      $3, $5, 0xF;
    sra        $3, $3, 4;
  L0013F630:
    blez       $7, L0013F640;
    addiu     $3, $3, -0x1;
    bgtzl      $6, L0013F648;
    ori       $5, $3, 0x8000;
  L0013F640:
    b          L0013F670;
    sw        $8, 0xF4($4);
  L0013F648:
    lui        $3, (0x10000000 >> 16);
    or         $8, $7, $3;
    lw         $7, 0x104($4);
    lui        $3, (0x50000000 >> 16);
    or         $6, $6, $3;
    sw         $8, 0x0($7);
    lw         $3, 0x108($4);
    sw         $6, 0x0($3);
    lw         $3, 0x100($4);
    sw         $5, 0x0($3);
  L0013F670:
    lw         $3, 0xE8($4);
    bnez       $3, L0013F6A0;
    nop;
    lw         $3, 0xF4($4);
    lw         $2, 0xEC($4);
    subu       $2, $3, $2;
    bgez       $2, L0013F698;
    sra       $5, $2, 4;
    addiu      $2, $2, 0xF;
    sra        $5, $2, 4;
  L0013F698:
    jal        MemStackAllocQw_14d950;
    lw        $4, 0x0($4);
  L0013F6A0:
    ld         $31, 0x0($29);
  L0013F6A4:
    jr         $31;
    addiu     $29, $29, 0x10;
}

