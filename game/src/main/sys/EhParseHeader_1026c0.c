#include "types.h"

extern void DecodeVarUInt_100ed0(void);

asm void EhParseHeader_1026c0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $4, $0;
    lw         $3, 0x4($5);
    lb         $2, 0x0($3);
    addiu      $5, $17, 0x220;
    andi       $16, $2, 0x40;
    andi       $2, $2, 0x20;
    sw         $2, 0x230($4);
    lb         $2, 0x0($3);
    andi       $2, $2, 0x10;
    sw         $2, 0x22C($4);
    lb         $2, 0x0($3);
    andi       $2, $2, 0xF;
    sw         $2, 0x228($4);
    jal        DecodeVarUInt_100ed0;
    addiu     $4, $3, 0x1;
    daddu      $4, $2, $0;
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $17, 0x224;
    lw         $3, 0x230($17);
    beqz       $3, L00102738;
    daddu     $4, $2, $0;
    lq         $3, 0x200($17);
    dsll32     $3, $3, 0;
    dsra32     $3, $3, 0;
    b          L00102740;
    sw        $3, 0x18($17);
  L00102738:
    lw         $3, 0x14($17);
    sw         $3, 0x18($17);
  L00102740:
    beql       $16, $0, L00102750;
    sw        $0, 0x234($17);
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $17, 0x234;
  L00102750:
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}

