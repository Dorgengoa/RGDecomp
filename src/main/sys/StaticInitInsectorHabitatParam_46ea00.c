#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

extern const s32 D_00465600;
extern const s32 D_00465608;
extern const s32 D_00467240;
extern const s32 D_00467288;
extern s32 D_004800FC;
extern s32 D_00480100;
extern s32 D_00483B60;
extern s32 D_00483B6C;
extern s32 D_00483B70;
extern s32 D_00483B7C;
extern s32 D_00483B80;
extern s32 D_00483B84;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitInsectorHabitatParam_46ea00(void)
{
    IosBaseInitCtor_102bd0(&D_00483B6C);
    RegisterGlobalObject_100dc0(&D_00483B6C, IosBaseInitDtor_102ee0, &D_00483B60);
    WIosBaseInitCtor_103110(&D_00483B7C);
    RegisterGlobalObject_100dc0(&D_00483B7C, WIosBaseInitDtor_103420, &D_00483B70);
    D_00483B80 = D_004800FC;
    *(s32 *)&D_00467240 = D_00465600;
    D_00483B84 = D_00480100;
    *(s32 *)&D_00467288 = D_00465608;
}
