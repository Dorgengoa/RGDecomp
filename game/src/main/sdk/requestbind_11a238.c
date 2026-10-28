#include "types.h"

extern void _sceRpcGetFPacket(void);
extern void _search_svdata(void);
extern void isceSifSendCmd(void);
extern void iSetTimerAlarm_122420(void);

asm void requestbind_11a238(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    daddu      $17, $5, $0;
    daddu      $16, $4, $0;
    sd         $18, 0x20($29);
    sd         $31, 0x30($29);
    jal        _sceRpcGetFPacket;
    daddu     $4, $17, $0;
    daddu      $18, $2, $0;
    lw         $4, 0x1C($16);
    lw         $3, 0x14($16);
    lui        $2, (0x80000009 >> 16);
    ori        $2, $2, (0x80000009 & 0xFFFF);
    sw         $4, 0x1C($18);
    sw         $3, 0x14($18);
    daddu      $5, $17, $0;
    sw         $2, 0x20($18);
    jal        _search_svdata;
    lw        $4, 0x20($16);
    bnel       $2, $0, L0011A29C;
    sw        $2, 0x24($18);
    sw         $0, 0x24($18);
    b          L0011A2A4;
    sw        $0, 0x28($18);
  L0011A29C:
    lw         $2, 0x8($2);
    sw         $2, 0x28($18);
  L0011A2A4:
    lui        $4, (0x80000008 >> 16);
    daddu      $5, $18, $0;
    ori        $4, $4, (0x80000008 & 0xFFFF);
    addiu      $6, $0, 0x40;
    daddu      $7, $0, $0;
    daddu      $8, $0, $0;
    jal        isceSifSendCmd;
    daddu     $9, $0, $0;
    bnez       $2, L0011A2F0;
    ld        $31, 0x30($29);
    daddu      $6, $18, $0;
    lui        $5, 0x12;
    addiu      $5, $5, -0x5E08;
    ld         $18, 0x20($29);
    addiu      $4, $0, 0x800;
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    j          iSetTimerAlarm_122420;
    addiu     $29, $29, 0x40;
  L0011A2F0:
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
