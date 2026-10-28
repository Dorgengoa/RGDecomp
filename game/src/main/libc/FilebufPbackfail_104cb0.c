#include "types.h"

extern void Ungetc_1364e8(void);

asm void FilebufPbackfail_104cb0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $31, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $16, $5, $0;
    lw         $5, 0x1C($4);
    bnel       $5, $0, L00104CD4;
    lbu       $2, 0x36($4);
    b          L00104D68;
    addiu     $2, $0, -0x1;
  L00104CD4:
    bnel       $2, $0, L00104D1C;
    lw        $3, 0x8($4);
    lbu        $2, 0x35($4);
    beqz       $2, L00104D18;
    nop;
    addiu      $2, $0, -0x1;
    bnel       $16, $2, L00104CFC;
    daddu     $4, $16, $0;
    b          L00104D6C;
    ld        $31, 0x10($29);
  L00104CFC:
    jal        Ungetc_1364e8;
    nop;
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L00104D58;
    addiu     $2, $0, -0x1;
    b          L00104D68;
    daddu     $2, $3, $0;
  L00104D18:
    lw         $3, 0x8($4);
  L00104D1C:
    lw         $2, 0x4($4);
    sltu       $1, $2, $3;
    bnel       $1, $0, L00104D34;
    lw        $3, 0x8($4);
    b          L00104D68;
    addiu     $2, $0, -0x1;
  L00104D34:
    not        $2, $16;
    sltiu      $2, $2, 0x1;
    xori       $2, $2, 0x1;
    addiu      $3, $3, -0x1;
    beqz       $2, L00104D54;
    sw        $3, 0x8($4);
    lw         $2, 0x8($4);
    sb         $16, 0x0($2);
  L00104D54:
    addiu      $2, $0, -0x1;
  L00104D58:
    bne        $16, $2, L00104D64;
    nop;
    daddu      $16, $0, $0;
  L00104D64:
    daddu      $2, $16, $0;
  L00104D68:
    ld         $31, 0x10($29);
  L00104D6C:
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

