#include "types.h"

extern void IpuSyncIfBusy_10ffc8(void);
extern void IpuSkipBitsThunk2_10de00(void);

asm void IpuByteAlign_110168(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        IpuSyncIfBusy_10ffc8;
    daddu     $16, $4, $0;
    lui        $2, (0x10002020 >> 16);
    ori        $2, $2, (0x10002020 & 0xFFFF);
    lw         $3, 0x0($2);
    andi       $3, $3, 0x7;
    negu       $3, $3;
    andi       $5, $3, 0x7;
    beqz       $5, L001101AC;
    ld        $31, 0x10($29);
    daddu      $4, $16, $0;
    ld         $16, 0x0($29);
    j          IpuSkipBitsThunk2_10de00;
    addiu     $29, $29, 0x20;
  L001101AC:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
