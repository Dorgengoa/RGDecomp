#include "types.h"

asm void AngleStepToward_13c150(void)
{
    .set noreorder;
    sub.s      $f2, $f13, $f12;
    lwc1       $f0, -0x7F74($28);
    c.le.s     $f2, $f0;
    bc1tl      L0013C170;
    lwc1      $f0, -0x7E80($28);
    lwc1       $f0, -0x7E7C($28);
    sub.s      $f2, $f2, $f0;
    lwc1       $f0, -0x7E78($28);
  L0013C170:
    c.le.s     $f2, $f0;
    bc1f       L0013C184;
    nop;
    lwc1       $f0, -0x7E74($28);
    add.s      $f2, $f2, $f0;
  L0013C184:
    mtc1       $0, $f1;
    bnel       $4, $0, L0013C1B8;
    addiu     $2, $0, 0x1;
    c.lt.s     $f2, $f1;
    bc1fl      L0013C1A0;
    mov.s     $f0, $f2;
    neg.s      $f0, $f2;
  L0013C1A0:
    c.lt.s     $f0, $f14;
    bc1f       L0013C1B4;
    nop;
    b          L0013C260;
    mov.s     $f0, $f13;
  L0013C1B4:
    addiu      $2, $0, 0x1;
  L0013C1B8:
    beq        $4, $2, L0013C220;
    nop;
    beqz       $4, L0013C1D0;
    nop;
    b          L0013C230;
    add.s     $f0, $f12, $f1;
  L0013C1D0:
    mtc1       $0, $f0;
    nop;
    c.lt.s     $f2, $f0;
    bc1f       L0013C1F8;
    nop;
    c.lt.s     $f14, $f2;
    bc1fl      L0013C1F8;
    sub.s     $f1, $f1, $f14;
    b          L0013C260;
    mov.s     $f0, $f13;
  L0013C1F8:
    mtc1       $0, $f0;
    nop;
    c.lt.s     $f2, $f0;
    bc1t       L0013C22C;
    nop;
    c.le.s     $f14, $f2;
    bc1tl      L0013C22C;
    add.s     $f1, $f1, $f14;
    b          L0013C260;
    mov.s     $f0, $f13;
  L0013C220:
    nop;
    nop;
    div.s      $f1, $f2, $f14;
  L0013C22C:
    add.s      $f0, $f12, $f1;
  L0013C230:
    lwc1       $f1, -0x7F74($28);
    c.le.s     $f0, $f1;
    bc1tl      L0013C24C;
    lwc1      $f1, -0x7E70($28);
    lwc1       $f1, -0x7E6C($28);
    sub.s      $f0, $f0, $f1;
    lwc1       $f1, -0x7E68($28);
  L0013C24C:
    c.le.s     $f0, $f1;
    bc1f       L0013C260;
    nop;
    lwc1       $f1, -0x7E64($28);
    add.s      $f0, $f0, $f1;
  L0013C260:
    jr         $31;
    nop;
}

