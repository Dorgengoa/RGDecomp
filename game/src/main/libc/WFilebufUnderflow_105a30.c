#include "types.h"

extern void WFilebufGetcPeek_105c30(void);
extern void WFilebufGetBytesPeekMaybe_105ce0(void);

asm void WFilebufUnderflow_105a30(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    lw         $2, 0x1C($4);
    bnez       $2, L00105A54;
    daddu     $16, $4, $0;
    b          L00105B94;
    addiu     $2, $0, -0x1;
  L00105A54:
    lbu        $2, 0x66($16);
    beql       $2, $0, L00105ACC;
    sb        $0, 0x64($16);
    lw         $2, 0x8($16);
    bnez       $2, L00105AC8;
    nop;
    lw         $3, 0x14($16);
    lw         $2, 0x10($16);
    sltu       $1, $2, $3;
    beqz       $1, L00105AA0;
    daddu     $17, $0, $0;
    lw         $25, 0x0($4);
    lw         $25, 0x34($25);
    jalr $31, $25;
    addiu     $5, $0, -0x1;
    addiu      $3, $0, -0x1;
    bne        $2, $3, L00105AA0;
    nop;
    daddiu     $17, $0, 0x1;
  L00105AA0:
    beql       $17, $0, L00105AB0;
    sw        $0, 0x14($16);
    b          L00105B94;
    addiu     $2, $0, -0x1;
  L00105AB0:
    addiu      $2, $16, 0x24;
    sw         $0, 0x10($16);
    sw         $0, 0x18($16);
    sw         $2, 0x4($16);
    sw         $2, 0x8($16);
    sw         $2, 0xC($16);
  L00105AC8:
    sb         $0, 0x64($16);
  L00105ACC:
    lw         $3, 0x8($16);
    lw         $2, 0xC($16);
    sltu       $1, $3, $2;
    beql       $1, $0, L00105AE8;
    lbu       $2, 0x65($16);
    b          L00105B94;
    lhu       $2, 0x0($3);
  L00105AE8:
    beql       $2, $0, L00105B08;
    xor       $6, $3, $0;
    xor        $5, $3, $0;
    daddu      $4, $16, $0;
    jal        WFilebufGetcPeek_105c30;
    sltiu     $5, $5, 0x1;
    b          L00105B1C;
    addiu     $3, $0, -0x1;
  L00105B08:
    daddu      $4, $16, $0;
    sltiu      $6, $6, 0x1;
    jal        WFilebufGetBytesPeekMaybe_105ce0;
    addiu     $5, $0, 0x4;
    addiu      $3, $0, -0x1;
  L00105B1C:
    bnel       $2, $3, L00105B2C;
    lw        $3, 0x8($16);
    b          L00105B94;
    daddu     $2, $3, $0;
  L00105B2C:
    beqz       $3, L00105B94;
    andi      $5, $2, 0xFFFF;
    lw         $4, 0xC($16);
    lw         $3, 0x4($16);
    subu       $3, $4, $3;
    bgez       $3, L00105B50;
    sra       $4, $3, 2;
    addiu      $3, $3, 0x3;
    sra        $4, $3, 2;
  L00105B50:
    addiu      $3, $0, 0x10;
    bnel       $4, $3, L00105B6C;
    addiu     $3, $4, 0x1;
    lw         $3, 0x60($16);
    addiu      $4, $0, 0x1;
    sw         $3, 0x24($16);
    addiu      $3, $4, 0x1;
  L00105B6C:
    addiu      $4, $16, 0x24;
    sll        $3, $3, 2;
    sw         $4, 0x4($16);
    addu       $3, $16, $3;
    addiu      $4, $3, 0x20;
    addiu      $3, $3, 0x24;
    sw         $4, 0x8($16);
    sw         $3, 0xC($16);
    lw         $3, 0x8($16);
    sh         $5, 0x0($3);
  L00105B94:
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

