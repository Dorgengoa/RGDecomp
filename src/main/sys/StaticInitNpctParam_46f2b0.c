#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

extern const s32 D_00465568;
extern const s32 D_00465570;
extern const s32 D_00467EB8;
extern const s32 D_00467EE8;
extern s32 D_004800B0;
extern s32 D_004800B4;
extern s32 D_00483E50;
extern s32 D_00483E5C;
extern s32 D_00483E60;
extern s32 D_00483E6C;
extern s32 D_00483E70;
extern s32 D_00483E74;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitNpctParam_46f2b0(void)
{
    IosBaseInitCtor_102bd0(&D_00483E5C);
    RegisterGlobalObject_100dc0(&D_00483E5C, IosBaseInitDtor_102ee0, &D_00483E50);
    WIosBaseInitCtor_103110(&D_00483E6C);
    RegisterGlobalObject_100dc0(&D_00483E6C, WIosBaseInitDtor_103420, &D_00483E60);
    D_00483E70 = D_004800B0;
    *(s32 *)&D_00467EB8 = D_00465568;
    D_00483E74 = D_004800B4;
    *(s32 *)&D_00467EE8 = D_00465570;
}
