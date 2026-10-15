#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

extern const s32 D_004654C8;
extern const s32 D_004654D0;
extern const s32 D_004654D8;
extern const s32 D_004654E0;
extern const s32 D_00466FF0;
extern const s32 D_00467038;
extern const s32 D_00467088;
extern const s32 D_004670C8;
extern s32 D_0048005C;
extern s32 D_00480060;
extern s32 D_00480064;
extern s32 D_00480068;
extern s32 D_00483AB0;
extern s32 D_00483ABC;
extern s32 D_00483AC0;
extern s32 D_00483ACC;
extern s32 D_00483AD0;
extern s32 D_00483AD4;
extern s32 D_00483AD8;
extern s32 D_00483ADC;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitBtlEffCalcParam_46e7f0(void)
{
    IosBaseInitCtor_102bd0(&D_00483ABC);
    RegisterGlobalObject_100dc0(&D_00483ABC, IosBaseInitDtor_102ee0, &D_00483AB0);
    WIosBaseInitCtor_103110(&D_00483ACC);
    RegisterGlobalObject_100dc0(&D_00483ACC, WIosBaseInitDtor_103420, &D_00483AC0);
    D_00483AD0 = D_0048005C;
    *(s32 *)&D_00466FF0 = D_004654C8;
    D_00483AD4 = D_00480060;
    *(s32 *)&D_00467038 = D_004654D0;
    D_00483AD8 = D_00480064;
    *(s32 *)&D_00467088 = D_004654D8;
    D_00483ADC = D_00480068;
    *(s32 *)&D_004670C8 = D_004654E0;
}
