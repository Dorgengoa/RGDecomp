#include "types.h"

extern void VariantSetS32_36f040(s32, s32, s32);
extern void PartyRefreshMembersMaybe_2f40b0(s32);

extern s32 D_00483960;
extern s32 D_00483964;

void ScriptFnPartyRefreshMembersMaybe_3d8190(s32 p0)
{
    if (p0 == 0) {
        return;
    }
    VariantSetS32_36f040(p0, 0, 1);
    if (D_00483960 != 0) {
        if (D_00483964 != 0) {
            goto call;
        }
    }
    return;
call:
    PartyRefreshMembersMaybe_2f40b0(1);
}
