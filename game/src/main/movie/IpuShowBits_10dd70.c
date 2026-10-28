#include "types.h"

extern void IpuSyncIfBusy_10de98(void);
extern void IpuWaitCmd_10db08(void);

asm void IpuShowBits_10dd70(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    daddu      $16, $4, $0;
    lw         $2, 0x828($16);
    bnez       $2, L0010DDA0;
    daddu     $17, $5, $0;
    lw         $2, 0x84C($16);
    slt        $2, $2, $17;
    beql       $2, $0, L0010DDE0;
    lw        $3, 0x848($16);
  L0010DDA0:
    jal        IpuSyncIfBusy_10de98;
    daddu     $4, $16, $0;
    lui        $2, (0x10002000 >> 16);
    lui        $3, (0x40000000 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    daddu      $4, $16, $0;
    sw         $3, 0x0($2);
    sw         $0, 0x828($16);
    jal        IpuWaitCmd_10db08;
    sw        $3, 0x82C($16);
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    addiu      $3, $0, 0x20;
    sw         $2, 0x848($16);
    sw         $3, 0x84C($16);
    lw         $3, 0x848($16);
  L0010DDE0:
    negu       $2, $17;
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    srlv       $2, $3, $2;
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

