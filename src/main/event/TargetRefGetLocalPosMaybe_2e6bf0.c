#include "types.h"

/* 13-case sibling of TargetRefGetPos_2e6a60 -- same source shape, different callee
   column.  jtbl_004619A0, identity permutation, same case grouping.

   The {2,3} arm is a `lq 0x180 / sq 0x0` pair, i.e. a 128-BIT ASSIGNMENT
   (levers.d: a u128 local/member is what makes mwcc emit lq/sq here).

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  TargetRefGetLocalPosMaybe_2e6bf0  004619A0  34   # jtbl_004619A0, 13 cases */

typedef unsigned __int128 u128;

extern s32 TargetRefGetKind_2e7130(void *);
extern void ModelFrameGetPos_14a220(s32, void *);
extern void MapDataGetPosVec4_1e7740(s32, void *);
extern void NodeGetTranslation_186650(s32, void *);
extern void TreasureBoxGetPos_33ae30(s32, void *);
extern void InsectCageSlotGetPos_39b340(s32, void *);

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    f32 m08;
    f32 m0C;
    f32 m10;
    f32 m14;
};

struct Big {
    u8 pad000[0x180];
    u128 m180;
};

struct Vec4 {
    f32 m00;
    f32 m04;
    f32 m08;
    f32 m0C;
};

s32 TargetRefGetLocalPosMaybe_2e6bf0(struct Obj0 *p0, struct Vec4 *p1)
{
    switch (TargetRefGetKind_2e7130(p0)) {
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
    switch (TargetRefGetKind_2e7130(p0)) {
    case 0:
    case 1:
        break;
    case 2:
    case 3:
        *(u128 *)p1 = ((struct Big *)p0->m04)->m180;
        return 1;
    case 4:
        ModelFrameGetPos_14a220(p0->m04, p1);
        return 1;
    case 5:
        ModelFrameGetPos_14a220(p0->m04, p1);
        return 1;
    case 6:
        MapDataGetPosVec4_1e7740(p0->m04, p1);
        return 1;
    case 7:
    case 8:
        NodeGetTranslation_186650(p0->m04, p1);
        return 1;
    case 9:
    case 10:
        NodeGetTranslation_186650(p0->m04, p1);
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
