#include "types.h"

asm void AngleDiffSign_13c0d0(void)
{
    .set noreorder;
    sub.s      $f1, $f12, $f13;
    mtc1       $0, $f0;
    nop;
    c.eq.s     $f0, $f1;
    bc1fl      L0013C0F0;
    lwc1      $f0, -0x7F74($28);
    b          L0013C148;
    daddu     $2, $0, $0;
  L0013C0F0:
    c.le.s     $f1, $f0;
    bc1tl      L0013C108;
    lwc1      $f0, -0x7E5C($28);
    lwc1       $f0, -0x7E58($28);
    sub.s      $f1, $f1, $f0;
    lwc1       $f0, -0x7E54($28);
  L0013C108:
    c.lt.s     $f1, $f0;
    bc1f       L0013C11C;
    nop;
    lwc1       $f0, -0x7E50($28);
    add.s      $f1, $f1, $f0;
  L0013C11C:
    c.le.s     $f1, $f14;
    bc1tl      L0013C130;
    neg.s     $f0, $f14;
    b          L0013C148;
    addiu     $2, $0, 0x1;
  L0013C130:
    c.lt.s     $f1, $f0;
    bc1t       L0013C140;
    addiu     $2, $0, 0x1;
    daddu      $2, $0, $0;
  L0013C140:
    andi       $2, $2, 0xFF;
    negu       $2, $2;
  L0013C148:
    jr         $31;
    nop;
}

