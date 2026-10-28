#include "types.h"

extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void CreateSema(void);
extern void SifCallRpcRetry_11ad90(void);
extern void DeleteSema(void);
extern void FileIoUnlock_11b330(void);
extern void WaitSema(void);

asm void FileIoPathCmdRpc_11ca10(void)
{
    .set noreorder;
    addiu      $29, $29, -0xD0;
    sd         $22, 0xA0($29);
    sd         $17, 0x50($29);
    daddu      $22, $5, $0;
    daddu      $17, $4, $0;
    sd         $23, 0xB0($29);
    sd         $19, 0x70($29);
    daddu      $4, $22, $0;
    sd         $31, 0xC0($29);
    lui        $23, 0x49;
    sd         $21, 0x90($29);
    addiu      $19, $23, -0x7C40;
    sd         $20, 0x80($29);
    sd         $18, 0x60($29);
    jal        FileIoLock_11b300;
    sd        $16, 0x40($29);
    lui        $2, 0x44;
    lw         $3, 0x629C($2);
    bnel       $3, $0, L0011CA6C;
    lbu       $2, 0x0($17);
    jal        SceFsInit_11b428;
    nop;
    lbu        $2, 0x0($17);
  L0011CA6C:
    daddu      $16, $0, $0;
    sll        $3, $2, 24;
    beqz       $3, L0011CABC;
    sb        $2, 0xC($19);
    lui        $5, 0x45;
    addiu      $18, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
    addiu      $16, $16, 0x1;
  L0011CA90:
    slti       $2, $16, 0x400;
    beqz       $2, L0011CACC;
    addu      $2, $17, $16;
    addu       $4, $19, $16;
    lbu        $3, 0x0($2);
    sb         $3, 0xC($4);
    sll        $3, $3, 24;
    bnel       $3, $0, L0011CA90;
    addiu     $16, $16, 0x1;
    b          L0011CAD0;
    addiu     $2, $0, 0x400;
  L0011CABC:
    lui        $5, 0x45;
    addiu      $18, $29, 0x30;
    lui        $21, 0x49;
    lui        $20, 0x49;
  L0011CACC:
    addiu      $2, $0, 0x400;
  L0011CAD0:
    bne        $16, $2, L0011CAE0;
    addiu     $2, $5, 0x6A88;
    sb         $0, 0x40B($19);
    addiu      $16, $0, 0x3FF;
  L0011CAE0:
    addiu      $3, $0, 0x1;
    sw         $3, 0x14($29);
    addiu      $4, $29, 0x10;
    sw         $2, 0x24($29);
    addiu      $20, $20, -0x7000;
    jal        CreateSema;
    sw        $0, 0x18($29);
    daddu      $17, $2, $0;
    sw         $18, 0x4($19);
    addiu      $2, $0, 0x4;
    sw         $17, 0x0($19);
    sw         $2, 0x8($19);
    addiu      $4, $21, -0x6540;
    daddu      $5, $22, $0;
    addiu      $7, $23, -0x7C40;
    addiu      $8, $16, 0xD;
    daddu      $6, $0, $0;
    sw         $0, 0x0($29);
    daddu      $9, $20, $0;
    sw         $0, 0x8($29);
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011CB5C;
    lui       $2, (0x20000000 >> 16);
    jal        DeleteSema;
    daddu     $4, $17, $0;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011CB94;
    addiu     $2, $0, -0xB;
  L0011CB5C:
    or         $2, $20, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    bnez       $16, L0011CB80;
    nop;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    b          L0011CB94;
    addiu     $2, $0, -0xB;
  L0011CB80:
    jal        WaitSema;
    daddu     $4, $17, $0;
    jal        DeleteSema;
    daddu     $4, $17, $0;
    lw         $2, 0x30($29);
  L0011CB94:
    ld         $31, 0xC0($29);
    ld         $23, 0xB0($29);
    ld         $22, 0xA0($29);
    ld         $21, 0x90($29);
    ld         $20, 0x80($29);
    ld         $19, 0x70($29);
    ld         $18, 0x60($29);
    ld         $17, 0x50($29);
    ld         $16, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0xD0;
}
