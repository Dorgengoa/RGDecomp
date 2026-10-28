#include "types.h"

extern void GsTestSetAlphaTest_157100(void);
extern void GsTestSetDate_156ff0(void);
extern void GsTestSetZTest_156f40(void);
extern void GsZbufSetZMask_156ee0(void);
extern void GsFbaSetEnable_156e80(void);

asm void GsPktSetDefaultState_13fa80(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    andi       $2, $0, 0x1;
    sd         $31, 0x10($29);
    sll        $3, $2, 6;
    sq         $16, 0x0($29);
    addiu      $2, $0, -0x41;
    lbu        $6, 0x70($4);
    daddu      $16, $4, $0;
    addiu      $5, $0, 0x1;
    and        $2, $6, $2;
    or         $2, $2, $3;
    sb         $2, 0x70($4);
    jal        GsTestSetAlphaTest_157100;
    addiu     $4, $16, 0x10;
    addiu      $4, $16, 0x10;
    jal        GsTestSetDate_156ff0;
    daddu     $5, $0, $0;
    addiu      $4, $16, 0x10;
    jal        GsTestSetZTest_156f40;
    addiu     $5, $0, 0x2;
    addiu      $5, $0, 0x1;
    addiu      $4, $16, 0x10;
    jal        GsZbufSetZMask_156ee0;
    sw        $5, 0xE4($16);
    addiu      $4, $16, 0x10;
    jal        GsFbaSetEnable_156e80;
    daddu     $5, $0, $0;
    lbu        $6, 0x70($16);
    andi       $5, $0, 0x1;
    addiu      $3, $0, -0x11;
    sll        $4, $5, 4;
    addiu      $9, $0, -0x2;
    daddiu     $10, $0, 0x1;
    and        $3, $6, $3;
    addiu      $12, $0, 0x1;
    or         $3, $3, $4;
    addiu      $7, $0, -0x9;
    sb         $3, 0x70($16);
    sll        $8, $5, 3;
    lbu        $11, 0x71($16);
    sll        $6, $5, 7;
    sll        $4, $5, 5;
    addiu      $3, $0, -0x21;
    addiu      $5, $0, -0x81;
    and        $9, $11, $9;
    or         $9, $9, $10;
    sb         $9, 0x71($16);
    sw         $12, 0xE0($16);
    lbu        $9, 0x70($16);
    and        $7, $9, $7;
    or         $7, $7, $8;
    sb         $7, 0x70($16);
    lbu        $7, 0x70($16);
    and        $5, $7, $5;
    or         $5, $5, $6;
    sb         $5, 0x70($16);
    lbu        $5, 0x70($16);
    and        $3, $5, $3;
    or         $3, $3, $4;
    sb         $3, 0x70($16);
    ld         $31, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

