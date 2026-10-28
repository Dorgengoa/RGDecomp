#include "types.h"

extern void DecodeVarUInt_100ed0(void);

asm void EhSkipHeaderVarUInts_102640(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $31, 0x10($29);
    addiu      $5, $29, 0x2C;
    sq         $16, 0x0($29);
    lb         $2, 0x0($4);
    andi       $16, $2, 0x40;
    jal        DecodeVarUInt_100ed0;
    addiu     $4, $4, 0x1;
    daddu      $4, $2, $0;
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $29, 0x2C;
    beql       $16, $0, L00102684;
    ld        $31, 0x10($29);
    daddu      $4, $2, $0;
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $29, 0x2C;
    ld         $31, 0x10($29);
  L00102684:
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

