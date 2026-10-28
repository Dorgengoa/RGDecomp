#include "types.h"

extern void FileIoLock_11b300(void);
extern void SceFsInit_11b428(void);
extern void FsVersion_11b630(void);
extern void FileIoUnlock_11b330(void);
extern void FileIoCountSlots_11ac88(void);
extern void SifCallRpcRetry_11ad90(void);

asm void FileIoSetIopParamRelated_11b838(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $16, 0x10($29);
    daddu      $16, $4, $0;
    sd         $31, 0x30($29);
    sd         $17, 0x20($29);
    jal        FileIoLock_11b300;
    addiu     $4, $0, 0xFD;
    lui        $3, 0x44;
    lw         $2, 0x629C($3);
    bnez       $2, L0011B86C;
    nop;
    jal        SceFsInit_11b428;
    nop;
  L0011B86C:
    jal        FsVersion_11b630;
    nop;
    beqz       $2, L0011B890;
    nop;
    jal        FileIoUnlock_11b330;
    nop;
    lui        $2, (0xFFFEFFFC >> 16);
    b          L0011B914;
    ori       $2, $2, (0xFFFEFFFC & 0xFFFF);
  L0011B890:
    jal        FileIoCountSlots_11ac88;
    nop;
    beqz       $2, L0011B8B0;
    lui       $7, 0x49;
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011B914;
    addiu     $2, $0, -0x10;
  L0011B8B0:
    lui        $2, 0x49;
    addiu      $17, $2, -0x7000;
    lui        $4, 0x49;
    sw         $16, -0x7C40($7);
    addiu      $4, $4, -0x6540;
    addiu      $7, $7, -0x7C40;
    sw         $0, 0x0($29);
    sw         $0, 0x8($29);
    addiu      $5, $0, 0xFD;
    daddu      $6, $0, $0;
    addiu      $8, $0, 0x8;
    daddu      $9, $17, $0;
    addiu      $10, $0, 0x4;
    jal        SifCallRpcRetry_11ad90;
    daddu     $11, $0, $0;
    bgez       $2, L0011B904;
    lui       $2, (0x20000000 >> 16);
    jal        FileIoUnlock_11b330;
    nop;
    b          L0011B914;
    addiu     $2, $0, -0xB;
  L0011B904:
    or         $2, $17, $2;
    jal        FileIoUnlock_11b330;
    lw        $16, (0x20000000 & 0xFFFF)($2);
    daddu      $2, $16, $0;
  L0011B914:
    ld         $31, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
