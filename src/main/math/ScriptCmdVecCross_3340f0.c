#include "types.h"
typedef unsigned __int128 u128;
extern void ScriptSlotsToVec4_334810(u128 *, void *);
extern void sceVu0OuterProduct(u128 *, u128 *, u128 *);
extern void ScriptSlotStoreVec3_334790(void *, u128 *);

s32 ScriptCmdVecCross_3340f0(u8 *p0, s32 p1)
{
    u128 v40;
    u128 v30;
    u128 v20;

    if (p1 != 9) {
        return 0;
    }
    ScriptSlotsToVec4_334810(&v30, p0 + 0x18);
    ScriptSlotsToVec4_334810(&v20, p0 + 0x30);
    sceVu0OuterProduct(&v40, &v30, &v20);
    ScriptSlotStoreVec3_334790(p0, &v40);
    return 1;
}
