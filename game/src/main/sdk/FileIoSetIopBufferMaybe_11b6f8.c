#include "types.h"

extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void FsVersion_11b630(void);
extern void FileIoUnlock_11b330(void);
extern void FileIoCountSlots_11ac88(void);
extern void SifCallRpcRetry_11ad90(void);

asm void FileIoSetIopBufferMaybe_11b6f8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $16, 0x10($29);
    sd         $17, 0x20($29);
    daddu      $16, $4, $0;
    sd         $31, 0x40($29);
    daddu      $17, $5, $0;
    sd         $18, 0x30($29);
    jal        FileIoLock_11b300;
    addiu     $4, $0, 0xFE;
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    bnez       $2, L0011B734;
    nop;
    jal        SceFsInit_11b428;
    nop;
  L0011B734:
    jal        FsVersion_11b630;
    nop;
    beqz       $2, L0011B758;
    nop;
    jal        FileIoUnlock_11b330;
    nop;
    lui        $2, (0xFFFEFFFC >> 16);
    b          L0011B820;
    ori       $2, $2, (0xFFFEFFFC & 0xFFFF);
  L0011B758:
    jal        FileIoCountSlots_11ac88;
    nop;
    beqz       $2, L0011B778;
    andi      $2, $16, 0x3FFF;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011B820;
    addiu     $2, $0, -0x10;
  L0011B778:
    bnez       $2, L0011B7A8;
    nop;
    beqz       $16, L0011B7A8;
    lui       $2, (0xFFFFF >> 16);
    ori        $2, $2, (0xFFFFF & 0xFFFF);
    sltu       $2, $2, $16;
    bnez       $2, L0011B7A8;
    nop;
    beqz       $17, L0011B7A8;
    sltiu     $2, $17, 0x21;
    bnez       $2, L0011B7B8;
    lui       $3, 0x49;
  L0011B7A8:
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011B820;
    addiu     $2, $0, -0x16;
  L0011B7B8:
    lui        $2, 0x49;
    addiu      $7, $3, -0x7C40;
    sw         $16, -0x7C40($3);
    sw         $17, 0x4($7);
    addiu      $18, $2, -0x7000;
    lui        $4, 0x49;
    sw         $0, 0x0($29);
    addiu      $4, $4, -0x6540;
    sw         $0, 0x8($29);
    addiu      $5, $0, 0xFE;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x8;
    daddu      $9, $18, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011B810;
    lui       $2, (0x20000000 >> 16);
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011B820;
    addiu     $2, $0, -0xB;
  L0011B810:
    or         $2, $18, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L0011B820:
    ld         $31, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
