#include "types.h"

extern void cd_callback(void);

asm void CdReadUnalignedCb_129450(void)
{
    .set noreorder;
    lui        $5, (0x20000004 >> 16);
    or         $7, $4, $5;
    lw         $2, (0x20000000 & 0xFFFF)($7);
    blez       $2, L001294B0;
    daddu     $6, $0, $0;
    lw         $9, (0x20000008 & 0xFFFF)($7);
    blez       $2, L001294B0;
    or        $10, $9, $5;
    addiu      $8, $7, (0x20000010 & 0xFFFF);
    lui        $11, 0x44;
    addu       $2, $8, $6;
    nop;
  L00129480:
    addu       $5, $10, $6;
    lbu        $3, 0x0($2);
    addu       $4, $9, $6;
    addiu      $6, $6, 0x1;
    sb         $3, (0x20000000 & 0xFFFF)($5);
    sb         $3, 0x0($4);
    lw         $2, (0x20000000 & 0xFFFF)($7);
    slt        $2, $6, $2;
    bnez       $2, L00129480;
    addu      $2, $8, $6;
    b          L001294B8;
    lw        $3, (0x20000004 & 0xFFFF)($7);
  L001294B0:
    lui        $11, 0x44;
    lw         $3, (0x20000004 & 0xFFFF)($7);
  L001294B8:
    blez       $3, L00129500;
    lui       $2, (0x20000000 >> 16);
    lw         $9, (0x2000000C & 0xFFFF)($7);
    daddu      $6, $0, $0;
    blez       $3, L00129500;
    or        $10, $9, $2;
    addiu      $8, $7, (0x20000050 & 0xFFFF);
    addu       $2, $8, $6;
  L001294D8:
    addu       $5, $10, $6;
    lbu        $3, 0x0($2);
    addu       $4, $9, $6;
    addiu      $6, $6, 0x1;
    sb         $3, (0x20000000 & 0xFFFF)($5);
    sb         $3, 0x0($4);
    lw         $2, (0x20000004 & 0xFFFF)($7);
    slt        $2, $6, $2;
    bnez       $2, L001294D8;
    addu      $2, $8, $6;
  L00129500:
    j          cd_callback;
    addiu     $4, $11, 0x79A0;
}
