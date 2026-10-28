#include "types.h"

extern "C" {
extern void RegisterGlobalObject_100dc0(void *arg0, void *arg1, void *arg2);
extern void IosBaseInitCtor_102bd0(void *arg0);
extern void WIosBaseInitCtor_103110(void *arg0);
extern void MemStackCtor_14e030(void *arg0);
extern void TargetRefCtor_2e71f0(void *arg0);
extern void HandleHeapCreate_3129b0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void ObjRefTableCtor_314a30(void *arg0);
extern void TargetSlotReset_3211c0(void *arg0);

extern u8 D_0046FFA0[];
extern u8 D_0046FFC0[];
extern u8 D_00471B10[];
extern u8 D_004829F8;
extern u8 D_00482A04;
extern u8 D_00482A08;
extern u8 D_00482A14;
extern u8 D_00482A18;
extern u8 D_00482A24;
extern u8 D_00482A28;
extern u8 D_00482A38;
extern u8 D_00482A40;
extern u8 D_004E7BF0[0x400];
extern void *D_004E7CD0[0x10];
extern void *D_004E7D90[0x10];
extern void *D_004E7DA0[0x10];
extern u8 D_004E7DA4[0x100];
extern u8 D_004E7E70[0x100];
extern u8 D_004E7F20[0x100];
extern void IosBaseInitDtor_102ee0(void);
extern void WIosBaseInitDtor_103420(void);
extern void HandleHeapDtor_312950(void);
extern void SpatialMgrDtor_313e70(void);
extern void ObjRefTableDtor_3148d0(void);
}

class V7BF0 {
public:
    u8 pad[0xE0];
    VC_VPTR_MEMBER;
    
    void v2() { VCM0(void, 0x10); }
};

extern "C" void StaticInitFieldObjSysMaybe_46cbc0(void)
{
    IosBaseInitCtor_102bd0(&D_00482A04);
    RegisterGlobalObject_100dc0(&D_00482A04, (void *)IosBaseInitDtor_102ee0, &D_004829F8);
    WIosBaseInitCtor_103110(&D_00482A14);
    RegisterGlobalObject_100dc0(&D_00482A14, (void *)WIosBaseInitDtor_103420, &D_00482A08);
    D_004E7D90[0] = D_0046FFC0;
    D_004E7CD0[0] = D_0046FFA0;
    ((V7BF0 *)D_004E7BF0)->v2();
    HandleHeapCreate_3129b0(&D_00482A24, 0, 0, 0x10);
    RegisterGlobalObject_100dc0(&D_00482A24, (void *)HandleHeapDtor_312950, &D_00482A18);
    ObjRefTableCtor_314a30(&D_00482A38);
    RegisterGlobalObject_100dc0(&D_00482A38, (void *)ObjRefTableDtor_3148d0, &D_00482A28);
    D_004E7DA0[0] = D_00471B10;
    MemStackCtor_14e030(D_004E7DA4);
    RegisterGlobalObject_100dc0(D_004E7DA0, (void *)SpatialMgrDtor_313e70, &D_00482A40);
    TargetRefCtor_2e71f0(D_004E7E70);
    TargetSlotReset_3211c0(D_004E7E70);
    TargetRefCtor_2e71f0(D_004E7F20);
}
