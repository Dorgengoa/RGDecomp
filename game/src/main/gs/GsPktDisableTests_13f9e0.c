#include "types.h"

extern void GsTestSetZTest_156f40(void);
extern void GsZbufSetZMask_156ee0(void);
extern void GsTestSetAlphaTest_157100(void);
extern void GsTestSetDate_156ff0(void);

asm void GsPktDisableTests_13f9e0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $5, $0, $0;
    sd         $31, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $16, $4, $0;
    jal        GsTestSetZTest_156f40;
    addiu     $4, $16, 0x10;
    addiu      $5, $0, 0x1;
    addiu      $4, $16, 0x10;
    jal        GsZbufSetZMask_156ee0;
    sw        $5, 0xE4($16);
    addiu      $4, $16, 0x10;
    jal        GsTestSetZTest_156f40;
    daddu     $5, $0, $0;
    andi       $2, $0, 0x1;
    lbu        $6, 0x70($16);
    sll        $3, $2, 6;
    addiu      $4, $16, 0x10;
    addiu      $2, $0, -0x41;
    daddu      $5, $0, $0;
    and        $2, $6, $2;
    or         $2, $2, $3;
    jal        GsTestSetAlphaTest_157100;
    sb        $2, 0x70($16);
    addiu      $4, $16, 0x10;
    jal        GsTestSetDate_156ff0;
    daddu     $5, $0, $0;
    andi       $3, $0, 0x1;
    lbu        $5, 0x70($16);
    sll        $4, $3, 4;
    addiu      $3, $0, -0x11;
    and        $3, $5, $3;
    or         $3, $3, $4;
    sb         $3, 0x70($16);
    ld         $31, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

