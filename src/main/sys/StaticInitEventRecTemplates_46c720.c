#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);
extern void EventScriptRecCtor_2e3ac0(void *);
extern void EventVolumeRecCtor_2e4f60(void *);
extern void EventPathRecCtor_2e43f0(void *);
extern void EvSwitchObjCtor_2f86b0(void *);
extern void EvFollowObjCtor_2f81d0(void *);
extern void EvDoorObjCtor_3044b0(void *);
extern void EvMapObjCtor_367040(void *);
extern void ObjTypeVehicleCtor_338410(void *);
extern void EvObjLiftCtor_336560(void *);
extern void EvM05ChangeCtor_352400(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482800;
extern s32 D_0048280C;
extern s32 D_00482810;
extern s32 D_0048281C;
extern u8 D_004E66B0[];
extern u8 D_004E66D0[];
extern u8 D_004E6700[];
extern u8 D_004E6720[];
extern u8 D_004E6880[];
extern u8 D_004E69D0[];
extern u8 D_004E6B80[];
extern u8 D_004E6EC0[];
extern u8 D_004E7000[];
extern u8 D_004E7110[];
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitEventRecTemplates_46c720(void)
{
    IosBaseInitCtor_102bd0(&D_0048280C);
    RegisterGlobalObject_100dc0(&D_0048280C, IosBaseInitDtor_102ee0, &D_00482800);
    WIosBaseInitCtor_103110(&D_0048281C);
    RegisterGlobalObject_100dc0(&D_0048281C, WIosBaseInitDtor_103420, &D_00482810);
    EventScriptRecCtor_2e3ac0(D_004E66B0);
    EventVolumeRecCtor_2e4f60(D_004E66D0);
    EventPathRecCtor_2e43f0(D_004E6700);
    EvSwitchObjCtor_2f86b0(D_004E6720);
    EvFollowObjCtor_2f81d0(D_004E6880);
    EvDoorObjCtor_3044b0(D_004E69D0);
    EvMapObjCtor_367040(D_004E6B80);
    ObjTypeVehicleCtor_338410(D_004E6EC0);
    EvObjLiftCtor_336560(D_004E7000);
    EvM05ChangeCtor_352400(D_004E7110);
}
