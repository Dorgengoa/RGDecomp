/* rgp:protos */
#define RGP_SELF_TargetRefSetScale_2e5e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 0x002E5-0x002E6 sibling cluster (TargetRefSetScaleRotPos_2e5a50 fans out to
   TargetRefSetRotation_2e5d10 and TargetRefSetTranslation_2e5bf0; the three callee triples below are the three
   ARGUMENT COLUMNS of TargetRefSetScaleRotPos_2e5a50's arms):
       column p1: ModelSetScale_150ff0 / FrameSetScale_14a2c0 / NodeSetScale_1865b0   <- THIS unit
       column p2: ModelSetRot_151080 / FrameSetRot_14a390 / NodeSetRotation_186620   <- TargetRefSetRotation_2e5d10
       column p3: ModelSetPos_151110 / FrameSetPos_14a450 / NodeSetTranslation_1866b0   <- TargetRefSetTranslation_2e5bf0

   jtbl_004618B0 is 11 entries and is the IDENTITY permutation, so physical
   block order IS source order.  Its shape is shared verbatim by
   jtbl_00461820 / 50 / 80: {0,1,6} -> the shared epilogue (empty arms that
   still need their `case` labels), {2,3} -> A, 4 -> B, 5 -> C, {7,8} -> D,
   {9,10} -> E.  Cases 4 and 5 have IDENTICAL bodies and are two blocks, so
   they are two arms, not one label group.

   Retail FALLS THROUGH the `beqz $3` into the `jal`, so the source guard is
   the positive `if (p0->m04 != 0)`.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  TargetRefSetScale_2e5e10  004618B0  2C   # jtbl_004618B0, 11 cases */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
};

void TargetRefSetScale_2e5e10(struct Obj0 *p0, void *p1)
{
    if (p0->m04 != 0) {
        switch (((short)TargetRefGetKind_2e7130(p0))) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            ModelSetScale_150ff0(p0->m04, p1);
            break;
        case 4:
            FrameSetScale_14a2c0(p0->m04, p1);
            break;
        case 5:
            FrameSetScale_14a2c0(p0->m04, p1);
            break;
        case 6:
            break;
        case 7:
        case 8:
            NodeSetScale_1865b0(p0->m04, p1);
            break;
        case 9:
        case 10:
            NodeSetScale_1865b0(p0->m04, p1);
            break;
        }
    }
}
