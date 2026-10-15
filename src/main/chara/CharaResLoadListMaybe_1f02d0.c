#include "types.h"

s32 CharaResRecreateAbilityData_1f0800(s32, s32);
s32 CharaResRequestBtChrByIdMaybe_1f09f0(s32, s32);
s32 CharaEnsureDataLoaded_1f0ca0(s32, s32);
s32 GetActionMgr_1fdb50();
u8 *GetGameData_1fede0();
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyGetMemberId_3c2490(s32, s32);

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
    t = GetGameData_1fede0();
    n2 = PartyCountMembers_3c2010(*(s32 *)(t + 0x18), 1, 1);
    n = n2;
    for (i = 0; i < arg3; i++) {
        p = &arg2[i];
        CharaEnsureDataLoaded_1f0ca0(arg0, *p);
        for (j = 0; j < n; j++) {
            v = PartyGetMemberId_3c2490(*(s32 *)(t + 0x18), i);
            w = arg2[j];
            if (w == v) {
                CharaResRequestBtChrByIdMaybe_1f09f0(arg0, *p);
            }
        }
        CharaResRecreateAbilityData_1f0800(arg0, *p);
    }
}
