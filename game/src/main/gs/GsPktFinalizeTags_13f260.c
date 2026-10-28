#include "types.h"

asm void GsPktFinalizeTags_13f260(void)
{
    .set noreorder;
    lw         $3, 0x114($4);
    bnel       $3, $0, L0013F304;
    lw        $10, 0xF8($4);
    lw         $9, 0xF8($4);
    lw         $8, 0xF4($4);
    subu       $5, $8, $9;
    bgez       $5, L0013F288;
    sra       $3, $5, 4;
    addiu      $3, $5, 0xF;
    sra        $3, $3, 4;
  L0013F288:
    addiu      $7, $3, -0x1;
    lw         $3, 0xFC($4);
    subu       $5, $8, $3;
    bgez       $5, L0013F2A4;
    sra       $3, $5, 4;
    addiu      $3, $5, 0xF;
    sra        $3, $3, 4;
  L0013F2A4:
    addiu      $6, $3, -0x1;
    lw         $3, 0x100($4);
    subu       $5, $8, $3;
    bgez       $5, L0013F2C0;
    sra       $3, $5, 4;
    addiu      $3, $5, 0xF;
    sra        $3, $3, 4;
  L0013F2C0:
    blez       $7, L0013F2D0;
    addiu     $3, $3, -0x1;
    bgtzl      $6, L0013F2D8;
    ori       $5, $3, 0x8000;
  L0013F2D0:
    b          L0013F3A8;
    sw        $9, 0xF4($4);
  L0013F2D8:
    lui        $3, (0x10000000 >> 16);
    or         $8, $7, $3;
    lw         $7, 0x104($4);
    lui        $3, (0x50000000 >> 16);
    or         $6, $6, $3;
    sw         $8, 0x0($7);
    lw         $3, 0x108($4);
    sw         $6, 0x0($3);
    lw         $3, 0x100($4);
    b          L0013F3A8;
    sw        $5, 0x0($3);
  L0013F304:
    lw         $6, 0xF4($4);
    subu       $5, $6, $10;
    bgez       $5, L0013F31C;
    sra       $3, $5, 4;
    addiu      $3, $5, 0xF;
    sra        $3, $3, 4;
  L0013F31C:
    addiu      $7, $3, -0x1;
    lw         $3, 0xFC($4);
    subu       $5, $6, $3;
    bgez       $5, L0013F338;
    sra       $3, $5, 4;
    addiu      $3, $5, 0xF;
    sra        $3, $3, 4;
  L0013F338:
    addiu      $9, $3, -0x1;
    lw         $3, 0x100($4);
    subu       $5, $6, $3;
    bgez       $5, L0013F354;
    sra       $3, $5, 4;
    addiu      $3, $5, 0xF;
    sra        $3, $3, 4;
  L0013F354:
    blez       $7, L0013F364;
    addiu     $8, $3, -0x1;
    bgtzl      $9, L0013F36C;
    lui       $3, (0x10000000 >> 16);
  L0013F364:
    b          L0013F3A8;
    sw        $10, 0xF4($4);
  L0013F36C:
    lw         $6, 0x104($4);
    or         $7, $7, $3;
    lui        $3, (0x50000000 >> 16);
    or         $5, $9, $3;
    sw         $7, 0x0($6);
    lw         $3, 0x108($4);
    sw         $5, 0x0($3);
    lw         $3, 0x118($4);
    bnez       $3, L0013F398;
    div $8, $3;
        .word 0x000001CD;
  L0013F398:
    lw         $3, 0x100($4);
    mflo       $4;
    ori        $4, $4, 0x8000;
    sw         $4, 0x0($3);
  L0013F3A8:
    jr         $31;
    nop;
}

