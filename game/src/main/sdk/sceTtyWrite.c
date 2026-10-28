#include "types.h"

extern void DisableIntr_120660(void);
extern void sceDeci2ReqSend(void);
extern void EnableIntr_1206b0(void);
extern void sceDeci2Poll_117920(void);

asm void sceTtyWrite(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    lui        $21, 0x48;
    sd         $19, 0x30($29);
    daddu      $20, $0, $0;
    sd         $18, 0x20($29);
    addiu      $19, $21, 0x6510;
    sd         $17, 0x10($29);
    daddu      $18, $5, $0;
    sd         $16, 0x0($29);
    daddu      $17, $0, $0;
    sd         $31, 0x70($29);
    daddu      $16, $4, $0;
    sd         $22, 0x60($29);
    lw         $2, 0xC($19);
    bnez       $2, L00117E44;
    addiu     $2, $0, -0x1;
    jal        DisableIntr_120660;
    nop;
    daddu      $22, $2, $0;
    lui        $4, (0x20000000 >> 16);
    lui        $2, 0x48;
    addiu      $3, $0, 0x1;
    addiu      $2, $2, 0x6540;
    sw         $3, 0xC($19);
    or         $6, $2, $4;
    addiu      $8, $0, -0x1;
    sw         $6, 0x10($19);
    addiu      $7, $0, 0xA;
    addiu      $5, $0, 0xD;
    addiu      $4, $6, 0xC;
  L00117D78:
    addiu      $18, $18, -0x1;
    beql       $18, $8, L00117DC8;
    addiu     $16, $21, 0x6510;
    lb         $2, 0x0($16);
    bne        $2, $7, L00117DA8;
    lbu       $3, 0x0($16);
    sb         $5, 0x0($4);
    addiu      $17, $17, 0x1;
    slti       $2, $17, 0x100;
    beqz       $2, L00117DC4;
    addiu     $4, $4, 0x1;
    lbu        $3, 0x0($16);
  L00117DA8:
    sb         $3, 0x0($4);
    addiu      $17, $17, 0x1;
    addiu      $16, $16, 0x1;
    addiu      $4, $4, 0x1;
    slti       $2, $17, 0x100;
    bnez       $2, L00117D78;
    addiu     $20, $20, 0x1;
  L00117DC4:
    addiu      $16, $21, 0x6510;
  L00117DC8:
    addiu      $2, $17, 0xC;
    sw         $2, 0x4($16);
    lw         $3, 0x4($16);
    lb         $5, 0x7($6);
    lw         $4, 0x6510($21);
    jal        sceDeci2ReqSend;
    sh        $3, 0x0($6);
    bgez       $2, L00117E08;
    nop;
    sw         $0, 0xC($16);
    beqz       $22, L00117E44;
    addiu     $2, $0, -0x1;
    jal        EnableIntr_1206b0;
    nop;
    b          L00117E44;
    addiu     $2, $0, -0x1;
  L00117E08:
    lw         $2, 0xC($16);
    beqz       $2, L00117E30;
    daddu     $17, $21, $0;
    nop;
  L00117E18:
    lw         $4, 0x6510($17);
    jal        sceDeci2Poll_117920;
    nop;
    lw         $2, 0xC($16);
    bnez       $2, L00117E18;
    nop;
  L00117E30:
    beqz       $22, L00117E44;
    daddu     $2, $20, $0;
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $20, $0;
  L00117E44:
    ld         $31, 0x70($29);
    ld         $22, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
