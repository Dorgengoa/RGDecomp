#include "types.h"

extern void Timer2SetCompare_120f60(void);
extern void Timer2SetMode_120f50(void);

asm void SetNextComp_1212c0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    lui        $2, 0x44;
    sd         $31, 0x30($29);
    addiu      $2, $2, 0x78A8;
    sd         $18, 0x20($29);
    daddu      $7, $4, $0;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    lw         $3, 0x1C($2);
    bgez       $3, L00121438;
    lw        $6, 0x18($2);
    lui        $2, (0x10001010 >> 16);
    ori        $2, $2, (0x10001010 & 0xFFFF);
    lw         $18, 0x0($2);
    bnel       $6, $0, L0012132C;
    ld        $2, 0x20($6);
    jal        Timer2SetCompare_120f60;
    daddu     $4, $0, $0;
    lui        $4, (0xFFFFF7FF >> 16);
    ld         $31, 0x30($29);
    ori        $4, $4, (0xFFFFF7FF & 0xFFFF);
    ld         $17, 0x10($29);
    and        $4, $18, $4;
    ld         $16, 0x0($29);
    ld         $18, 0x20($29);
    j          Timer2SetMode_120f50;
    addiu     $29, $29, 0x40;
  L0012132C:
    ld         $3, 0x10($6);
    ld         $4, 0x18($6);
    daddu      $2, $2, $3;
    lw         $6, 0x0($6);
    beqz       $6, L001213A4;
    dsubu     $16, $2, $4;
    ld         $2, 0x20($6);
    daddiu     $3, $16, 0x7333;
    ld         $4, 0x10($6);
    ld         $5, 0x18($6);
    daddu      $2, $2, $4;
    dsubu      $2, $2, $5;
    sltu       $3, $2, $3;
    beqz       $3, L001213A4;
    andi      $17, $18, 0x3;
    daddu      $16, $2, $0;
    nop;
  L00121370:
    lw         $6, 0x0($6);
    beqz       $6, L001213A8;
    daddiu    $3, $16, 0x7333;
    ld         $2, 0x20($6);
    ld         $4, 0x10($6);
    ld         $5, 0x18($6);
    daddu      $2, $2, $4;
    dsubu      $2, $2, $5;
    sltu       $3, $2, $3;
    beql       $3, $0, L001213AC;
    dsubu     $2, $16, $7;
    b          L00121370;
    daddu     $16, $2, $0;
  L001213A4:
    andi       $17, $18, 0x3;
  L001213A8:
    dsubu      $2, $16, $7;
  L001213AC:
    slti       $2, $2, 0x7333;
    beqz       $2, L00121400;
    lui       $2, (0x10001000 >> 16);
    sll        $5, $17, 2;
    ori        $2, $2, (0x10001000 & 0xFFFF);
    addiu      $4, $0, 0x7333;
    dsrlv      $4, $4, $5;
    lw         $3, 0x0($2);
    dsll32     $4, $4, 0;
    dsra32     $4, $4, 0;
    jal        Timer2SetCompare_120f60;
    addu      $4, $3, $4;
    lui        $4, (0xFFFFF7FF >> 16);
    ld         $31, 0x30($29);
    ori        $4, $4, (0xFFFFF7FF & 0xFFFF);
    ld         $17, 0x10($29);
    and        $4, $18, $4;
    ld         $16, 0x0($29);
    ld         $18, 0x20($29);
    j          Timer2SetMode_120f50;
    addiu     $29, $29, 0x40;
  L00121400:
    lui        $4, (0xFFFFF7FF >> 16);
    ori        $4, $4, (0xFFFFF7FF & 0xFFFF);
    jal        Timer2SetMode_120f50;
    and       $4, $18, $4;
    sll        $4, $17, 2;
    ld         $31, 0x30($29);
    dsrlv      $4, $16, $4;
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    dsll32     $4, $4, 0;
    dsra32     $4, $4, 0;
    ld         $16, 0x0($29);
    j          Timer2SetCompare_120f60;
    addiu     $29, $29, 0x40;
  L00121438:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
