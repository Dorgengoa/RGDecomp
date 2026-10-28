#include "types.h"

extern void scePrintf_119288(void);

asm void sceGsPutDrawEnv(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $3, (0x1000A000 >> 16);
    sd         $31, 0x0($29);
    ori        $3, $3, (0x1000A000 & 0xFFFF);
    daddu      $6, $4, $0;
    lw         $2, 0x0($3);
    andi       $2, $2, 0x100;
    beqz       $2, L00108C0C;
    daddu     $4, $0, $0;
    lui        $3, (0x1000A000 >> 16);
    lui        $5, (0x1000000 >> 16);
    ori        $3, $3, (0x1000A000 & 0xFFFF);
    daddu      $2, $4, $0;
    nop;
  L00108BF0:
    sltu       $2, $5, $2;
    bnez       $2, L00108C58;
    addiu     $4, $4, 0x1;
    lw         $2, 0x0($3);
    andi       $2, $2, 0x100;
    bnez       $2, L00108BF0;
    daddu     $2, $4, $0;
  L00108C0C:
    ld         $2, 0x0($6);
    lui        $3, (0x1000A020 >> 16);
    ori        $3, $3, (0x1000A020 & 0xFFFF);
    lui        $4, (0x70000000 >> 16);
    andi       $2, $2, 0x7FFF;
    and        $5, $6, $4;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    addiu      $2, $2, 0x1;
    sw         $2, 0x0($3);
    bne        $5, $4, L00108C6C;
    lui       $2, (0xFFFFFFF >> 16);
    lui        $3, (0x1000A010 >> 16);
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    lui        $4, (0x80000000 >> 16);
    and        $2, $6, $2;
    ori        $3, $3, (0x1000A010 & 0xFFFF);
    b          L00108C7C;
    or        $2, $2, $4;
  L00108C58:
    lui        $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x5C80;
    b          L00108C94;
    addiu     $2, $0, -0x1;
  L00108C6C:
    lui        $3, (0x1000A010 >> 16);
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    ori        $3, $3, (0x1000A010 & 0xFFFF);
    and        $2, $6, $2;
  L00108C7C:
    sw         $2, 0x0($3);
    lui        $3, (0x1000A000 >> 16);
    addiu      $4, $0, 0x101;
    ori        $3, $3, (0x1000A000 & 0xFFFF);
    daddu      $2, $0, $0;
    sw         $4, 0x0($3);
  L00108C94:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

