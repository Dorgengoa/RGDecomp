#include "types.h"

extern void Unexpected_100cb0(void);
extern void DecodeVarUInt_100ed0(void);
extern void DecodeVarInt_100f70(void);
extern void EhCatchTypeCompare_100a60(void);
extern void ThrowException_1025c0(void);
extern void EhEndCatch_101010(void);
extern void Terminate_100ce0(void);

asm void EhUnexpected_1014d0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xA0;
    sd         $31, 0x40($29);
    sq         $30, 0x30($29);
    sq         $18, 0x20($29);
    addu       $30, $29, $0;
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    lw         $16, 0x14($4);
    jal        Unexpected_100cb0;
    sw        $29, 0x64($30);
    b          L00101670;
    nop;
    addiu      $4, $16, 0x1;
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $30, 0x70;
    daddu      $4, $2, $0;
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $30, 0x74;
    daddu      $4, $2, $0;
    jal        DecodeVarInt_100f70;
    addiu     $5, $30, 0x78;
    sw         $2, 0x7C($30);
    daddu      $17, $2, $0;
    lw         $2, 0x70($30);
    lw         $18, 0x54($30);
    beqz       $2, L001015A0;
    daddu     $16, $0, $0;
  L0010153C:
    lbu        $2, 0x1($17);
    daddu      $4, $18, $0;
    lbu        $3, 0x2($17);
    addiu      $6, $30, 0x88;
    lbu        $5, 0x0($17);
    sll        $7, $2, 8;
    lbu        $2, 0x3($17);
    sll        $3, $3, 16;
    or         $5, $5, $7;
    or         $3, $3, $5;
    sll        $2, $2, 24;
    or         $5, $2, $3;
    jal        EhCatchTypeCompare_100a60;
    sw        $5, 0x98($30);
    sltu       $2, $0, $2;
    xori       $2, $2, 0x1;
    bnel       $2, $0, L0010158C;
    lw        $2, 0x70($30);
    b          L001015A4;
    addiu     $2, $0, 0x1;
  L0010158C:
    addiu      $16, $16, 0x1;
    sltu       $2, $16, $2;
    bnez       $2, L0010153C;
    addiu     $17, $17, 0x4;
    nop;
  L001015A0:
    daddu      $2, $0, $0;
  L001015A4:
    beql       $2, $0, L001015C0;
    lw        $2, 0x70($30);
    daddu      $4, $0, $0;
    daddu      $5, $0, $0;
    jal        ThrowException_1025c0;
    daddu     $6, $0, $0;
    lw         $2, 0x70($30);
  L001015C0:
    lw         $17, 0x7C($30);
    beqz       $2, L00101630;
    daddu     $16, $0, $0;
  L001015CC:
    lbu        $2, 0x1($17);
    lui        $4, 0x45;
    lbu        $3, 0x2($17);
    addiu      $4, $4, 0x5550;
    lbu        $5, 0x0($17);
    addiu      $6, $30, 0x80;
    sll        $7, $2, 8;
    lbu        $2, 0x3($17);
    sll        $3, $3, 16;
    or         $5, $5, $7;
    or         $3, $3, $5;
    sll        $2, $2, 24;
    or         $5, $2, $3;
    jal        EhCatchTypeCompare_100a60;
    sw        $5, 0x94($30);
    sltu       $2, $0, $2;
    xori       $2, $2, 0x1;
    bnel       $2, $0, L00101620;
    lw        $2, 0x70($30);
    b          L00101634;
    addiu     $2, $0, 0x1;
  L00101620:
    addiu      $16, $16, 0x1;
    sltu       $2, $16, $2;
    bnez       $2, L001015CC;
    addiu     $17, $17, 0x4;
  L00101630:
    daddu      $2, $0, $0;
  L00101634:
    beql       $2, $0, L00101664;
    addiu     $4, $30, 0x50;
    lui        $2, 0x47;
    lui        $4, 0x45;
    addiu      $2, $2, -0x270;
    lui        $6, 0x10;
    addiu      $4, $4, 0x5570;
    sw         $2, 0x9C($30);
    addiu      $5, $30, 0x9C;
    jal        ThrowException_1025c0;
    addiu     $6, $6, 0x16A0;
    addiu      $4, $30, 0x50;
  L00101664:
    jal        EhEndCatch_101010;
    nop;
    lw         $29, 0x64($30);
  L00101670:
    jal        Terminate_100ce0;
    nop;
    addu       $29, $30, $0;
    ld         $31, 0x40($29);
    lq         $30, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0xA0;
}

