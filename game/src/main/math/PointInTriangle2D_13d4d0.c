#include "types.h"

asm void PointInTriangle2D_13d4d0(void)
{
    .set noreorder;
    c.lt.s     $f14, $f16;
    bc1f       L0013D4F4;
    nop;
    c.lt.s     $f14, $f18;
    bc1fl      L0013D4EC;
    mov.s     $f0, $f18;
    mov.s      $f0, $f14;
  L0013D4EC:
    b          L0013D508;
    nop;
  L0013D4F4:
    c.lt.s     $f16, $f18;
    bc1fl      L0013D508;
    mov.s     $f0, $f18;
    b          L0013D508;
    mov.s     $f0, $f16;
  L0013D508:
    c.le.s     $f0, $f12;
    bc1t       L0013D51C;
    nop;
    b          L0013D6E4;
    daddu     $2, $0, $0;
  L0013D51C:
    c.le.s     $f14, $f16;
    bc1t       L0013D540;
    nop;
    c.le.s     $f14, $f18;
    bc1tl      L0013D538;
    mov.s     $f0, $f18;
    mov.s      $f0, $f14;
  L0013D538:
    b          L0013D554;
    nop;
  L0013D540:
    c.le.s     $f16, $f18;
    bc1tl      L0013D554;
    mov.s     $f0, $f18;
    b          L0013D554;
    mov.s     $f0, $f16;
  L0013D554:
    c.le.s     $f12, $f0;
    bc1t       L0013D568;
    nop;
    b          L0013D6E4;
    daddu     $2, $0, $0;
  L0013D568:
    c.lt.s     $f15, $f17;
    bc1f       L0013D58C;
    nop;
    c.lt.s     $f15, $f19;
    bc1fl      L0013D584;
    mov.s     $f0, $f19;
    mov.s      $f0, $f15;
  L0013D584:
    b          L0013D5A0;
    nop;
  L0013D58C:
    c.lt.s     $f17, $f19;
    bc1fl      L0013D5A0;
    mov.s     $f0, $f19;
    b          L0013D5A0;
    mov.s     $f0, $f17;
  L0013D5A0:
    c.le.s     $f0, $f13;
    bc1t       L0013D5B4;
    nop;
    b          L0013D6E4;
    daddu     $2, $0, $0;
  L0013D5B4:
    c.le.s     $f15, $f17;
    bc1t       L0013D5D8;
    nop;
    c.le.s     $f15, $f19;
    bc1tl      L0013D5D0;
    mov.s     $f0, $f19;
    mov.s      $f0, $f15;
  L0013D5D0:
    b          L0013D5EC;
    nop;
  L0013D5D8:
    c.le.s     $f17, $f19;
    bc1tl      L0013D5EC;
    mov.s     $f0, $f19;
    b          L0013D5EC;
    mov.s     $f0, $f17;
  L0013D5EC:
    c.le.s     $f13, $f0;
    bc1tl      L0013D600;
    sub.s     $f2, $f16, $f14;
    b          L0013D6E4;
    daddu     $2, $0, $0;
  L0013D600:
    sub.s      $f0, $f13, $f15;
    mula.s     $f2, $f0;
    sub.s      $f4, $f17, $f15;
    sub.s      $f3, $f12, $f14;
    msub.s     $f8, $f4, $f3;
    mtc1       $0, $f7;
    sub.s      $f3, $f13, $f17;
    sub.s      $f4, $f18, $f16;
    sub.s      $f6, $f19, $f17;
    sub.s      $f5, $f12, $f16;
    mula.s     $f4, $f3;
    sub.s      $f1, $f14, $f18;
    sub.s      $f0, $f13, $f19;
    msub.s     $f3, $f6, $f5;
    mula.s     $f1, $f0;
    sub.s      $f2, $f15, $f19;
    sub.s      $f0, $f12, $f18;
    c.eq.s     $f7, $f8;
    bc1f       L0013D658;
    msub.s    $f1, $f2, $f0;
    b          L0013D6E4;
    addiu     $2, $0, 0x2;
  L0013D658:
    c.eq.s     $f7, $f3;
    bc1f       L0013D66C;
    nop;
    b          L0013D6E4;
    addiu     $2, $0, 0x3;
  L0013D66C:
    c.eq.s     $f7, $f1;
    bc1f       L0013D680;
    nop;
    b          L0013D6E4;
    addiu     $2, $0, 0x4;
  L0013D680:
    c.le.s     $f8, $f7;
    bc1t       L0013D6AC;
    nop;
    c.le.s     $f3, $f7;
    bc1t       L0013D6AC;
    nop;
    c.le.s     $f1, $f7;
    bc1t       L0013D6AC;
    nop;
    b          L0013D6E4;
    addiu     $2, $0, 0x1;
  L0013D6AC:
    mtc1       $0, $f0;
    nop;
    c.lt.s     $f8, $f0;
    bc1fl      L0013D6E4;
    daddu     $2, $0, $0;
    c.lt.s     $f3, $f0;
    bc1f       L0013D6E0;
    nop;
    c.lt.s     $f1, $f0;
    bc1f       L0013D6E0;
    nop;
    b          L0013D6E4;
    addiu     $2, $0, 0x1;
  L0013D6E0:
    daddu      $2, $0, $0;
  L0013D6E4:
    jr         $31;
    nop;
}

