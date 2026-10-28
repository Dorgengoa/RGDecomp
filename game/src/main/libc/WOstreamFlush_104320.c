#include "types.h"

extern void WOstreamSentryCtor_106510(void);
extern void ThrowException_1025c0(void);
extern void EhEndCatch_101010(void);
extern void strlen(void);
extern void OperatorNewArray_100900(void);
extern void SharedArrayPtrCtor_102b30(void);
extern void strcpy(void);
extern void WOstreamFlush_104320(void);

asm void WOstreamFlush_104320(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $31, 0x40($29);
    sq         $30, 0x30($29);
    sq         $18, 0x20($29);
    addu       $30, $29, $0;
    sq         $17, 0x10($29);
    daddu      $17, $4, $0;
    sq         $16, 0x0($29);
    addiu      $4, $30, 0x78;
    jal        WOstreamSentryCtor_106510;
    daddu     $5, $17, $0;
    addiu      $2, $0, 0x1;
    sb         $2, 0x79($30);
    lw         $2, 0x0($17);
    lw         $4, 0x20($2);
    beql       $4, $0, L0010447C;
    lw        $4, 0x7C($30);
    sw         $29, 0x64($30);
    daddu      $16, $0, $0;
    lw         $25, 0x0($4);
    lw         $25, 0x18($25);
    jalr $31, $25;
    nop;
    addiu      $3, $0, -0x1;
    bne        $2, $3, L001043D4;
    nop;
    b          L001043D4;
    daddiu    $16, $0, 0x1;
    lw         $3, 0x0($17);
    lbu        $2, 0x3A($3);
    ori        $2, $2, 0x1;
    sb         $2, 0x3A($3);
    lw         $2, 0x0($17);
    lbu        $2, 0x3B($2);
    andi       $2, $2, 0x1;
    beql       $2, $0, L001043C8;
    addiu     $4, $30, 0x50;
    daddu      $4, $0, $0;
    daddu      $5, $0, $0;
    jal        ThrowException_1025c0;
    daddu     $6, $0, $0;
    addiu      $4, $30, 0x50;
  L001043C8:
    jal        EhEndCatch_101010;
    nop;
    lw         $29, 0x64($30);
  L001043D4:
    beqz       $16, L00104478;
    nop;
    lw         $4, 0x0($17);
    lbu        $2, 0x3A($4);
    ori        $2, $2, 0x1;
    sb         $2, 0x3A($4);
    lw         $2, 0x20($4);
    bnel       $2, $0, L00104408;
    lbu       $3, 0x3B($4);
    lbu        $2, 0x3A($4);
    ori        $2, $2, 0x1;
    sb         $2, 0x3A($4);
    lbu        $3, 0x3B($4);
  L00104408:
    lbu        $2, 0x3A($4);
    and        $2, $2, $3;
    andi       $2, $2, 0xFF;
    beqz       $2, L00104478;
    nop;
    lui        $2, 0x47;
    lui        $4, 0x45;
    addiu      $2, $2, -0x250;
    addiu      $18, $30, 0x68;
    sw         $2, 0x68($30);
    addiu      $4, $4, 0x56F0;
    jal        strlen;
    addiu     $16, $30, 0x6C;
    jal        OperatorNewArray_100900;
    addiu     $4, $2, 0x1;
    daddu      $5, $2, $0;
    jal        SharedArrayPtrCtor_102b30;
    daddu     $4, $16, $0;
    lw         $4, 0x0($16);
    lui        $5, 0x45;
    jal        strcpy;
    addiu     $5, $5, 0x56F0;
    lui        $4, 0x45;
    lui        $6, 0x10;
    daddu      $5, $18, $0;
    addiu      $4, $4, 0x5A60;
    jal        ThrowException_1025c0;
    addiu     $6, $6, 0x28F0;
  L00104478:
    lw         $4, 0x7C($30);
  L0010447C:
    lw         $3, 0x0($4);
    lbu        $2, 0x3A($3);
    andi       $2, $2, 0x5;
    andi       $2, $2, 0xFF;
    bnel       $2, $0, L001044C0;
    daddu     $2, $17, $0;
    lhu        $2, 0x38($3);
    andi       $2, $2, 0x2000;
    andi       $2, $2, 0xFFFF;
    beqz       $2, L001044BC;
    nop;
    lbu        $2, 0x79($30);
    bnez       $2, L001044BC;
    nop;
    jal        WOstreamFlush_104320;
    nop;
  L001044BC:
    daddu      $2, $17, $0;
  L001044C0:
    addu       $29, $30, $0;
    ld         $31, 0x40($29);
    lq         $30, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

