#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

extern const s32 D_004655D8;
extern const s32 D_004655E0;
extern const s32 D_00467660;
extern const s32 D_004676C8;
extern s32 D_004800F0;
extern s32 D_004800F4;
extern s32 D_00483C90;
extern s32 D_00483C9C;
extern s32 D_00483CA0;
extern s32 D_00483CAC;
extern s32 D_00483CB0;
extern s32 D_00483CB4;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitImgBoardParam_46ed20(void)
{
    IosBaseInitCtor_102bd0(&D_00483C9C);
    RegisterGlobalObject_100dc0(&D_00483C9C, IosBaseInitDtor_102ee0, &D_00483C90);
    WIosBaseInitCtor_103110(&D_00483CAC);
    RegisterGlobalObject_100dc0(&D_00483CAC, WIosBaseInitDtor_103420, &D_00483CA0);
    D_00483CB0 = D_004800F0;
    *(s32 *)&D_00467660 = D_004655D8;
    D_00483CB4 = D_004800F4;
    *(s32 *)&D_004676C8 = D_004655E0;
}
