#include "types.h"

extern void _sceRpcGetFPacket2(void);
extern void _sceRpcGetFPacket(void);
extern void isceSifSendCmd(void);
extern void iSetTimerAlarm_122420(void);

asm void requestrdata_119f70(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    daddu      $17, $4, $0;
    sd         $31, 0x20($29);
    sd         $16, 0x0($29);
    daddu      $4, $5, $0;
    lw         $5, 0x10($17);
    andi       $2, $5, 0x4;
    beqz       $2, L00119FA8;
    nop;
    jal        _sceRpcGetFPacket2;
    srl       $5, $5, 16;
    b          L00119FB4;
    daddu     $16, $2, $0;
  L00119FA8:
    jal        _sceRpcGetFPacket;
    nop;
    daddu      $16, $2, $0;
  L00119FB4:
    lw         $3, 0x14($17);
    lui        $2, (0x8000000C >> 16);
    lw         $5, 0x1C($17);
    ori        $2, $2, (0x8000000C & 0xFFFF);
    sw         $3, 0x14($16);
    lui        $4, (0x80000008 >> 16);
    sw         $5, 0x1C($16);
    ori        $4, $4, (0x80000008 & 0xFFFF);
    sw         $2, 0x20($16);
    daddu      $5, $16, $0;
    addiu      $6, $0, 0x40;
    lw         $2, 0x20($17);
    sw         $2, 0x24($16);
    lw         $3, 0x24($17);
    sw         $3, 0x28($16);
    lw         $2, 0x28($17);
    sw         $2, 0x2C($16);
    lw         $9, 0x28($17);
    lw         $7, 0x20($17);
    jal        isceSifSendCmd;
    lw        $8, 0x24($17);
    bnez       $2, L0011A030;
    ld        $31, 0x20($29);
    daddu      $6, $16, $0;
    lui        $5, 0x12;
    addiu      $5, $5, -0x60D0;
    ld         $17, 0x10($29);
    addiu      $4, $0, 0x800;
    ld         $16, 0x0($29);
    j          iSetTimerAlarm_122420;
    addiu     $29, $29, 0x30;
  L0011A030:
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
