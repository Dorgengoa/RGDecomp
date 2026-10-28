#include "types.h"

extern void memcpy(void);
extern void Swbuf_138e90(void);

asm void FilebufPutBytesMaybe_106100(void)
{
    .set noreorder;
    addiu      $29, $29, -0x70;
    sd         $31, 0x40($29);
    sq         $19, 0x30($29);
    sq         $18, 0x20($29);
    daddu      $19, $4, $0;
    sq         $17, 0x10($29);
    daddu      $18, $5, $0;
    sq         $16, 0x0($29);
    addiu      $4, $29, 0x60;
    sb         $6, 0x5F($29);
    addiu      $5, $29, 0x5F;
    jal        memcpy;
    daddu     $6, $18, $0;
    blez       $18, L00106208;
    daddu     $17, $0, $0;
    addiu      $16, $29, 0x60;
  L00106140:
    lw         $3, 0x1C($19);
    lw         $2, 0x8($3);
    addiu      $2, $2, -0x1;
    bgez       $2, L001061C0;
    sw        $2, 0x8($3);
    lw         $5, 0x1C($19);
    lw         $3, 0x8($5);
    lw         $2, 0x18($5);
    slt        $2, $3, $2;
    bnez       $2, L001061B0;
    nop;
    lb         $3, 0x0($16);
    addiu      $4, $0, 0xA;
    lw         $2, 0x0($5);
    sb         $3, 0x0($2);
    lw         $5, 0x1C($19);
    lw         $3, 0x0($5);
    lbu        $2, 0x0($3);
    beq        $2, $4, L001061A0;
    nop;
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($5);
    b          L001061A8;
    lbu       $2, 0x0($3);
  L001061A0:
    jal        Swbuf_138e90;
    nop;
  L001061A8:
    b          L001061B8;
    nop;
  L001061B0:
    jal        Swbuf_138e90;
    lb        $4, 0x0($16);
  L001061B8:
    b          L001061E8;
    nop;
  L001061C0:
    lw         $2, 0x1C($19);
    lb         $3, 0x0($16);
    lw         $2, 0x0($2);
    sb         $3, 0x0($2);
    lw         $4, 0x1C($19);
    lw         $3, 0x0($4);
    addiu      $2, $3, 0x1;
    sw         $2, 0x0($4);
    lbu        $2, 0x0($3);
    nop;
  L001061E8:
    addiu      $3, $0, -0x1;
    bnel       $2, $3, L001061FC;
    addiu     $17, $17, 0x1;
    b          L0010620C;
    daddu     $2, $3, $0;
  L001061FC:
    slt        $2, $17, $18;
    bnez       $2, L00106140;
    addiu     $16, $16, 0x1;
  L00106208:
    lbu        $2, 0x5F($29);
  L0010620C:
    ld         $31, 0x40($29);
    lq         $19, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x70;
}

