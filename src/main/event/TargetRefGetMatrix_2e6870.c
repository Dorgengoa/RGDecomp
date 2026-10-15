#include "types.h"

/* 13-case sibling of TargetRefGetPos_2e6a60 / TargetRefGetLocalPosMaybe_2e6bf0.  jtbl_00461920, identity
   permutation, same case grouping.  This is the wing that writes at +0x30 of
   the destination and calls MatIdentity_1cbe40 first, and its 6 / 11 / 12 arms build
   TWO 16-byte stack temporaries and hand both to MatFromRotPos_1caf90 -- six locals at
   sp+0x30..0x80, which is the whole -0x90 frame above the 0x20 save area.
   mwcc allocates stack LOCALS in REVERSE declaration order.

   SHIPPING THIS UNIT NEEDS A .rodata SLOT:
       config/crodata.txt:  TargetRefGetMatrix_2e6870  00461920  34   # jtbl_00461920, 13 cases */

extern s32 TargetRefGetKind_2e7130(void *);
extern void MatIdentity_1cbe40(void *);
extern s32 ModelGetRootFrame_1511a0(s32);
extern void FrameCalcWorldMatrix_148ff0(s32, void *);
extern void MapDataGetRotVec4_1e7720(s32, void *);
extern void MapDataGetPosVec4_1e7740(s32, void *);
extern void MatFromRotPos_1caf90(void *, void *, void *);
extern void NodeCalcWorldMatrixThunk_186130(s32, void *);
extern void NodeCalcWorldMatrix_186130(s32, void *);
extern void TreasureBoxGetRot_33ae20(s32, void *);
extern void TreasureBoxGetPos_33ae30(s32, void *);
extern void InsectCageSlotGetRot_39b320(s32, void *);
extern void InsectCageSlotGetPos_39b340(s32, void *);

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    f32 m08;
    f32 m0C;
    f32 m10;
    f32 m14;
};

struct Dst {
    u8 pad000[0x30];
    f32 m30;
    f32 m34;
    f32 m38;
    f32 m3C;
};

struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

s32 TargetRefGetMatrix_2e6870(struct Obj0 *p0, struct Dst *p1)
{
    struct V4 v80;
    struct V4 v70;
    struct V4 v60;
    struct V4 v50;
    struct V4 v40;
    struct V4 v30;

    switch (TargetRefGetKind_2e7130(p0)) {
    case 1:
        MatIdentity_1cbe40(p1);
        p1->m30 = p0->m0C;
        p1->m34 = p0->m10;
        p1->m38 = p0->m14;
        p1->m3C = 1.0f;
        return 1;
    case 13:
        MatIdentity_1cbe40(p1);
        p1->m30 = p0->m0C;
        p1->m34 = p0->m10;
        p1->m38 = p0->m14;
        p1->m3C = 1.0f;
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
        FrameCalcWorldMatrix_148ff0(ModelGetRootFrame_1511a0(p0->m04), p1);
        return 1;
    case 4:
        FrameCalcWorldMatrix_148ff0(p0->m04, p1);
        return 1;
    case 5:
        FrameCalcWorldMatrix_148ff0(p0->m04, p1);
        return 1;
    case 6:
        MapDataGetRotVec4_1e7720(p0->m04, &v80);
        MapDataGetPosVec4_1e7740(p0->m04, &v70);
        MatFromRotPos_1caf90(p1, &v80, &v70);
        return 1;
    case 7:
    case 8:
        NodeCalcWorldMatrixThunk_186130(p0->m04, p1);
        return 1;
    case 9:
    case 10:
        NodeCalcWorldMatrix_186130(p0->m04, p1);
        return 1;
    case 11:
        TreasureBoxGetRot_33ae20(p0->m04, &v60);
        TreasureBoxGetPos_33ae30(p0->m04, &v50);
        MatFromRotPos_1caf90(p1, &v60, &v50);
        return 1;
    case 12:
        InsectCageSlotGetRot_39b320(p0->m04, &v40);
        InsectCageSlotGetPos_39b340(p0->m04, &v30);
        MatFromRotPos_1caf90(p1, &v40, &v30);
        return 1;
    }
    return 0;
}
