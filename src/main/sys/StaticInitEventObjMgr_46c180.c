#include "types.h"

extern void ConstructArray_100620(void *, void *, void *, s32, s32);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void IosBaseInitCtor_102bd0(void *);
extern void WIosBaseInitCtor_103110(void *);
extern void MemStackCtor_14e030(void *);
extern void NavMgrPoolCtor_2d1b40(void *);
extern void NavMgrCtor_2d1c60(void *);
extern void EventPosRecListCtor_2d2110(void *);
extern void EventScriptRecListCtor_2d2180(void *);
extern void EventParamRecListCtor_2d21f0(void *);
extern void EventVolumeRecListCtor_2d2260(void *);
extern void EventPathRecListCtor_2d22d0(void *);
extern void EventObjMgrReset_2ea280(void *);
extern void UskMemoryInit_42e070(void *);
extern void UskStackInit_42e470(void *);
extern void DListInit_42eae0(void *);

extern u8 D_00471508[];
extern u8 D_00471638[];
extern u8 D_00471648[];
extern u8 D_00471658[];
extern u8 D_004825E8;
extern u8 D_004825F4;
extern u8 D_004825F8;
extern u8 D_00482604;
extern u8 D_00482608;
extern u8 D_00482618;
extern u8 D_00482628;
extern u8 D_004DCAB0[];
extern u8 D_004DCB10[];
extern u8 D_004DCB20[];
extern u8 D_004DCC70[];
extern void *D_004DCC7C[];
extern u8 D_004DCC84[];
extern u8 D_004DCCC0[];
extern u8 D_004DCCC4[];
extern void IosBaseInitDtor_102ee0(void);
extern void WIosBaseInitDtor_103420(void);
extern void UskMemoryDtor_2d1c90(void);
extern void EventObjMgrDtor_2d1d80(void);
extern void EvObjListDtor_2d1ff0(void);
extern void EvObjListCtor_2d20a0(void);
extern void NavMgrDtor_2d19a0(void);

void StaticInitEventObjMgr_46c180(void)
{
    void *base;

    IosBaseInitCtor_102bd0(&D_004825F4);
    RegisterGlobalObject_100dc0(&D_004825F4, &IosBaseInitDtor_102ee0, &D_004825E8);
    WIosBaseInitCtor_103110(&D_00482604);
    RegisterGlobalObject_100dc0(&D_00482604, &WIosBaseInitDtor_103420, &D_004825F8);
    MemStackCtor_14e030(&D_004DCAB0);
    base = &D_004DCB10;
    EventPathRecListCtor_2d22d0(base);
    EventVolumeRecListCtor_2d2260(&D_004DCB20);
    EventParamRecListCtor_2d21f0((u8 *)base + 0x20);
    EventScriptRecListCtor_2d2180((u8 *)base + 0x30);
    EventPosRecListCtor_2d2110((u8 *)base + 0x40);
    ConstructArray_100620((u8 *)base + 0x50, &EvObjListCtor_2d20a0, &EvObjListDtor_2d1ff0, 0x10, 0x10);
    EventObjMgrReset_2ea280(base);
    RegisterGlobalObject_100dc0(base, &EventObjMgrDtor_2d1d80, &D_00482608);
    base = &D_004DCC70;
    DListInit_42eae0(base);
    D_004DCC7C[0] = &D_00471658;
    DListInit_42eae0(base);
    D_004DCC7C[0] = &D_00471648;
    DListInit_42eae0(base);
    D_004DCC7C[0] = &D_00471638;
    DListInit_42eae0(base);
    D_004DCC7C[0] = &D_00471508;
    DListInit_42eae0(base);
    UskStackInit_42e470(&D_004DCC84);
    UskMemoryInit_42e070(base);
    RegisterGlobalObject_100dc0(base, &UskMemoryDtor_2d1c90, &D_00482618);
    NavMgrCtor_2d1c60(&D_004DCCC0);
    NavMgrPoolCtor_2d1b40(&D_004DCCC4);
    RegisterGlobalObject_100dc0(&D_004DCCC0, &NavMgrDtor_2d19a0, &D_00482628);
}
