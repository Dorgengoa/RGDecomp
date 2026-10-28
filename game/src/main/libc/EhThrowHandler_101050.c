#include "types.h"

extern void EhFindCallSite_102380(void);
extern void Terminate_100ce0(void);
extern void EhParseHeader_1026c0(void);
extern void EhGetCatchRecord_101700(void);
extern void EhDispatchHandler_1011d0(void);
extern void DecodeVarUInt_100ed0(void);
extern void DecodeVarInt_100f70(void);
extern void EhUnwindActions_101860(void);
extern void EhRestoreContextAndJump_102550(void);

asm void EhThrowHandler_101050(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $4, $0;
    lw         $4, 0x10($4);
    jal        EhFindCallSite_102380;
    addiu     $5, $29, 0x30;
    lw         $2, 0x34($29);
    bnel       $2, $0, L00101088;
    daddu     $4, $17, $0;
    jal        Terminate_100ce0;
    nop;
    daddu      $4, $17, $0;
  L00101088:
    jal        EhParseHeader_1026c0;
    addiu     $5, $29, 0x30;
    lw         $2, 0x0($17);
    bnel       $2, $0, L001010AC;
    sw        $0, 0xC($17);
    daddu      $4, $17, $0;
    jal        EhGetCatchRecord_101700;
    addiu     $5, $29, 0x30;
    sw         $2, 0xC($17);
  L001010AC:
    daddu      $4, $17, $0;
    addiu      $5, $29, 0x30;
    jal        EhDispatchHandler_1011d0;
    addiu     $6, $29, 0x48;
    lbu        $6, 0x2($2);
    daddu      $16, $2, $0;
    lbu        $3, 0x3($2);
    addiu      $4, $16, 0x5;
    lbu        $5, 0x1($2);
    sll        $6, $6, 8;
    sll        $3, $3, 16;
    lbu        $2, 0x4($2);
    or         $5, $5, $6;
    or         $3, $3, $5;
    sll        $2, $2, 24;
    or         $2, $2, $3;
    beqz       $2, L001010FC;
    sw        $2, 0x50($29);
    b          L00101104;
    sw        $2, 0x50($29);
  L001010FC:
    daddu      $2, $0, $0;
    sw         $2, 0x50($29);
  L00101104:
    jal        DecodeVarUInt_100ed0;
    addiu     $5, $29, 0x54;
    daddu      $4, $2, $0;
    jal        DecodeVarInt_100f70;
    addiu     $5, $29, 0x58;
    daddu      $6, $16, $0;
    daddu      $4, $17, $0;
    jal        EhUnwindActions_101860;
    addiu     $5, $29, 0x30;
    lw         $5, 0x58($29);
    addiu      $2, $0, 0x2A;
    lw         $4, 0x18($17);
    ld         $6, 0x48($29);
    lw         $3, 0x4($17);
    addu       $4, $4, $5;
    sw         $3, 0x0($4);
    lw         $3, 0x0($17);
    sw         $3, 0x4($4);
    lw         $3, 0x8($17);
    sw         $3, 0x8($4);
    lw         $3, 0x0($17);
    lb         $3, 0x0($3);
    bnel       $3, $2, L00101188;
    lw        $2, 0x4($17);
    addiu      $2, $4, 0x10;
    sw         $2, 0xC($4);
    lw         $2, 0x4($17);
    lw         $2, 0x0($2);
    daddu      $2, $2, $6;
    dsll32     $2, $2, 0;
    dsra32     $2, $2, 0;
    b          L00101198;
    sw        $2, 0x10($4);
  L00101188:
    dsll32     $3, $6, 0;
    dsra32     $3, $3, 0;
    addu       $2, $2, $3;
    sw         $2, 0xC($4);
  L00101198:
    lw         $3, 0x30($29);
    daddu      $4, $17, $0;
    lw         $2, 0x54($29);
    addiu      $5, $29, 0x30;
    jal        EhRestoreContextAndJump_102550;
    addu      $6, $3, $2;
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}

