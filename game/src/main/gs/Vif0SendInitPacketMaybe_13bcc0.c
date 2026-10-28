#include "types.h"

extern void sceDmaGetChan(void);
extern void sceDmaSend_10a040(void);
extern void sceDmaSync_10a2e0(void);

asm void Vif0SendInitPacketMaybe_13bcc0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $4, $0, $0;
    sd         $31, 0x10($29);
    jal        sceDmaGetChan;
    sq        $16, 0x0($29);
    lbu        $7, 0x0($2);
    addiu      $3, $0, -0x41;
    daddu      $16, $2, $0;
    lui        $5, 0x44;
    daddiu     $6, $0, 0x40;
    daddu      $4, $16, $0;
    and        $3, $7, $3;
    addiu      $5, $5, 0x5810;
    or         $3, $3, $6;
    jal        sceDmaSend_10a040;
    sb        $3, 0x0($2);
    daddu      $4, $16, $0;
    daddu      $5, $0, $0;
    jal        sceDmaSync_10a2e0;
    daddu     $6, $0, $0;
    ld         $31, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

