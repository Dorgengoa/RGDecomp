/* rgp:protos */
#define RGP_SELF_InvIdGetMajorIndex_3d55f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on

/* Not the Var-accessor family.  p0 is a raw s32 (time-ish value).
   InvGetCategoryOfId_3d56f0(p0) buckets it into a tag 0-9 (or -1 out of range,
   already-existing helper elsewhere).  Per tag, either return a
   constant, or `(p0 - BASE)/SCALE` with BASE/SCALE a pair of far
   (below the $gp window, so plain lui/lw, no small-data games) s32
   globals.  jtbl_004665A0 text-order (NOT value order):
   0,1,2,3,6,7,8,9,{4,5} -- five separate `return 0;` case clusters
   (2,3,6,7,8) each get their OWN code copy (never merge them), and
   {4,5} share ONE cluster + textually-separate `default:` shares the
   SAME return value (-1) but is a DIFFERENT arm, compiled into the
   out-of-range bound check's delay slot (same idiom as the Var
   family's "case 0 shares default"). */

/*rgp*/
extern s32 D_00465A00[3];
extern s32 D_00465A08[3];
extern s32 D_00465A30[3];
extern s32 D_00465A38[3];
extern s32 D_00465B28[3];
extern s32 D_00465B30[3];

s32 InvIdGetMajorIndex_3d55f0(s32 p0)
{
    s32 tag;

    tag = InvGetCategoryOfId_3d56f0(p0);
    switch (tag) {
    case 0:
        return (p0 - D_00465A08[0]) / D_00465A00[0];
    case 1:
        return (p0 - D_00465A38[0]) / D_00465A30[0];
    case 2:
        return 0;
    case 3:
        return 0;
    case 6:
        return 0;
    case 7:
        return 0;
    case 8:
        return 0;
    case 9:
        return (p0 - D_00465B30[0]) / D_00465B28[0];
    case 4:
    case 5:
    default:
        return -1;
    }
}
