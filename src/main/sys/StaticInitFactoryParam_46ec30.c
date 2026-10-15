#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

extern const s32 D_00465640;
extern const s32 D_00465648;
extern const s32 D_00467560;
extern const s32 D_004675A8;
extern s32 D_00480124;
extern s32 D_00480128;
extern s32 D_00483C28;
extern s32 D_00483C34;
extern s32 D_00483C38;
extern s32 D_00483C44;
extern s32 D_00483C48;
extern s32 D_00483C50;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitFactoryParam_46ec30(void)
{
    IosBaseInitCtor_102bd0(&D_00483C34);
    RegisterGlobalObject_100dc0(&D_00483C34, IosBaseInitDtor_102ee0, &D_00483C28);
    WIosBaseInitCtor_103110(&D_00483C44);
    RegisterGlobalObject_100dc0(&D_00483C44, WIosBaseInitDtor_103420, &D_00483C38);
    D_00483C48 = D_00480124;
    *(s32 *)&D_00467560 = D_00465640;
    D_00483C50 = D_00480128;
    *(s32 *)&D_004675A8 = D_00465648;
}
