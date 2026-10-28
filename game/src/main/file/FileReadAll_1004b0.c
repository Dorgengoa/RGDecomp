#include "types.h"

extern void sceOpen_11b928(void);
extern void sceLseek_11bd30(void);
extern void sceRead_11bf70(void);
extern void sceClose_11bbb8(void);

asm void FileReadAll_1004b0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x30($29);
    sq         $18, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $0, $0;
    daddu      $16, $5, $0;
    jal        sceOpen_11b928;
    addiu     $5, $0, 0x1;
    daddu      $18, $2, $0;
    bltz       $18, L00100504;
    nop;
    daddu      $4, $18, $0;
    daddu      $5, $0, $0;
    jal        sceLseek_11bd30;
    addiu     $6, $0, 0x2;
    daddu      $17, $2, $0;
    daddu      $4, $18, $0;
    daddu      $5, $0, $0;
    jal        sceLseek_11bd30;
    daddu     $6, $0, $0;
  L00100504:
    blez       $17, L00100538;
    nop;
    daddu      $5, $16, $0;
    daddu      $6, $17, $0;
    daddu      $4, $18, $0;
    jal        sceRead_11bf70;
    daddu     $16, $17, $0;
    daddu      $17, $2, $0;
    bltz       $17, L00100538;
    nop;
    beq        $17, $16, L00100538;
    nop;
    addiu      $17, $0, -0x1;
  L00100538:
    bltzl      $18, L0010054C;
    daddu     $2, $17, $0;
    jal        sceClose_11bbb8;
    daddu     $4, $18, $0;
    daddu      $2, $17, $0;
  L0010054C:
    ld         $31, 0x30($29);
    lq         $18, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

