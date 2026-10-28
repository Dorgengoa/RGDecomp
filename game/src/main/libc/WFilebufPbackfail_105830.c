#include "types.h"

extern void Ungetc_1364e8(void);

asm void WFilebufPbackfail_105830(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $31, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $16, $5, $0;
    lw         $5, 0x1C($4);
    bnel       $5, $0, L00105854;
    lbu       $2, 0x66($4);
    b          L001058E8;
    addiu     $2, $0, -0x1;
  L00105854:
    bnel       $2, $0, L0010589C;
    lw        $3, 0x8($4);
    lbu        $2, 0x65($4);
    beqz       $2, L00105898;
    nop;
    addiu      $2, $0, -0x1;
    bnel       $16, $2, L0010587C;
    daddu     $4, $16, $0;
    b          L001058EC;
    ld        $31, 0x10($29);
  L0010587C:
    jal        Ungetc_1364e8;
    nop;
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L001058D8;
    addiu     $2, $0, -0x1;
    b          L001058E8;
    daddu     $2, $3, $0;
  L00105898:
    lw         $3, 0x8($4);
  L0010589C:
    lw         $2, 0x4($4);
    sltu       $1, $2, $3;
    bnel       $1, $0, L001058B4;
    lw        $3, 0x8($4);
    b          L001058E8;
    addiu     $2, $0, -0x1;
  L001058B4:
    not        $2, $16;
    sltiu      $2, $2, 0x1;
    xori       $2, $2, 0x1;
    addiu      $3, $3, -0x4;
    beqz       $2, L001058D4;
    sw        $3, 0x8($4);
    lw         $2, 0x8($4);
    sh         $16, 0x0($2);
  L001058D4:
    addiu      $2, $0, -0x1;
  L001058D8:
    bne        $16, $2, L001058E4;
    nop;
    daddu      $16, $0, $0;
  L001058E4:
    daddu      $2, $16, $0;
  L001058E8:
    ld         $31, 0x10($29);
  L001058EC:
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

