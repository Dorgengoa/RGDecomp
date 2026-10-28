#include "types.h"

extern void sceSifBindRpc(void);
extern void scePadGetModVersion(void);
extern void scePrintf_119288(void);
extern void PadInitAfterBindMaybe_12b110(void);

asm void scePadInit(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    lui        $3, 0x45;
    sd         $18, 0x20($29);
    addiu      $2, $0, 0x1;
    sd         $31, 0x30($29);
    daddu      $18, $4, $0;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sw         $2, -0x6AF8($3);
    b          L0012AFDC;
    lui       $17, 0x49;
    nop;
  L0012AFB8:
    addiu      $3, $0, -0x1;
    nop;
  L0012AFC0:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L0012AFC0;
    nop;
  L0012AFDC:
    addiu      $16, $17, -0x1300;
    lui        $5, (0x80000100 >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x80000100 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    lw         $3, 0x24($16);
    beqz       $3, L0012AFB8;
    lui       $2, 0x1;
    daddu      $17, $16, $0;
    b          L0012B034;
    addiu     $16, $16, 0x28;
    nop;
  L0012B010:
    addiu      $3, $0, -0x1;
    nop;
  L0012B018:
    addiu      $2, $2, -0x1;
    nop;
    nop;
    nop;
    nop;
    bne        $2, $3, L0012B018;
    nop;
  L0012B034:
    lui        $5, (0x80000101 >> 16);
    daddu      $4, $16, $0;
    ori        $5, $5, (0x80000101 & 0xFFFF);
    jal        sceSifBindRpc;
    daddu     $6, $0, $0;
    lw         $3, 0x4C($17);
    beqz       $3, L0012B010;
    lui       $2, 0x1;
    jal        scePadGetModVersion;
    nop;
    daddu      $17, $2, $0;
    addiu      $2, $0, 0x4;
    sra        $16, $17, 8;
    beq        $16, $2, L0012B0A8;
    lui       $2, 0x45;
    lw         $3, -0x6AF4($2);
    beqz       $3, L0012B0A0;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7C80;
    lui        $4, 0x45;
    daddu      $7, $16, $0;
    addiu      $4, $4, 0x7CA8;
    andi       $8, $17, 0xFF;
    addiu      $5, $0, 0x4;
    jal        scePrintf_119288;
    daddu     $6, $0, $0;
  L0012B0A0:
    b          L0012B0B0;
    daddu     $2, $0, $0;
  L0012B0A8:
    jal        PadInitAfterBindMaybe_12b110;
    daddu     $4, $18, $0;
  L0012B0B0:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
