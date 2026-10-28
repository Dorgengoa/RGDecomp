/* rgp:protos */
#line 1
#include "types.h"

class A {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void fA4(f32 * a0) { VCM(void, (void *, f32 *), 0xA4, a0); }
    void fA8(f32 * a0) { VCM(void, (void *, f32 *), 0xA8, a0); }
};

class B {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f44(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
};

extern "C" {
extern void ModelSetPos_151110(u8 *, f32 *);
extern A *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
extern void VecScaleToLength_1cb510(f32 *, f32 *, f32);
extern void VecSub_1cbd00(f32 *, f32 *, f32 *);
extern void VecAdd_1cbdc0(f32 *, f32 *, f32 *);
extern s32 MapObjIsLoaded_1e0a80(void *);
extern void MapObjRelease_1e0a90(u8 *);
extern s32 MapFindBlockAtPos_1e3a00(s32, f32 *, f32);
extern s32 MapDataHasFallenLeaves_1e7a40(s32);
extern u8 *GetCurrentScene_1f5be0(void);
extern u8 *GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern f32 D_0045B080[4];
}

extern "C" void MapObjStep_1e0660(u8 *arg0, f32 fparg0)
{
    f32 sp60[4] __attribute__((aligned(16)));
    f32 sp50[4] __attribute__((aligned(16)));
    f32 sp40[4] __attribute__((aligned(16)));
    f32 f;
    s32 k;
    s32 r;
    u8 *g;
    u8 *h;
    A *a;

    if (((unsigned char)MapObjIsLoaded_1e0a80((void *)arg0)) == 0) {
        return;
    }
    g = GetGameData_1fede0();
    k = *(s16 *)(arg0 + 0x14);
    switch (k) {
    case 0:
        if (StateFlagTest_3ccd70(*(s32 *)(g + 0x10), 0x7E9) == 0) {
            MapObjRelease_1e0a90(arg0);
            return;
        }
        break;
    case 1:
        h = GetCurrentScene_1f5be0();
        a = ObjRecGetLiveObject_1c3bc0(h, *(s32 *)(h + 0x4344));
        if (a != 0) {
            a->fA4(sp60);
            a->fA8(sp50);
            VecSub_1cbd00(sp40, sp50, sp60);
            f = D_0045B080[0];
            VecScaleToLength_1cb510(sp40, sp40, 10.0f * f);
            VecAdd_1cbdc0(sp50, sp60, sp40);
            sp50[1] -= f;
            r = MapFindBlockAtPos_1e3a00(GetMapMgr_201a90(), sp50, 20.0f * f);
            if (r != 0 && ((unsigned char)MapDataHasFallenLeaves_1e7a40(r)) != 0) {
                ModelSetPos_151110(*(u8 **)(arg0 + 0xC), sp50);
            }
        }
        break;
    default:
        return;
    }
    ((B *)*(u8 **)(arg0 + 0xC))->f44(fparg0);
}
