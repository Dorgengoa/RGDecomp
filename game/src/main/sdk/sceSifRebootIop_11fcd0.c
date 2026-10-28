#include "types.h"

extern void scePrintf_119288(void);
extern void sceSifInitRpc_119b60(void);
extern void sceSifExitRpc(void);
extern void sceSifResetIop(void);

asm void sceSifRebootIop_11fcd0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    lui        $2, 0x45;
    sd         $17, 0x60($29);
    sd         $16, 0x50($29);
    sd         $31, 0x70($29);
    daddu      $16, $4, $0;
    lb         $3, 0x0($16);
    beqz       $3, L0011FD1C;
    addiu     $17, $2, 0x6C00;
    addiu      $3, $16, -0xB;
  L0011FCF8:
    addiu      $4, $4, 0x1;
    lb         $2, 0x0($4);
    nop;
    nop;
    nop;
    bnez       $2, L0011FCF8;
    nop;
    b          L0011FD24;
    subu      $2, $4, $3;
  L0011FD1C:
    addiu      $3, $16, -0xB;
    subu       $2, $4, $3;
  L0011FD24:
    sltiu      $2, $2, 0x51;
    bnez       $2, L0011FD44;
    lui       $4, 0x45;
    daddu      $5, $16, $0;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x6C10;
    b          L0011FDCC;
    daddu     $2, $0, $0;
  L0011FD44:
    jal        sceSifInitRpc_119b60;
    daddu     $4, $0, $0;
    jal        sceSifExitRpc;
    nop;
    lb         $2, 0x0($17);
    daddu      $3, $29, $0;
    beqz       $2, L0011FD8C;
    lbu       $4, 0x0($17);
    lbu        $5, 0x0($16);
  L0011FD68:
    sb         $4, 0x0($3);
    addiu      $17, $17, 0x1;
    addiu      $3, $3, 0x1;
    lbu        $4, 0x0($17);
    lb         $2, 0x0($17);
    bnez       $2, L0011FD68;
    nop;
    b          L0011FD94;
    daddu     $4, $5, $0;
  L0011FD8C:
    lbu        $5, 0x0($16);
    daddu      $4, $5, $0;
  L0011FD94:
    beql       $4, $0, L0011FDC0;
    sb        $0, 0x0($3);
    nop;
  L0011FDA0:
    sb         $4, 0x0($3);
    addiu      $16, $16, 0x1;
    addiu      $3, $3, 0x1;
    lb         $2, 0x0($16);
    daddu      $4, $2, $0;
    bnez       $2, L0011FDA0;
    nop;
    sb         $0, 0x0($3);
  L0011FDC0:
    daddu      $4, $29, $0;
    jal        sceSifResetIop;
    daddu     $5, $0, $0;
  L0011FDCC:
    ld         $31, 0x70($29);
    ld         $17, 0x60($29);
    ld         $16, 0x50($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
