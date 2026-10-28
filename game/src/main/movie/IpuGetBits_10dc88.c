#include "types.h"

extern void IpuSyncIfBusy_10de98(void);
extern void IpuWaitCmd_10db08(void);

asm void IpuGetBits_10dc88(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x0($29);
    sd         $17, 0x10($29);
    daddu      $16, $4, $0;
    sd         $31, 0x20($29);
    jal        IpuSyncIfBusy_10de98;
    daddu     $17, $5, $0;
    lw         $2, 0x828($16);
    bnez       $2, L0010DCC0;
    lui       $2, (0x10002000 >> 16);
    lw         $2, 0x84C($16);
    slt        $2, $2, $17;
    beqz       $2, L0010DCE8;
    lui       $2, (0x10002000 >> 16);
  L0010DCC0:
    lui        $3, (0x40000000 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    daddu      $4, $16, $0;
    sw         $3, 0x0($2);
    sw         $0, 0x828($16);
    jal        IpuWaitCmd_10db08;
    sw        $3, 0x82C($16);
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    sw         $2, 0x848($16);
  L0010DCE8:
    addiu      $4, $0, 0x20;
    lui        $8, (0x40000000 >> 16);
    lui        $3, (0x10002000 >> 16);
    or         $5, $17, $8;
    sw         $4, 0x84C($16);
    lui        $2, (0xF0000000 >> 16);
    lw         $6, 0x848($16);
    ori        $3, $3, (0x10002000 & 0xFFFF);
    and        $7, $5, $2;
    sw         $5, 0x0($3);
    subu       $4, $4, $17;
    sw         $7, 0x82C($16);
    lui        $2, (0x20000000 >> 16);
    beq        $7, $2, L0010DD38;
    srlv      $17, $6, $4;
    lui        $2, (0x30000000 >> 16);
    beql       $7, $2, L0010DD44;
    sw        $0, 0x828($16);
    bne        $7, $8, L0010DD40;
    addiu     $2, $0, 0x1;
  L0010DD38:
    b          L0010DD44;
    sw        $0, 0x828($16);
  L0010DD40:
    sw         $2, 0x828($16);
  L0010DD44:
    jal        IpuWaitCmd_10db08;
    daddu     $4, $16, $0;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    ld         $31, 0x20($29);
    sw         $2, 0x848($16);
    daddu      $2, $17, $0;
    ld         $16, 0x0($29);
    ld         $17, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

