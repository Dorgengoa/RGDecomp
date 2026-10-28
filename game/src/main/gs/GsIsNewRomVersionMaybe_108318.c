#include "types.h"

extern void sceOpen_11b928(void);
extern void sceRead_11bf70(void);
extern void sceClose_11bbb8(void);
extern void atoi(void);

asm void GsIsNewRomVersionMaybe_108318(void)
{
    .set noreorder;
    addiu      $29, $29, -0x140;
    lui        $4, 0x45;
    sd         $18, 0x120($29);
    addiu      $5, $0, 0x1;
    sd         $31, 0x130($29);
    addiu      $4, $4, 0x5C38;
    sd         $17, 0x110($29);
    jal        sceOpen_11b928;
    sd        $16, 0x100($29);
    daddu      $18, $2, $0;
    bgez       $18, L00108350;
    daddu     $17, $0, $0;
    b          L001083A0;
    addiu     $2, $0, -0x1;
  L00108350:
    b          L0010835C;
    daddu     $16, $29, $0;
  L00108358:
    addiu      $17, $17, 0x1;
  L0010835C:
    sltiu      $2, $17, 0x100;
    beqz       $2, L00108380;
    daddu     $5, $16, $0;
    daddu      $4, $18, $0;
    jal        sceRead_11bf70;
    addiu     $6, $0, 0x1;
    lb         $3, 0x0($16);
    bnez       $3, L00108358;
    addiu     $16, $16, 0x1;
  L00108380:
    jal        sceClose_11bbb8;
    daddu     $4, $18, $0;
    addiu      $4, $17, -0x9;
    jal        atoi;
    addu      $4, $29, $4;
    lui        $3, (0x1315670 >> 16);
    ori        $3, $3, (0x1315670 & 0xFFFF);
    slt        $2, $3, $2;
  L001083A0:
    ld         $31, 0x130($29);
    ld         $18, 0x120($29);
    ld         $17, 0x110($29);
    ld         $16, 0x100($29);
    jr         $31;
    addiu     $29, $29, 0x140;
}

