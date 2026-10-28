/* rgp:protos */
#define RGP_SELF_FieldHudRelease_203dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_00203dc0 Obj_FUN_00203dc0;

extern u8 D_00527020[];
extern u8 D_004BC250[];
extern s32 D_00481C00;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void FieldHudRelease_203dc0(void)
{
    func_4F7180(D_00527020);
    func_506D70(D_004BC250);
    func_4F4600(D_00527020);
    LoaderReleaseById_1cd340(((Obj_FUN_00203dc0 *)GetLoaderMgr_1f59d0()), D_00481C00);
    BattleCmdResPendingReset_204e60();
}
