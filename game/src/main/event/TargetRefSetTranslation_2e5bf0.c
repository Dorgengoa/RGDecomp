/* rgp:protos */
#define RGP_SELF_TargetRefSetTranslation_2e5bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The p3 COLUMN of the 0x002E5-0x002E6 cluster (see TargetRefSetScale_2e5e10.c).
   jtbl_00461850, identity permutation, cluster shape.

   MEASURED, round trip 1 -> 2: the 13/1 pre-check is a SWITCH, not an
   if/else-if chain.  Written as `if (r0 == 13) ... else if (r0 == 1) ...`
   mwcc emits `bnel` PAST each arm and folds the else into the fall-through --
   exactly one word short (68 of 69).  Retail emits `beql` INTO each arm plus
   its own `b <default>`, which is the switch shape, and the physical block
   order (the r0==1 body FIRST) is the compare chain (13 then 1) REVERSED.

   The two arms have IDENTICAL three-store bodies and retail emits TWO copies,
   so they are two arms, not one label group -- contrast TargetRefSetScaleRotPos_2e5a50, where
   the same pair of values shares ONE block.  The stores are INTERLEAVED
   load/store pairs, i.e. three separate assignments, not a struct copy.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  TargetRefSetTranslation_2e5bf0  00461850  2C   # jtbl_00461850, 11 cases */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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

void TargetRefSetTranslation_2e5bf0(struct Obj0 *p0, struct Vec3 *p1)
{
    switch (((short)TargetRefGetKind_2e7130(p0))) {
    case 1:
        p0->m0C = p1->m00;
        p0->m10 = p1->m04;
        p0->m14 = p1->m08;
        break;
    case 13:
        p0->m0C = p1->m00;
        p0->m10 = p1->m04;
        p0->m14 = p1->m08;
        break;
    default:
        if (p0->m04 != 0) {
            switch (((short)TargetRefGetKind_2e7130(p0))) {
            case 0:
            case 1:
                break;
            case 2:
            case 3:
                ModelSetPos_151110(p0->m04, p1);
                break;
            case 4:
                FrameSetPos_14a450(p0->m04, p1);
                break;
            case 5:
                FrameSetPos_14a450(p0->m04, p1);
                break;
            case 6:
                break;
            case 7:
            case 8:
                NodeSetTranslation_1866b0(p0->m04, p1);
                break;
            case 9:
            case 10:
                NodeSetTranslation_1866b0(p0->m04, p1);
                break;
            }
        }
        break;
    }
}
