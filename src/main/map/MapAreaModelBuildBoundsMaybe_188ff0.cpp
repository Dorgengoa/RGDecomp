#include "types.h"
#include "vec.h"
#pragma opt_common_subs off
#pragma opt_propagation off
extern "C" void MapAreaModelBuildObjTablesMaybe_18d940(void);
extern "C" s32 NodeObjGetWorldBounds_194420(void *, u128 *);
extern "C" void TexPairResolveAll_18fa70(void);
extern "C" void BBoxUnion_13dea0(void *, u128 *);

extern "C" void MapAreaModelBuildBoundsMaybe_188ff0(void *arg0) {
    u128 sp50[2];
    s32 count;
    void **arr;
    s32 i;
    void *obj;

    MapAreaModelBuildObjTablesMaybe_18d940();
    count = *(s32 *)((u8 *)arg0 + 0x504);
    arr = *(void ***)((u8 *)arg0 + 0x508);
    for (i = 0; i < count; i++) {
        obj = arr[i];
        {
            bool off = *(s8 *)((u8 *)obj + 0x6C) == 0;
            if (off) {
                continue;
            }
        }
        if (NodeObjGetWorldBounds_194420(obj, &sp50[0]) == 0) {
            continue;
        }
        if (*(s32 *)((u8 *)arg0 + 0x554) == 0) {
            *(u128 *)((u8 *)arg0 + 0x560) = sp50[0];
            *(u128 *)((u8 *)arg0 + 0x570) = sp50[1];
            *(s32 *)((u8 *)arg0 + 0x554) = 1;
        } else {
            BBoxUnion_13dea0((u8 *)arg0 + 0x560, &sp50[0]);
        }
    }
    TexPairResolveAll_18fa70();
}
