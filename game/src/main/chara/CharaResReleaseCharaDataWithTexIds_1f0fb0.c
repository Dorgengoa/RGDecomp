/* rgp:protos */
#define RGP_SELF_CharaResReleaseCharaDataWithTexIds_1f0fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Buf60 {
    void *ptrs[4];
    u8 pad[0x28];
};

void CharaResReleaseCharaDataWithTexIds_1f0fb0(s32 arg0, s32 arg1) {
    struct Buf60 sp60 __attribute__((aligned(16)));
    s32 count;
    s32 temp_2;
    s32 i;
    void *obj;

    temp_2 = ((s32)GetCharaDataMgr_1fdb70());
    count = CharaDataCollectAllNodes_1ed5d0(temp_2, arg1, 0, &sp60, 0x10);
    for (i = 0; i < count; i++) {
        obj = *(void **)((u8 *)sp60.ptrs[i] + 0x20);
        if (obj != NULL) {
            IdBitmapClearBit_1f50f0(arg0 + 0xD04, *(s32 *)((u8 *)obj + 0x4DC));
        }
    }
    CharaDataReleaseById_1ed850(temp_2, arg1);
}
