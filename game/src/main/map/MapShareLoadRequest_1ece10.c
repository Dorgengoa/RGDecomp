/* rgp:protos */
#define RGP_SELF_Busy 1
#define RGP_SELF_MapShareLoadRequest_1ece10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S001ece10 {
    u8 pad0[0x28];
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x34 - 0x30];
    s32 unk34;
} S001ece10;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline u32 Busy(S001ece10 *s)
{
    return s->unk28 != 0;
}

s32 MapShareLoadRequest_1ece10(s32 arg0, S001ece10 *arg1, s32 arg2, s32 arg3)
{
    s32 a;
    s32 b;

    if (((unsigned char)MapDataIsEnabled_1e7c20((void *)arg0)) == 0) {
        return 0;
    }
    if (((signed char)MapDataGetState_1e7a00(arg0)) == -1) {
        return 0;
    }
    if (((signed char)MapDataGetState_1e7a00(arg0)) != 0) {
        return 0;
    }
    if (arg1 == NULL || arg2 == 0) {
        return 0;
    }
    if (Busy(arg1)) {
        return 0;
    }
    if (MapDataGetName_1e7bf0(arg0) == 0) {
        return 0;
    }
    if (MapDataGetFileName_1e7be0(arg0) == 0) {
        return 0;
    }
    a = 0;
    if (arg3 == 1) {
        MemStackHeapAlloc_14db10(arg1, 2, 0, 0x40);
        b = (arg1->unk34 - arg1->unk2C) - 4;
        a = MemStackAllocAligned64_14da10(arg1, b);
        MemStackReturnToOwnerMaybe_14dad0(arg1);
    } else {
        b = AlignUp_1cacf0(MapDataGetHeapSize_1e7ba0(arg0), 0x100);
        switch (MapDataIsMemRev_1e7b90(arg0)) {
        case 0:
            a = MemStackHeapAllocFront_14dd10(arg1, b);
            break;
        case 1:
            a = MemStackHeapAllocBack_14dcf0(arg1, b);
            break;
        }
    }
    return MapDataLoadRequest_1e6990(arg0, arg1, arg2, MapDataGetFileName_1e7be0(arg0), a, b);
}
