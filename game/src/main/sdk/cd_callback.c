#include "types.h"

extern void iSignalSema(void);

asm void cd_callback(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $5, $0, 0xB;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    lui        $16, 0x44;
    lw         $3, 0x0($4);
    lui        $4, 0x44;
    sw         $3, 0x79A0($16);
    lw         $2, 0x79A0($16);
    sw         $2, 0x79A4($4);
    lw         $3, 0x79A0($16);
    bne        $3, $5, L00129288;
    lui       $2, 0x44;
    sw         $0, 0x79A0($16);
    lui        $2, 0x44;
    sw         $0, 0x7974($2);
    b          L001292D4;
    ld        $31, 0x10($29);
  L00129288:
    lw         $4, 0x7968($2);
    jal        iSignalSema;
    nop;
    lui        $3, 0x44;
    lw         $2, 0x7954($3);
    beqz       $2, L001292C4;
    lui       $2, 0x49;
    lw         $3, -0x15C0($2);
    beqz       $3, L001292C4;
    lui       $2, 0x44;
    lw         $4, 0x7960($2);
    jal        iSignalSema;
    nop;
    b          L001292CC;
    nop;
  L001292C4:
    lui        $2, 0x44;
    sw         $0, 0x7974($2);
  L001292CC:
    sw         $0, 0x79A0($16);
    ld         $31, 0x10($29);
  L001292D4:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
