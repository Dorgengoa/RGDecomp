/* rgp:protos */
#define RGP_SELF_CharaResLoadListMaybe_1f02d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CharaResLoadListMaybe_1f02d0(s32 arg0, s32 arg1, s32 *arg2, s32 arg3)
{
    u8 *t;
    s32 n;
    s32 i;
    s32 j;
    s32 *p;
    s32 v;
    s32 w;
    s32 n2;

    GetActionMgr_1fdb50();
    t = ((u8 *)GetGameData_1fede0());
    n2 = PartyCountMembers_3c2010(*(s32 *)(t + 0x18), 1, 1);
    n = n2;
    for (i = 0; i < arg3; i++) {
        p = &arg2[i];
        CharaEnsureDataLoaded_1f0ca0(arg0, *p);
        for (j = 0; j < n; j++) {
            v = ((short)PartyGetMemberId_3c2490(*(s32 *)(t + 0x18), i));
            w = arg2[j];
            if (w == v) {
                CharaResRequestBtChrByIdMaybe_1f09f0(arg0, *p);
            }
        }
        CharaResRecreateAbilityData_1f0800(arg0, *p);
    }
}
