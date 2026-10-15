#include "types.h"

typedef struct Obj_FUN_00203dc0 Obj_FUN_00203dc0;

extern const u8 D_00527020[];
extern const u8 D_004BC250[];
extern s32 D_00481C00;
extern void func_4F7180(const u8 *p);
extern void func_506D70(const u8 *p);
extern void func_4F4600(const u8 *p);
extern Obj_FUN_00203dc0 *GetLoaderMgr_1f59d0(void);
extern void LoaderReleaseById_1cd340(Obj_FUN_00203dc0 *o, s32 n);
extern void BattleCmdResPendingReset_204e60(void);

void FieldHudRelease_203dc0(void)
{
    func_4F7180(D_00527020);
    func_506D70(D_004BC250);
    func_4F4600(D_00527020);
    LoaderReleaseById_1cd340(GetLoaderMgr_1f59d0(), D_00481C00);
    BattleCmdResPendingReset_204e60();
}
