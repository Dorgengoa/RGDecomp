/* rgp:protos */
#define RGP_SELF_MapAreaHeapAllocRest_1d8e50 1
#define RGP_SELF_busy 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    s32 unk0;
    void *unk4;
} T1d8e50_arg0;

static inline u32 busy(void*p){return *(s32*)((u8*)p+0x28)!=0;}
s32 MapAreaHeapAllocRest_1d8e50(T1d8e50_arg0 *arg0)
{
    s32 temp_18;
    s32 temp_17;
    void *temp_4;
    void *temp_4_2;

    arg0->unk0 = 0;
    temp_4 = arg0->unk4;
    if (temp_4 == NULL) {
        return -1;
    }
    if (busy(temp_4)) return -1;
    {
        MemStackHeapAlloc_14db10(temp_4, 2, 0, 0x40);
        temp_4_2 = arg0->unk4;
        temp_18 = (*(s32 *)((u8 *)temp_4_2 + 0x34) - *(s32 *)((u8 *)temp_4_2 + 0x2C)) - 4;
        temp_17 = MemStackAllocAligned64_14da10(temp_4_2, temp_18);
        MemStackReturnToOwnerMaybe_14dad0(arg0->unk4);
        return MapAreaHeapInit_1d8c50(arg0, temp_17, temp_18);
    }
    return -1;
    return -1;
}
