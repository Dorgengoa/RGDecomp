#include "types.h"

extern void FilebufGetcPeek_105f30(void);
extern void FilebufGetBytesPeekMaybe_105fe0(void);

asm void FilebufUnderflow_104eb0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    lw         $2, 0x1C($4);
    bnez       $2, L00104ED4;
    daddu     $16, $4, $0;
    b          L00105004;
    addiu     $2, $0, -0x1;
  L00104ED4:
    lbu        $2, 0x36($16);
    beql       $2, $0, L00104F4C;
    sb        $0, 0x34($16);
    lw         $2, 0x8($16);
    bnez       $2, L00104F48;
    nop;
    lw         $3, 0x14($16);
    lw         $2, 0x10($16);
    sltu       $1, $2, $3;
    beqz       $1, L00104F20;
    daddu     $17, $0, $0;
    lw         $25, 0x0($4);
    lw         $25, 0x34($25);
    jalr $31, $25;
    addiu     $5, $0, -0x1;
    addiu      $3, $0, -0x1;
    bne        $2, $3, L00104F20;
    nop;
    daddiu     $17, $0, 0x1;
  L00104F20:
    beql       $17, $0, L00104F30;
    sw        $0, 0x14($16);
    b          L00105004;
    addiu     $2, $0, -0x1;
  L00104F30:
    addiu      $2, $16, 0x24;
    sw         $0, 0x10($16);
    sw         $0, 0x18($16);
    sw         $2, 0x4($16);
    sw         $2, 0x8($16);
    sw         $2, 0xC($16);
  L00104F48:
    sb         $0, 0x34($16);
  L00104F4C:
    lw         $3, 0x8($16);
    lw         $2, 0xC($16);
    sltu       $1, $3, $2;
    beql       $1, $0, L00104F68;
    lbu       $2, 0x35($16);
    b          L00105004;
    lbu       $2, 0x0($3);
  L00104F68:
    beql       $2, $0, L00104F88;
    xor       $6, $3, $0;
    xor        $5, $3, $0;
    daddu      $4, $16, $0;
    jal        FilebufGetcPeek_105f30;
    sltiu     $5, $5, 0x1;
    b          L00104F9C;
    addiu     $3, $0, -0x1;
  L00104F88:
    daddu      $4, $16, $0;
    sltiu      $6, $6, 0x1;
    jal        FilebufGetBytesPeekMaybe_105fe0;
    addiu     $5, $0, 0x1;
    addiu      $3, $0, -0x1;
  L00104F9C:
    bnel       $2, $3, L00104FAC;
    lw        $3, 0x8($16);
    b          L00105004;
    daddu     $2, $3, $0;
  L00104FAC:
    dsll32     $6, $2, 24;
    beqz       $3, L00105004;
    dsra32    $6, $6, 24;
    lw         $5, 0xC($16);
    addiu      $3, $0, 0x10;
    lw         $4, 0x4($16);
    subu       $4, $5, $4;
    bnel       $4, $3, L00104FE0;
    addiu     $3, $4, 0x1;
    lw         $3, 0x30($16);
    addiu      $4, $0, 0x4;
    sw         $3, 0x24($16);
    addiu      $3, $4, 0x1;
  L00104FE0:
    addiu      $4, $16, 0x24;
    addu       $3, $16, $3;
    sw         $4, 0x4($16);
    addiu      $4, $3, 0x23;
    addiu      $3, $3, 0x24;
    sw         $4, 0x8($16);
    sw         $3, 0xC($16);
    lw         $3, 0x8($16);
    sb         $6, 0x0($3);
  L00105004:
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

