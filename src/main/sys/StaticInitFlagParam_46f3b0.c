#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

extern const s32 D_00465400;
extern const s32 D_00465408;
extern const s32 D_00465410;
extern const s32 D_00465418;
extern const s32 D_00465420;
extern const s32 D_00465428;
extern const s32 D_00467FD8;
extern const s32 D_00468040;
extern const s32 D_00468088;
extern const s32 D_004680C8;
extern const s32 D_00468108;
extern const s32 D_00468148;
extern s32 D_0047FFF8;
extern s32 D_0047FFFC;
extern s32 D_00480000;
extern s32 D_00480004;
extern s32 D_00480008;
extern s32 D_0048000C;
extern s32 D_00483EB0;
extern s32 D_00483EBC;
extern s32 D_00483EC0;
extern s32 D_00483ECC;
extern s32 D_00483ED0;
extern s32 D_00483ED4;
extern s32 D_00483ED8;
extern s32 D_00483EDC;
extern s32 D_00483EE0;
extern s32 D_00483EE4;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitFlagParam_46f3b0(void)
{
    IosBaseInitCtor_102bd0(&D_00483EBC);
    RegisterGlobalObject_100dc0(&D_00483EBC, IosBaseInitDtor_102ee0, &D_00483EB0);
    WIosBaseInitCtor_103110(&D_00483ECC);
    RegisterGlobalObject_100dc0(&D_00483ECC, WIosBaseInitDtor_103420, &D_00483EC0);
    D_00483ED0 = D_0047FFF8;
    *(s32 *)&D_00467FD8 = D_00465400;
    D_00483ED4 = D_0047FFFC;
    *(s32 *)&D_00468040 = D_00465408;
    D_00483ED8 = D_00480000;
    *(s32 *)&D_00468088 = D_00465410;
    D_00483EDC = D_00480004;
    *(s32 *)&D_004680C8 = D_00465418;
    D_00483EE0 = D_00480008;
    *(s32 *)&D_00468108 = D_00465420;
    D_00483EE4 = D_0048000C;
    *(s32 *)&D_00468148 = D_00465428;
}
