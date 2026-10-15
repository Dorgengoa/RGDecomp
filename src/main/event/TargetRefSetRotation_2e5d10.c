#include "types.h"

/* The p2 COLUMN of the 0x002E5-0x002E6 cluster (see TargetRefSetScale_2e5e10.c).
   jtbl_00461880, identity permutation, cluster shape.

   MEASURED, 12-arm sweep build/mn06/v5d10 (ONE round trip), on the 13/1
   pre-check.  It is a SWITCH -- an if / else-if chain is 58 words of 61 and no
   spelling of it recovers (c_ifchain, h_ifchain_eq1_empty, l_if_m04_outer all
   58) -- but, unlike its siblings TargetRefSetTranslation_2e5bf0 / TargetRefSetScaleRotPos_2e5a50, the tail must
   NOT live in a `default:` arm.  The two arms that score are
   `case 1: return; case 13: ...; return;` with `if (p0->m04 != 0) { switch }`
   written AFTER the switch (61 words, .text and .rodata byte-identical); every
   `default: if (p0->m04 ...)` spelling is 59, i.e. TWO WORDS SHORT, because
   retail keeps the two DEAD COPIES that the branch-likely hoist leaves behind
   (`lwc1 $f0,0x4($16)` at 0x002E5D4C and `lw $3,0x4($17)` at 0x002E5D58).
   The difference from TargetRefSetTranslation_2e5bf0 is that here the `case 1` arm is EMPTY.
   Also measured INERT at 59 words: a named f32 local for the store, a named
   s32 local for the guard (same object 8e46af62), and the negated guard
   (same object facace5d as the base).

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  TargetRefSetRotation_2e5d10  00461880  2C   # jtbl_00461880, 11 cases */

extern s32 TargetRefGetKind_2e7130(void *);
extern void ModelSetRot_151080(s32, void *);
extern void FrameSetRot_14a390(s32, void *);
extern void NodeSetRotation_186620(s32, void *);

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    f32 m08;
    f32 m0C;
    f32 m10;
    f32 m14;
};

struct Vec3 {
    f32 m00;
    f32 m04;
    f32 m08;
};

void TargetRefSetRotation_2e5d10(struct Obj0 *p0, struct Vec3 *p1)
{
    switch (TargetRefGetKind_2e7130(p0)) {
    case 1:
        return;
    case 13:
        p0->m08 = p1->m04;
        return;
    }
    if (p0->m04 != 0) {
        switch (TargetRefGetKind_2e7130(p0)) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            ModelSetRot_151080(p0->m04, p1);
            break;
        case 4:
            FrameSetRot_14a390(p0->m04, p1);
            break;
        case 5:
            FrameSetRot_14a390(p0->m04, p1);
            break;
        case 6:
            break;
        case 7:
        case 8:
            NodeSetRotation_186620(p0->m04, p1);
            break;
        case 9:
        case 10:
            NodeSetRotation_186620(p0->m04, p1);
            break;
        }
    }
}
