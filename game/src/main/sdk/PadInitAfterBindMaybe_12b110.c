#include "types.h"

extern void sceSifCallRpc(void);
extern void DisableIntr_120660(void);
extern void sceSifAddCmdHandler(void);
extern void EnableIntr_1206b0(void);

asm void PadInitAfterBindMaybe_12b110(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    lui        $2, 0x49;
    addiu      $2, $2, -0x12B0;
    sd         $31, 0x30($29);
    sd         $17, 0x20($29);
    lui        $5, 0x49;
    sd         $16, 0x10($29);
    addiu      $2, $2, 0x84;
    addiu      $3, $0, 0x3;
    nop;
  L0012B138:
    sw         $0, -0x74($2);
    addiu      $3, $3, -0x1;
    sw         $0, -0x6C($2);
    sw         $0, -0x70($2);
    sw         $0, -0x4($2);
    sw         $0, 0x4($2);
    sw         $0, 0x0($2);
    bgez       $3, L0012B138;
    addiu     $2, $2, 0x1C;
    lui        $2, 0x45;
    addiu      $17, $5, -0x10C0;
    lw         $3, -0x6AEC($2);
    lui        $4, 0x49;
    addiu      $2, $0, 0x10;
    sw         $0, 0x10($17);
    sw         $2, -0x10C0($5);
    addiu      $4, $4, -0x1300;
    sw         $3, 0x14($17);
    addiu      $5, $0, 0x1;
    daddu      $6, $0, $0;
    daddu      $7, $17, $0;
    sw         $0, 0x0($29);
    addiu      $8, $0, 0x80;
    daddu      $9, $17, $0;
    addiu      $10, $0, 0x80;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bgez       $2, L0012B1B4;
    lui       $2, 0x45;
    b          L0012B1F0;
    daddu     $2, $0, $0;
  L0012B1B4:
    jal        DisableIntr_120660;
    sw        $0, -0x6AF0($2);
    lui        $5, 0x13;
    lui        $4, (0x80000019 >> 16);
    daddu      $16, $2, $0;
    addiu      $5, $5, -0x4F38;
    ori        $4, $4, (0x80000019 & 0xFFFF);
    jal        sceSifAddCmdHandler;
    daddu     $6, $0, $0;
    addiu      $2, $0, 0x1;
    bnel       $16, $2, L0012B1F0;
    lw        $2, 0xC($17);
    jal        EnableIntr_1206b0;
    nop;
    lw         $2, 0xC($17);
  L0012B1F0:
    ld         $31, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
