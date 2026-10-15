#include "types.h"

/* The FAN-OUT of the 0x002E5-0x002E6 cluster: each switch arm is the same
   operation applied to p1, p2 and p3 with the three callee triples that
   TargetRefSetScale_2e5e10 / TargetRefSetRotation_2e5d10 / TargetRefSetTranslation_2e5bf0 each carry one column of.
   jtbl_00461820, identity permutation, cluster shape
   ({0,1,6} default, {2,3} A, 4 B, 5 C, {7,8} D, {9,10} E).

   The r0 == 13 / r0 == 1 pair here is a REAL `||` join: retail reaches ONE
   block, via a `beql` (13, with the block's first instruction in the delay
   slot) and a plain `beq` (1, to the copy of that instruction one word
   earlier).  TargetRefSetTranslation_2e5bf0 emits TWO blocks for the same pair of values, which
   is what an if / else-if chain looks like.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  TargetRefSetScaleRotPos_2e5a50  00461820  2C   # jtbl_00461820, 11 cases */

extern s32 TargetRefGetKind_2e7130(void *);
extern void TargetRefSetRotation_2e5d10(void *, void *);
extern void TargetRefSetTranslation_2e5bf0(void *, void *);
extern void ModelSetScale_150ff0(s32, void *);
extern void ModelSetRot_151080(s32, void *);
extern void ModelSetPos_151110(s32, void *);
extern void FrameSetScale_14a2c0(s32, void *);
extern void FrameSetRot_14a390(s32, void *);
extern void FrameSetPos_14a450(s32, void *);
extern void NodeSetScale_1865b0(s32, void *);
extern void NodeSetRotation_186620(s32, void *);
extern void NodeSetTranslation_1866b0(s32, void *);

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

void TargetRefSetScaleRotPos_2e5a50(struct Obj0 *p0, void *p1, void *p2, void *p3)
{
    switch (TargetRefGetKind_2e7130(p0)) {
    case 1:
    case 13:
        TargetRefSetRotation_2e5d10(p0, p2);
        TargetRefSetTranslation_2e5bf0(p0, p3);
        break;
    default:
        if (p0->m04 != 0) {
            switch (TargetRefGetKind_2e7130(p0)) {
            case 0:
            case 1:
                break;
            case 2:
            case 3:
                ModelSetScale_150ff0(p0->m04, p1);
                ModelSetRot_151080(p0->m04, p2);
                ModelSetPos_151110(p0->m04, p3);
                break;
            case 4:
                FrameSetScale_14a2c0(p0->m04, p1);
                FrameSetRot_14a390(p0->m04, p2);
                FrameSetPos_14a450(p0->m04, p3);
                break;
            case 5:
                FrameSetScale_14a2c0(p0->m04, p1);
                FrameSetRot_14a390(p0->m04, p2);
                FrameSetPos_14a450(p0->m04, p3);
                break;
            case 6:
                break;
            case 7:
            case 8:
                NodeSetScale_1865b0(p0->m04, p1);
                NodeSetRotation_186620(p0->m04, p2);
                NodeSetTranslation_1866b0(p0->m04, p3);
                break;
            case 9:
            case 10:
                NodeSetScale_1865b0(p0->m04, p1);
                NodeSetRotation_186620(p0->m04, p2);
                NodeSetTranslation_1866b0(p0->m04, p3);
                break;
            }
        }
        break;
    }
}
