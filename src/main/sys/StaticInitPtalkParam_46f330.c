#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

extern const s32 D_004655B0;
extern const s32 D_004655B8;
extern const s32 D_00467F48;
extern const s32 D_00467F78;
extern s32 D_004800D4;
extern s32 D_004800D8;
extern s32 D_00483E80;
extern s32 D_00483E8C;
extern s32 D_00483E90;
extern s32 D_00483E9C;
extern s32 D_00483EA0;
extern s32 D_00483EA4;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitPtalkParam_46f330(void)
{
    IosBaseInitCtor_102bd0(&D_00483E8C);
    RegisterGlobalObject_100dc0(&D_00483E8C, IosBaseInitDtor_102ee0, &D_00483E80);
    WIosBaseInitCtor_103110(&D_00483E9C);
    RegisterGlobalObject_100dc0(&D_00483E9C, WIosBaseInitDtor_103420, &D_00483E90);
    D_00483EA0 = D_004800D4;
    *(s32 *)&D_00467F48 = D_004655B0;
    D_00483EA4 = D_004800D8;
    *(s32 *)&D_00467F78 = D_004655B8;
}
