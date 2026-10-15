#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

struct VBase { u8 pad[0x1B0]; };
class VObj : public VBase {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void f15(f32);
};

extern "C" {
f32 VecDistanceXZ_13d390(V4 *, V4 *);
void VecScale_13be00(V4 *, V4 *, f32);
void VecAddInPlace_13e070(V4 *, V4 *);
void ModelSetPos_151110(u8 *, V4 *);
void GuardEffectStepMaybe_2d5260(u8 *);
s32 GetEffectMgr_2d9040(void);
void EffectMgrTick_2e3070(s32);
s32 BitArrayTest_384320(u8 *, s32);
s32 MenuObjSlotIsActive_3849d0(u8 *);
void MenuObjBattlePairSpawnSparkMaybe_385a30(u8 *, s32);
void MenuObjGetPosWithOffsetMaybe_385cf0(s32, V4 *, s32);
extern f32 D_0047FBC0;
extern f32 D_0047FBC4;
extern f32 D_0047FBC8;
extern f32 D_0047FBCC;
void MenuObjSetUpdate_3850c0(u8 *arg0);
}

void MenuObjSetUpdate_3850c0(u8 *arg0)
{
    V4 a;
    V4 b;
    V4 c;
    s32 i;
    u8 *e;
    u8 *o;

    if (BitArrayTest_384320(arg0 + 0x4155, 1) == 0) {
        i = 0;
        do {
            if (*(s32 *)(arg0 + i * 0xC + 0x1390) != 0) {
                MenuObjBattlePairSpawnSparkMaybe_385a30(arg0, i);
            }
            i++;
        } while (i < 2);
        i = 0;
        do {
            GuardEffectStepMaybe_2d5260(arg0 + i * 0x340 + 0x10);
            i++;
        } while (i < 6);
    }
    if (BitArrayTest_384320(arg0 + 0x4155, 2) == 0) {
        i = 0;
        do {
            e = arg0 + i * 0x7A0;
            if (MenuObjSlotIsActive_3849d0(e + 0x13B0) != 0) {
                e = arg0 + (u32)i * 0x7A0;
                MenuObjGetPosWithOffsetMaybe_385cf0(*(s32 *)(e + 0x13B0), &a, 0);
                MenuObjGetPosWithOffsetMaybe_385cf0(*(s32 *)(e + 0x13B4), &b, 0);
                if (VecDistanceXZ_13d390(&a, &b) < 6.0f) {
                    VecAddInPlace_13e070(&a, &b);
                    VecScale_13be00(&a, &a, 0.5f);
                    a.y += 3.0f;
                    o = arg0 + (s32)(u32)i * 0x7A0 + 0x13C0;
                    ModelSetPos_151110(o, &a);
                    ((VObj *)o)->f15(1.0f);
                }
            } else {
                { f32 *p = (f32 *)&c; p[0] = D_0047FBC0; p[1] = D_0047FBC4; p[2] = D_0047FBC8; p[3] = D_0047FBCC; }
                *(s32 *)&c.y = 0xC2480000;
                *(s32 *)&c.x = 0;
                *(s32 *)&c.z = 0;
                ModelSetPos_151110(e + 0x13C0, &c);
            }
            i++;
        } while (i < 2);
    }
    i = 0;
    do {
        o = arg0 + i * 0x790;
        *(f32 *)(o + 0x2738) = *(f32 *)(arg0 + 0x4150);
        ((VObj *)(o + 0x22F0))->f15(1.0f);
        i++;
    } while (i < 2);
    if (MenuObjSlotIsActive_3849d0(arg0 + 0x3210) != 0) {
        ((VObj *)(arg0 + 0x3220))->f15(0.5f);
    }
    if (MenuObjSlotIsActive_3849d0(arg0 + 0x39B0) != 0) {
        ((VObj *)(arg0 + 0x39C0))->f15(0.5f);
    }
    EffectMgrTick_2e3070(GetEffectMgr_2d9040());
}
