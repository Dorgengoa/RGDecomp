#include "types.h"

extern void fptodp(void);
extern void Tan_1289b8(void);
extern void dpmul(void);
extern void AtanDouble_127d68(void);
extern void dptofp(void);

asm void FovHorizToVert_13fbe0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    lui        $2, (0x43340000 >> 16);
    lwc1       $f2, -0x7F74($28);
    sd         $31, 0x0($29);
    mtc1       $2, $f1;
    lui        $2, (0x40000000 >> 16);
    mul.s      $f2, $f2, $f12;
    div.s      $f1, $f2, $f1;
    mtc1       $2, $f0;
    nop;
    nop;
    div.s      $f12, $f1, $f0;
    nop;
    nop;
    jal        fptodp;
    nop;
    jal        Tan_1289b8;
    daddu     $4, $2, $0;
    lui        $3, (0x3FE80000 >> 16);
    daddu      $5, $2, $0;
    jal        dpmul;
    dsll32    $4, $3, 0;
    jal        AtanDouble_127d68;
    daddu     $4, $2, $0;
    lui        $3, (0x40000000 >> 16);
    daddu      $5, $2, $0;
    jal        dpmul;
    dsll32    $4, $3, 0;
    jal        dptofp;
    daddu     $4, $2, $0;
    lui        $2, (0x43340000 >> 16);
    mtc1       $2, $f1;
    nop;
    mul.s      $f1, $f1, $f0;
    lwc1       $f0, -0x7F74($28);
    div.s      $f0, $f1, $f0;
    nop;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

