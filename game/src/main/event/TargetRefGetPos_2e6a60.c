/* rgp:protos */
#define RGP_SELF_TargetRefGetPos_2e6a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The 13-case wing of the 0x002E5-0x002E6 cluster (see TargetRefSetScale_2e5e10.c for the
   11-case wing).  jtbl_00461960, identity permutation:
   {0,1} -> `return 0`, {2,3} -> A, 4 -> B, 5 -> C, 6 -> D, {7,8} -> E,
   {9,10} -> F, 11 -> G, 12 -> H.

   Shape settled on TargetRefSetRotation_2e5d10 (12-arm sweep, build/mn06/v5d10): the 13/1
   pre-check is a SWITCH whose arms RETURN, with the rest of the function
   written AFTER the switch -- NOT a `default:` arm.  Physical block order (the
   r==1 body first) is the compare chain (13 then 1) REVERSED.

   Retail FALLS THROUGH the `bnel $2,$0` into `$2 = 0; b epilogue`, so that
   guard is the positive `if (p0->m04 == 0) return 0;`.  Each inner arm
   materialises its own `addiu $2,$0,1` -- there is no shared `$2 = 1` block --
   so every arm is an explicit `return 1;`.
   `lui $3,0x3F800000>>16` + `sw` is a float 1.0 constant stored through an
   INTEGER register, which is what mwcc does for a constant float member store.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  TargetRefGetPos_2e6a60  00461960  34   # jtbl_00461960, 13 cases */

/*rgp*/
/*rgp*/
/*rgp*/
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

struct Vec4 {
    f32 m00;
    f32 m04;
    f32 m08;
    f32 m0C;
};

s32 TargetRefGetPos_2e6a60(struct Obj0 *p0, struct Vec4 *p1)
{
    switch (((short)TargetRefGetKind_2e7130(p0))) {
    case 1:
        p1->m00 = p0->m0C;
        p1->m04 = p0->m10;
        p1->m08 = p0->m14;
        p1->m0C = 1.0f;
        return 1;
    case 13:
        p1->m00 = p0->m0C;
        p1->m04 = p0->m10;
        p1->m08 = p0->m14;
        p1->m0C = 1.0f;
        return 1;
    }
    if (p0->m04 == 0) {
        return 0;
    }
    switch (((short)TargetRefGetKind_2e7130(p0))) {
    case 0:
    case 1:
        break;
    case 2:
    case 3:
        FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(p0->m04), p1);
        return 1;
    case 4:
        FrameGetWorldPos_148f30(p0->m04, p1);
        return 1;
    case 5:
        FrameGetWorldPos_148f30(p0->m04, p1);
        return 1;
    case 6:
        MapDataGetPosVec4_1e7740(p0->m04, p1);
        return 1;
    case 7:
    case 8:
        NodeGetWorldPos_186100(p0->m04, p1);
        return 1;
    case 9:
    case 10:
        NodeGetWorldPos_186100(p0->m04, p1);
        return 1;
    case 11:
        TreasureBoxGetPos_33ae30(p0->m04, p1);
        return 1;
    case 12:
        InsectCageSlotGetPos_39b340(p0->m04, p1);
        return 1;
    }
    return 0;
}
