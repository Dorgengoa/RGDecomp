#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

extern const s32 D_00465578;
extern const s32 D_00465580;
extern const s32 D_00465588;
extern const s32 D_004673F8;
extern const s32 D_00467440;
extern const s32 D_004674B0;
extern s32 D_004800B8;
extern s32 D_004800BC;
extern s32 D_004800C0;
extern s32 D_00483BD0;
extern s32 D_00483BDC;
extern s32 D_00483BE0;
extern s32 D_00483BEC;
extern s32 D_00483BF0;
extern s32 D_00483BF4;
extern s32 D_00483BF8;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitEncountParam_46eb20(void)
{
    IosBaseInitCtor_102bd0(&D_00483BDC);
    RegisterGlobalObject_100dc0(&D_00483BDC, IosBaseInitDtor_102ee0, &D_00483BD0);
    WIosBaseInitCtor_103110(&D_00483BEC);
    RegisterGlobalObject_100dc0(&D_00483BEC, WIosBaseInitDtor_103420, &D_00483BE0);
    D_00483BF0 = D_004800B8;
    *(s32 *)&D_004673F8 = D_00465578;
    D_00483BF4 = D_004800BC;
    *(s32 *)&D_00467440 = D_00465580;
    D_00483BF8 = D_004800C0;
    *(s32 *)&D_004674B0 = D_00465588;
}
