#include "types.h"

extern void CreateThread(void);
extern void StartThread_1176e0(void);
extern void ChangeThreadPriority(void);

asm void sceCdInitEeCB_1293b0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    daddu      $7, $4, $0;
    sd         $17, 0x10($29);
    daddu      $8, $5, $0;
    lui        $17, 0x44;
    sd         $16, 0x0($29);
    lw         $4, 0x7954($17);
    addiu      $16, $0, 0x1;
    bnez       $4, L00129428;
    sd        $31, 0x20($29);
    lui        $2, 0x49;
    lui        $3, 0x13;
    lui        $5, 0x45;
    addiu      $2, $2, -0x15A8;
    addiu      $3, $3, -0x6D20;
    addiu      $5, $5, 0x7A00;
    sw         $6, 0xC($2);
    daddu      $4, $2, $0;
    sw         $3, 0x4($2);
    sw         $8, 0x8($2);
    sw         $7, 0x14($2);
    sw         $5, 0x20($2);
    jal        CreateThread;
    sw        $0, 0x10($2);
    daddu      $5, $0, $0;
    sw         $2, 0x7954($17);
    jal        StartThread_1176e0;
    daddu     $4, $2, $0;
    b          L00129438;
    daddu     $2, $16, $0;
  L00129428:
    daddu      $5, $7, $0;
    jal        ChangeThreadPriority;
    daddu     $16, $0, $0;
    daddu      $2, $16, $0;
  L00129438:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
