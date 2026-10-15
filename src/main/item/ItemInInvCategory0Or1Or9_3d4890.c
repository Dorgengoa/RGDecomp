#include "types.h"
extern s32 ItemInInvCategory0_3d4960(s32);
extern s32 ItemInInvCategory1_3d4920(s32);
extern s32 ItemInInvCategory9_3d48e0(s32);

s32 ItemInInvCategory0Or1Or9_3d4890(s32 p0)
{
    s32 ok;

    ok = (ItemInInvCategory0_3d4960(p0) != 0);
    if (!ok) {
        ok = (ItemInInvCategory1_3d4920(p0) != 0);
    }
    if (!ok) {
        ok = (ItemInInvCategory9_3d48e0(p0) != 0);
    }
    return ok;
}
