#include "types.h"

extern void IpuSyncIfBusy_10de98(void);
extern void IpuWaitCmd_10db08(void);

asm void IpuSkipBits_10de00(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    daddu      $17, $4, $0;
    sd         $31, 0x20($29);
    jal        IpuSyncIfBusy_10de98;
    daddu     $16, $5, $0;
    lui        $4, (0x40000000 >> 16);
    lui        $2, (0x10002000 >> 16);
    or         $16, $16, $4;
    ori        $2, $2, (0x10002000 & 0xFFFF);
    sw         $16, 0x0($2);
    lui        $3, (0xF0000000 >> 16);
    and        $16, $16, $3;
    lui        $2, (0x20000000 >> 16);
    beq        $16, $2, L0010DE58;
    sw        $16, 0x82C($17);
    lui        $2, (0x30000000 >> 16);
    beql       $16, $2, L0010DE64;
    sw        $0, 0x828($17);
    bne        $16, $4, L0010DE60;
    addiu     $2, $0, 0x1;
  L0010DE58:
    b          L0010DE64;
    sw        $0, 0x828($17);
  L0010DE60:
    sw         $2, 0x828($17);
  L0010DE64:
    jal        IpuWaitCmd_10db08;
    daddu     $4, $17, $0;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    addiu      $3, $0, 0x20;
    sw         $3, 0x84C($17);
    sw         $2, 0x848($17);
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

