#include "types.h"

extern void scePrintf_119288(void);
extern void DelayThread_117618(void);
extern void sceSifCheckStatRpc(void);

asm void sceCdSyncS_129d90(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $31, 0x10($29);
    bnez       $4, L00129DE0;
    sd        $16, 0x0($29);
    lui        $2, 0x44;
    lw         $3, 0x7950($2);
    blez       $3, L00129DB8;
    lui       $4, 0x45;
    jal        scePrintf_119288;
    addiu     $4, $4, 0x7B20;
  L00129DB8:
    b          L00129DC8;
    lui       $16, 0x45;
  L00129DC0:
    jal        DelayThread_117618;
    addiu     $4, $0, 0xFA0;
  L00129DC8:
    jal        sceSifCheckStatRpc;
    addiu     $4, $16, -0x6B40;
    bnez       $2, L00129DC0;
    daddu     $2, $0, $0;
    b          L00129DF0;
    ld        $31, 0x10($29);
  L00129DE0:
    lui        $4, 0x45;
    jal        sceSifCheckStatRpc;
    addiu     $4, $4, -0x6B40;
    ld         $31, 0x10($29);
  L00129DF0:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
