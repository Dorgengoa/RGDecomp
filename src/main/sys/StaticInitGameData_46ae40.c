#include "types.h"

/* A branch-free STATIC INITIALISER (the IosBaseInitCtor_102bd0 / RegisterGlobalObject_100dc0 family).
   Drafted by build/rk_ctor.py: m2c gives the order and the arguments, the
   listing gives each global's RELOCATION -- %gp_rel means a plain extern,
   %hi/%lo means an incomplete array, because a written global cannot take
   the `const` escape out of small data. */

extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void IosBaseInitCtor_102bd0(void *);
extern void WIosBaseInitCtor_103110(void *);
extern void MemStackCtor_14e030(void *);
extern void GameDataInit_3ee5b0(void *);
extern void InteractRecResetMaybe_3ee600(void *);
extern void WorldDataMgrCtor_3f4010(void *);
extern void IosBaseInitDtor_102ee0(void);
extern void WIosBaseInitDtor_103420(void);

extern s32 D_00481AA0;
extern s32 D_00481AAC;
extern s32 D_00481AB0;
extern s32 D_00481ABC;
extern u8 D_00476180[];
extern u8 D_004B8A20[];
extern u8 D_004B8A80[];
extern void * D_004B8B30[];
extern u8 D_004B8B64[];

void StaticInitGameData_46ae40(void)
{
    IosBaseInitCtor_102bd0(&D_00481AAC);
    RegisterGlobalObject_100dc0(&D_00481AAC, IosBaseInitDtor_102ee0, &D_00481AA0);
    WIosBaseInitCtor_103110(&D_00481ABC);
    RegisterGlobalObject_100dc0(&D_00481ABC, WIosBaseInitDtor_103420, &D_00481AB0);
    MemStackCtor_14e030(D_004B8A20);
    WorldDataMgrCtor_3f4010(D_004B8A80);
    D_004B8B30[0] = D_00476180;
    InteractRecResetMaybe_3ee600(D_004B8B64);
    GameDataInit_3ee5b0(D_004B8B30);
}
