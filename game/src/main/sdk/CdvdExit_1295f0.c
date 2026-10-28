#include "types.h"

extern void SignalSema(void);
extern void DeleteSema(void);
extern void DisableIntr_120660(void);
extern void sceSifRemoveCmdHandler(void);
extern void EnableIntr_1206b0(void);

asm void CdvdExit_1295f0(void)
{
    .set noreorder;
    lui        $2, 0x44;
    addiu      $29, $29, -0x20;
    lw         $3, 0x7954($2);
    sd         $31, 0x10($29);
    beqz       $3, L00129628;
    sd        $16, 0x0($29);
    lui        $3, 0x44;
    addiu      $2, $0, -0x1;
    sw         $2, 0x79A0($3);
    lui        $16, 0x44;
    jal        SignalSema;
    lw        $4, 0x7960($16);
    b          L00129630;
    lui       $2, 0x44;
  L00129628:
    lui        $16, 0x44;
    lui        $2, 0x44;
  L00129630:
    jal        DeleteSema;
    lw        $4, 0x7968($2);
    lui        $3, 0x44;
    jal        DeleteSema;
    lw        $4, 0x796C($3);
    lui        $3, 0x44;
    jal        DeleteSema;
    lw        $4, 0x7970($3);
    jal        DeleteSema;
    lw        $4, 0x7960($16);
    jal        DisableIntr_120660;
    nop;
    lui        $4, (0x80000012 >> 16);
    daddu      $16, $2, $0;
    jal        sceSifRemoveCmdHandler;
    ori       $4, $4, (0x80000012 & 0xFFFF);
    beqz       $16, L00129684;
    ld        $31, 0x10($29);
    ld         $16, 0x0($29);
    j          EnableIntr_1206b0;
    addiu     $29, $29, 0x20;
  L00129684:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
