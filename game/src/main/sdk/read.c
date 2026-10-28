#include "types.h"

extern void sceTtyInit(void);
extern void sceTtyRead(void);

asm void read(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    daddu      $18, $6, $0;
    sd         $31, 0x30($29);
    daddu      $17, $5, $0;
    bnez       $4, L00116C40;
    sd        $16, 0x0($29);
    lui        $16, 0x44;
    lw         $2, 0x61F0($16);
    bnez       $2, L00116C30;
    daddu     $4, $17, $0;
    jal        sceTtyInit;
    nop;
    beqz       $2, L00116C40;
    addiu     $2, $0, 0x1;
    sw         $2, 0x61F0($16);
    daddu      $4, $17, $0;
  L00116C30:
    jal        sceTtyRead;
    daddu     $5, $18, $0;
    b          L00116C48;
    ld        $31, 0x30($29);
  L00116C40:
    addiu      $2, $0, -0x1;
    ld         $31, 0x30($29);
  L00116C48:
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
