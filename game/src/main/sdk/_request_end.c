#include "types.h"

extern void iSignalSema(void);
extern void _sceRpcFreePacket(void);

asm void _request_end(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    lui        $2, (0x8000000A >> 16);
    sd         $18, 0x20($29);
    ori        $2, $2, (0x8000000A & 0xFFFF);
    sd         $31, 0x30($29);
    daddu      $18, $4, $0;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    lw         $3, 0x20($18);
    beq        $3, $2, L00119EAC;
    sltu      $2, $2, $3;
    bnez       $2, L00119EF4;
    lw        $17, 0x1C($18);
    lui        $2, (0x80000009 >> 16);
    ori        $2, $2, (0x80000009 & 0xFFFF);
    beq        $3, $2, L00119EE4;
    nop;
    b          L00119EF8;
    lw        $4, 0x8($17);
  L00119EAC:
    lw         $17, 0x1C($18);
    lw         $2, 0x1C($17);
    beql       $2, $0, L00119EF8;
    lw        $4, 0x8($17);
    lw         $2, 0x18($17);
    daddu      $16, $28, $0;
    daddu      $28, $2, $0;
    lw         $2, 0x1C($17);
    jalr $31, $2;
    lw        $4, 0x20($17);
    daddu      $3, $28, $0;
    daddu      $28, $16, $0;
    b          L00119EF4;
    lw        $17, 0x1C($18);
  L00119EE4:
    lw         $2, 0x24($18);
    sw         $2, 0x24($17);
    lw         $3, 0x28($18);
    sw         $3, 0x14($17);
  L00119EF4:
    lw         $4, 0x8($17);
  L00119EF8:
    bltz       $4, L00119F08;
    nop;
    jal        iSignalSema;
    nop;
  L00119F08:
    jal        _sceRpcFreePacket;
    lw        $4, 0x0($17);
    sw         $0, 0x0($17);
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

