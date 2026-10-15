#include "types.h"

extern void IosBaseInitCtor_102bd0(void *);
extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void WIosBaseInitCtor_103110(void *);

extern const s32 D_00465610;
extern const s32 D_00465618;
extern const s32 D_00465620;
extern const s32 D_00465628;
extern const s32 D_00466E68;
extern const s32 D_00466E98;
extern const s32 D_00466ED0;
extern const s32 D_00466F08;
extern s32 D_00480104;
extern s32 D_00480108;
extern s32 D_0048010C;
extern s32 D_00480110;
extern s32 D_00483A30;
extern s32 D_00483A3C;
extern s32 D_00483A40;
extern s32 D_00483A4C;
extern s32 D_00483A50;
extern s32 D_00483A54;
extern s32 D_00483A58;
extern s32 D_00483A5C;
extern u8 IosBaseInitDtor_102ee0[];
extern u8 WIosBaseInitDtor_103420[];

void StaticInitInsectorBreedParam_46e650(void)
{
    IosBaseInitCtor_102bd0(&D_00483A3C);
    RegisterGlobalObject_100dc0(&D_00483A3C, IosBaseInitDtor_102ee0, &D_00483A30);
    WIosBaseInitCtor_103110(&D_00483A4C);
    RegisterGlobalObject_100dc0(&D_00483A4C, WIosBaseInitDtor_103420, &D_00483A40);
    D_00483A50 = D_00480104;
    *(s32 *)&D_00466E68 = D_00465610;
    D_00483A54 = D_00480108;
    *(s32 *)&D_00466E98 = D_00465618;
    D_00483A58 = D_0048010C;
    *(s32 *)&D_00466ED0 = D_00465620;
    D_00483A5C = D_00480110;
    *(s32 *)&D_00466F08 = D_00465628;
}
