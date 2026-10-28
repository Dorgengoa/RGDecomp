#include "types.h"

extern void memset(void);
extern void AlarmPoolInit_122240(void);
extern void AddIntcHandler_2(void);
extern void DisableIntr_120660(void);
extern void Timer2SetCount_120f40(void);
extern void Timer2SetCompare_120f60(void);
extern void Timer2SetMode_120f50(void);
extern void EnableIntc_1170e8(void);
extern void EnableIntr_1206b0(void);

asm void InitTimer_120f70(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $18, 0x20($29);
    sd         $20, 0x40($29);
    lui        $18, 0x44;
    sd         $17, 0x10($29);
    sd         $31, 0x50($29);
    addiu      $17, $18, 0x78A8;
    sd         $19, 0x30($29);
    sd         $16, 0x0($29);
    lw         $2, 0x8($17);
    bltz       $2, L00120FAC;
    daddu     $20, $4, $0;
    lui        $2, (0x80008001 >> 16);
    b          L001210A4;
    ori       $2, $2, (0x80008001 & 0xFFFF);
  L00120FAC:
    lui        $19, 0x49;
    sd         $0, 0x78A8($18);
    addiu      $16, $19, -0x4D80;
    sw         $0, 0x10($17);
    daddu      $4, $16, $0;
    daddu      $5, $0, $0;
    jal        memset;
    addiu     $6, $0, 0x2000;
    sw         $16, 0x14($17);
    addiu      $3, $16, 0x2000;
    addiu      $2, $0, 0x7F;
    addiu      $16, $16, 0x1FC0;
    nop;
  L00120FE0:
    sw         $3, 0x0($16);
    addiu      $2, $2, -0x1;
    addiu      $16, $16, -0x40;
    addiu      $3, $3, -0x40;
    nop;
    bgez       $2, L00120FE0;
    nop;
    addiu      $2, $19, -0x4D80;
    jal        AlarmPoolInit_122240;
    sw        $0, 0x1FC0($2);
    lui        $5, 0x12;
    addiu      $4, $0, 0xB;
    addiu      $5, $5, 0x1510;
    daddu      $6, $0, $0;
    jal        AddIntcHandler_2;
    daddu     $7, $0, $0;
    daddu      $3, $2, $0;
    bgezl      $3, L00121038;
    addiu     $2, $18, 0x78A8;
    lui        $2, (0x80009021 >> 16);
    b          L001210A4;
    ori       $2, $2, (0x80009021 & 0xFFFF);
  L00121038:
    jal        DisableIntr_120660;
    sw        $3, 0x8($2);
    lui        $3, (0x10001010 >> 16);
    daddu      $17, $2, $0;
    ori        $3, $3, (0x10001010 & 0xFFFF);
    lui        $2, (0xFFFFFFFC >> 16);
    lw         $16, 0x0($3);
    ori        $2, $2, (0xFFFFFFFC & 0xFFFF);
    and        $2, $16, $2;
    or         $16, $2, $20;
    ori        $16, $16, 0x300;
    andi       $2, $16, 0x80;
    bnez       $2, L00121080;
    daddu     $4, $0, $0;
    jal        Timer2SetCount_120f40;
    ori       $16, $16, 0xC80;
    jal        Timer2SetCompare_120f60;
    ori       $4, $0, 0xFFFF;
  L00121080:
    jal        Timer2SetMode_120f50;
    daddu     $4, $16, $0;
    jal        EnableIntc_1170e8;
    addiu     $4, $0, 0xB;
    beqz       $17, L001210A4;
    daddu     $2, $0, $0;
    jal        EnableIntr_1206b0;
    nop;
    daddu      $2, $0, $0;
  L001210A4:
    ld         $31, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}
