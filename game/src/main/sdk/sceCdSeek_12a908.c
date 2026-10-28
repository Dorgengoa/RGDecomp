#include "types.h"

extern void sceCdNcmdDiskReady_129c58(void);
extern void CdCheckNCmd_129b00(void);
extern void sceSifWriteBackDCache(void);
extern void sceSifCallRpc(void);
extern void SignalSema(void);

asm void sceCdSeek_12a908(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $16, 0x10($29);
    sd         $18, 0x30($29);
    daddu      $16, $4, $0;
    sd         $17, 0x20($29);
    sd         $31, 0x40($29);
    jal        sceCdNcmdDiskReady_129c58;
    lui       $17, 0x44;
    addiu      $3, $0, 0x6;
    beq        $2, $3, L0012A9B8;
    addiu     $18, $17, 0x7A40;
    jal        CdCheckNCmd_129b00;
    addiu     $4, $0, 0x9;
    beqz       $2, L0012A9B8;
    daddu     $4, $18, $0;
    sw         $16, 0x7A40($17);
    addiu      $5, $0, 0x4;
    jal        sceSifWriteBackDCache;
    lui       $16, 0x44;
    lui        $17, 0x44;
    addiu      $5, $16, 0x79A0;
    addiu      $2, $0, 0x4;
    sw         $2, 0x79A0($16);
    addiu      $3, $0, 0x1;
    lui        $4, 0x45;
    lui        $11, 0x13;
    sw         $5, 0x0($29);
    addiu      $4, $4, -0x74F0;
    sw         $3, 0x7974($17);
    daddu      $7, $18, $0;
    addiu      $11, $11, -0x6DC0;
    addiu      $5, $0, 0x5;
    addiu      $6, $0, 0x1;
    addiu      $8, $0, 0x4;
    daddu      $9, $0, $0;
    jal        sceSifCallRpc;
    daddu     $10, $0, $0;
    bgezl      $2, L0012A9BC;
    addiu     $2, $0, 0x1;
    sw         $0, 0x79A0($16);
    lui        $2, 0x44;
    sw         $0, 0x7974($17);
    jal        SignalSema;
    lw        $4, 0x7968($2);
  L0012A9B8:
    daddu      $2, $0, $0;
  L0012A9BC:
    ld         $31, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
