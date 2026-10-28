#include "types.h"

extern void OperatorNew_100990(void);
extern void OperatorDeleteArray_100820(void);
extern void ThrowException_1025c0(void);
extern void EhEndCatch_101010(void);

asm void SharedArrayPtrCtor_102b30(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $31, 0x20($29);
    sq         $30, 0x10($29);
    sq         $16, 0x0($29);
    addu       $30, $29, $0;
    sw         $5, 0x0($4);
    daddu      $16, $4, $0;
    sw         $0, 0x4($4);
    sw         $29, 0x44($30);
    lw         $2, 0x0($16);
    beql       $2, $0, L00102BAC;
    daddu     $2, $16, $0;
    jal        OperatorNew_100990;
    addiu     $4, $0, 0x4;
    beql       $2, $0, L00102BA8;
    sw        $2, 0x4($16);
    addiu      $3, $0, 0x1;
    sw         $3, 0x0($2);
    sw         $2, 0x4($16);
    b          L00102BA8;
    nop;
    jal        OperatorDeleteArray_100820;
    lw        $4, 0x0($16);
    daddu      $4, $0, $0;
    daddu      $5, $0, $0;
    jal        ThrowException_1025c0;
    daddu     $6, $0, $0;
    jal        EhEndCatch_101010;
    addiu     $4, $30, 0x30;
    lw         $29, 0x44($30);
  L00102BA8:
    daddu      $2, $16, $0;
  L00102BAC:
    addu       $29, $30, $0;
    ld         $31, 0x20($29);
    lq         $30, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

