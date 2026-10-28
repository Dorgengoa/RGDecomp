#include "types.h"

extern void PadSetCmdCallbackMaybe_12c510(void);
extern void sceSifCallRpc(void);
extern void sceSifRemoveCmdHandler(void);

asm void scePadEnd_12b208(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x10($29);
    sd         $31, 0x20($29);
    jal        PadSetCmdCallbackMaybe_12c510;
    daddu     $4, $0, $0;
    lui        $3, 0x49;
    addiu      $2, $0, 0xF;
    addiu      $16, $3, -0x10C0;
    lui        $4, 0x49;
    sw         $2, -0x10C0($3);
    addiu      $4, $4, -0x1300;
    sw         $0, 0x0($29);
    addiu      $5, $0, 0x1;
    daddu      $6, $0, $0;
    daddu      $7, $16, $0;
    addiu      $8, $0, 0x80;
    daddu      $9, $16, $0;
    addiu      $10, $0, 0x80;
    jal        sceSifCallRpc;
    daddu     $11, $0, $0;
    bltz       $2, L0012B288;
    daddu     $2, $0, $0;
    lui        $4, (0x80000019 >> 16);
    jal        sceSifRemoveCmdHandler;
    ori       $4, $4, (0x80000019 & 0xFFFF);
    lw         $3, 0xC($16);
    addiu      $2, $0, 0x1;
    bne        $3, $2, L0012B288;
    daddu     $2, $3, $0;
    lui        $2, 0x45;
    sw         $0, -0x6AF8($2);
    daddu      $2, $3, $0;
  L0012B288:
    ld         $31, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
