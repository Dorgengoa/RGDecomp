#include "types.h"

struct SubBase {
    u8 pad0[0xE0];
};

class Sub : public SubBase {
public:
    VC_VPTR_MEMBER;
    
    void v2() { VCM0(void, 0x10); }
};

extern "C" {

extern void FrameTreeOrFlags_149530(s32, s32);
extern u8 *ArrayGetChecked_14c5e0(void *, s32);
extern s32 ModelResGetMaterialCount_14c640(void *);
extern u8 *MemStackNew_14e230(s32, s32);
extern void ModelResStripToPositionsMaybe_14e2b0(void *);
extern void ModelBuildFrames_1506c0(u8 *, void *, s32, s32);
extern s32 ModelGetRootFrame_1511a0(u8 *);
extern s32 GetDrawCtx_15de80(void);
extern s32 CollFrameTreeBuild_16ba00(void *, s32);
extern void MotionListInit_1726f0(u8 *);
extern s32 ArchiveGetFileData_181dd0(s32, s32, s32 *);
extern void ModelObjPlayMotionByIndex_186790(u8 *, s32, s32);
extern void ModelObjBaseInit_1867b0(u8 *);
extern u8 *MapModelCreate_1952b0(s32, void *, s32);
extern u8 D_0045A000[];
extern u8 D_0046FFA0[];
extern u8 D_0046FFC0[];
extern u8 D_00470440[];
extern u8 D_00470650[];
extern u8 D_00470690[];
extern s32 D_00481310;
extern s32 *D_00481328;
extern s32 D_0048132C;
extern s32 D_00481330;
extern s32 D_00481338;
extern f32 D_00481340;
extern f32 D_00481344;
extern f32 D_00481348;
extern s32 D_00481350;

}

extern "C" s32 MapModelCfgMdsEnd_195750(void) {
    u8 *obj;
    s32 res;
    s32 n;
    s32 i;
    s32 m;
    u8 *e;
    s32 r;
    s32 sp6C;

    if (D_00481328 == 0) {
        return 0;
    }
    if (D_00481350 != 0) {
        return 1;
    }
    obj = 0;
    D_00481350 = 1;
    res = 0;
    if (D_00481338 != 0) {
        n = ModelResGetMaterialCount_14c640(&D_00481310);
        for (i = 0; i < n; i++) {
            e = ArrayGetChecked_14c5e0(&D_00481310, i);
            *(s32 *)(e + 0x40) = 8;
            *(s32 *)(e + 0x44) &= ~4;
            *(f32 *)(e + 0x20) = D_00481340;
            *(f32 *)(e + 0x24) = D_00481344;
            *(f32 *)(e + 0x28) = D_00481348;
        }
    }
    m = D_00481328[1];
    if (m & 1) {
        n = ModelResGetMaterialCount_14c640(&D_00481310);
        for (i = 0; i < n; i++) {
            e = ArrayGetChecked_14c5e0(&D_00481310, i);
            if (m == 1) {
                *(f32 *)(e + 0x20) = 1.0f;
                *(f32 *)(e + 0x24) = 0.0f;
            }
            if (m == 3) {
                *(f32 *)(e + 0x20) = 0.0f;
                *(f32 *)(e + 0x24) = 1.0f;
            }
        }
    }
    switch (D_00481328[1]) {
    case 16:
        ModelResStripToPositionsMaybe_14e2b0(&D_00481310);
    case 0:
        obj = MemStackNew_14e230(0x200, D_0048132C);
        if (obj != 0) {
            *(u8 **)(obj + 0x1B0) = D_0046FFC0;
            *(u8 **)(obj + 0xF0) = D_0046FFA0;
            ((Sub *)(obj + 0x10))->v2();
            *(u8 **)(obj + 0x1B0) = D_00470440;
            *(u8 **)(obj + 0x1B0) = D_00470690;
            MotionListInit_1726f0(obj + 0x1F0);
            *(u8 **)(obj + 0x1B0) = D_00470650;
        }
        if (obj != 0) {
            ModelObjBaseInit_1867b0(obj);
            ModelBuildFrames_1506c0(obj, &D_00481310, GetDrawCtx_15de80(), D_0048132C);
        }
        break;
    case 3:
    case 1:
    case 9:
        res = CollFrameTreeBuild_16ba00(&D_00481310, D_0048132C);
        break;
    case 4:
        obj = MapModelCreate_1952b0(ArchiveGetFileData_181dd0(D_00481330, D_00481328[0], &sp6C), D_0045A000, D_0048132C);
        ModelObjPlayMotionByIndex_186790(obj, 0, 0);
        break;
    }
    if (D_00481328[7] != 0) {
        r = 0;
        if (obj != 0) {
            r = ModelGetRootFrame_1511a0(obj);
        }
        if (r != 0) {
            FrameTreeOrFlags_149530(r, 8);
        }
    }
    D_00481328[2] = (s32)obj;
    D_00481328[3] = res;
    return 1;
}
